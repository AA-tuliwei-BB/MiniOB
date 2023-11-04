/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/aggrfunc_logical_operator.h"
#include "sql/operator/expression_logical_operator.h"
#include "sql/operator/orderby_logical_operator.h"
#include "sql/operator/groupby_logical_operator.h"
#include "sql/operator/value_list_logical_operator.h"
#include "sql/operator/create_select_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/create_select_stmt.h"
#include "logical_plan_generator.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;

    case StmtType::CREATE_SELECT: {
      CreateSelectStmt *create_select_stmt = static_cast<CreateSelectStmt *>(stmt);
      rc = create_plan(create_select_stmt, logical_operator);
    } break;

    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    JoinStmt *join_stmt, const std::vector<Field> &all_fields, std::unique_ptr<LogicalOperator> &logical_operator)
{

  const std::vector<Table *> &tables = join_stmt->tables;
  for (Table *table : tables) {
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true/*readonly*/));
    if (logical_operator == nullptr) {
      logical_operator = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(logical_operator));
      join_oper->add_child(std::move(table_get_oper));
      logical_operator = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(join_stmt->filter_stmt.get(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if (predicate_oper) {
    if (logical_operator) {
      PredicateLogicalOperator* tmp = static_cast<PredicateLogicalOperator*>(predicate_oper.get());
      tmp->set_table_get(std::move(logical_operator));
      logical_operator = std::move(predicate_oper);
    }
  }

  
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  for (int i = 0; i < select_stmt->from_size(); ++i) 
  {
    Table* const& table = tables[i];
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  std::vector<std::unique_ptr<JoinStmt>> &joins = select_stmt->joins();
  if(!joins.empty()){
    for(auto &it : joins){
      RC rc = create_plan(it.get(), all_fields, table_oper);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create join logical plan. rc=%s", strrc(rc));
        return rc;
      }
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<LogicalOperator> orderby_oper(nullptr);
  if (select_stmt->orders_fields().size() != 0) {
    orderby_oper = unique_ptr<LogicalOperator>(
        new OrderbyLogicalOperator(select_stmt->query_fields(), select_stmt->orders_fields(), select_stmt->asc()));
  }

  if (select_stmt->group_fields().size() != 0) {
    std::vector<bool> asc;
    asc.resize(select_stmt->group_fields().size());
    for (int i = 0; i < int(asc.size()); ++i) {
      asc[i] = true;
    }
    orderby_oper = unique_ptr<LogicalOperator>(
        new OrderbyLogicalOperator(select_stmt->query_fields(), select_stmt->group_fields(), select_stmt->asc()));
  }

  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator());
  unique_ptr<LogicalOperator> root_oper(nullptr);
  // group-by 操作以group算子为根
  if (select_stmt->group_fields().size() != 0) {
    root_oper = unique_ptr<LogicalOperator>(new GroupbyLogicalOperator(select_stmt->aggr_list(),
        select_stmt->group_fields(),
        select_stmt->having_left(),
        select_stmt->having_right(),
        select_stmt->having_opts()));
  } else if (select_stmt->is_aggregate()) {
    // 聚合函数以聚合算子为根
    root_oper = unique_ptr<LogicalOperator> (new AggrFuncLogicalOperator(std::move(select_stmt->expression()), std::move(select_stmt->aggr_list())));
  } else {
    // 普通表达式以表达式算子为根
    root_oper = unique_ptr<LogicalOperator> (new ExpressionLogicalOperator(std::move(select_stmt->expression())));
  }

  if (predicate_oper) {
    if (table_oper) {
      PredicateLogicalOperator* tmp = static_cast<PredicateLogicalOperator*>(predicate_oper.get());
      tmp->set_table_get(std::move(table_oper));
    }
  }

  if (orderby_oper) {
    if (predicate_oper) {
      orderby_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        orderby_oper->add_child(std::move(table_oper));
      } 
    }
    root_oper->add_child(std::move(orderby_oper));
  } else {
    if (predicate_oper) {
      root_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        root_oper->add_child(std::move(table_oper));
      }
    }
  }
  project_oper->add_child(std::move(root_oper));

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  FilterObj filter_obj_left, filter_obj_right;
  unique_ptr<Expression> left, right;
  std::vector<FieldExpr> left_expressions_sub_query_comp;
  std::vector<CompOp> compop_sub_query_comp;
  std::vector<int8_t> both_is_sub_query;
  std::vector<std::unique_ptr<LogicalOperator>> sub_querys;
  RC rc;
  for (FilterUnit *filter_unit : filter_units) {
    if (filter_unit->left_is_sub_query()) {
      std::unique_ptr<SelectStmt> left_stmt = std::unique_ptr<SelectStmt>(filter_unit->left_query());
      std::unique_ptr<LogicalOperator> left_query(nullptr);
      rc = create_plan(left_stmt.get(), left_query);
      if(rc != RC::SUCCESS){
        LOG_WARN("unable to generate right sub query's logical operator, error code = %d", (int)rc);
        return rc;
      }
      sub_querys.push_back(std::move(left_query));
    } else {
      filter_obj_left = filter_unit->left();
      left = std::move(filter_obj_left.expression);
    }
    
    if(filter_unit->right_is_sub_query()) {
      compop_sub_query_comp.push_back(filter_unit->comp());
      std::unique_ptr<SelectStmt> right_stmt = std::unique_ptr<SelectStmt>(filter_unit->right_query());
      std::unique_ptr<LogicalOperator> right_query(nullptr);
      rc = create_plan(right_stmt.get(), right_query);
      if(rc != RC::SUCCESS){
        LOG_WARN("unable to generate right sub query's logical operator, error code = %d", (int)rc);
        return rc;
      }
      sub_querys.push_back(std::move(right_query));
      both_is_sub_query.push_back(filter_unit->left_is_sub_query());
      if(filter_unit->left_is_sub_query()) continue;
      if (filter_unit->comp() != EXIST && filter_unit->comp() != NOT_EXIST) {
        if(left->type() != ExprType::FIELD) {
        LOG_WARN("left expression should be fieldexpr in condition stmt with sub query");
        return RC::INVALID_ARGUMENT;
        }
        FieldExpr* left_field = static_cast<FieldExpr*>(left.get());
        left_expressions_sub_query_comp.push_back(FieldExpr(left_field->field()));
      } else {
        left_expressions_sub_query_comp.push_back(Field());
      }

      
    } else if(!filter_unit->right_is_value_list()){
      FilterObj filter_obj_right = filter_unit->right();
      unique_ptr<Expression> right(std::move(filter_obj_right.expression));

      ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
      cmp_exprs.emplace_back(cmp_expr);
      
    } else {
      std::unique_ptr<LogicalOperator> val_list(new ValueListLogicalOperator(filter_unit->value_list()));
      sub_querys.push_back(std::move(val_list));
      compop_sub_query_comp.push_back(filter_unit->comp());
      both_is_sub_query.push_back(filter_unit->left_is_sub_query());
      if(left->type() != ExprType::FIELD) {
        LOG_WARN("left expression should be fieldexpr in condition stmt with sub query");
        return RC::INVALID_ARGUMENT;
      }
      FieldExpr* left_field = static_cast<FieldExpr*>(left.get());
      left_expressions_sub_query_comp.push_back(FieldExpr(left_field->field()));
    }
    
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty() || !sub_querys.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(filter_stmt->get_conj() ? ConjunctionExpr::Type::OR : ConjunctionExpr::Type::AND, cmp_exprs));
    if(!sub_querys.empty()){
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr), left_expressions_sub_query_comp, compop_sub_query_comp, both_is_sub_query, filter_stmt->get_conj()));
      predicate_oper->add_child(std::unique_ptr<LogicalOperator>(nullptr));
      for(auto &sub_query : sub_querys) {
        predicate_oper->add_child(std::move(sub_query));
      }
    } else {
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

// TODO
RC LogicalPlanGenerator::create_plan(
    UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = 0; i < update_stmt->value_amount(); ++i) {
    const FieldMeta *field_meta = table->table_meta().field(update_stmt->fields()[i].c_str());
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::vector<std::string>    update_fields(update_stmt->fields(), update_stmt->fields() + update_stmt->value_amount());
  std::vector<Value>          update_values(update_stmt->values(), update_stmt->values() + update_stmt->value_amount());
  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(table, std::move(update_fields), std::move(update_values)));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  // add sub-select
  for (SelectStmt *sub_stmt : *update_stmt->sub_select()) {
    unique_ptr<LogicalOperator> sub_select_oper;
    RC rc = create_plan(sub_stmt, sub_select_oper);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    update_oper->add_child(std::move(sub_select_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(CreateSelectStmt *create_select_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *select_stmt = create_select_stmt->select_stmt();
  unique_ptr<LogicalOperator> select_oper;
  RC rc = create(select_stmt, select_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(
      new CreateSelectLogicalOperator(create_select_stmt->create_table_stmt(), create_select_stmt->db()));
  logical_operator->add_child(std::move(select_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
