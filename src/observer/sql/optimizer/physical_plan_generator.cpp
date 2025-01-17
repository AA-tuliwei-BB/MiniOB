/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/12/14.
//

#include <utility>

#include "sql/optimizer/physical_plan_generator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/table_scan_physical_operator.h"
#include "sql/operator/index_scan_physical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/predicate_physical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/insert_physical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/delete_physical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/update_physical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/explain_physical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/join_physical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/calc_physical_operator.h"
#include "sql/operator/aggrfunc_logical_operator.h"
#include "sql/operator/aggrfunc_physical_operator.h"
#include "sql/operator/expression_logical_operator.h"
#include "sql/operator/expression_physical_operator.h"
#include "sql/operator/orderby_logical_operator.h"
#include "sql/operator/orderby_physical_operator.h"
#include "sql/operator/groupby_logical_operator.h"
#include "sql/operator/groupby_physical_operator.h"
#include "sql/operator/value_list_logical_operator.h"
#include "sql/operator/value_list_physical_operator.h"
#include "sql/operator/create_select_logical_operator.h"
#include "sql/operator/create_select_physical_operator.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "physical_plan_generator.h"

using namespace std;

RC PhysicalPlanGenerator::create(LogicalOperator &logical_operator, unique_ptr<PhysicalOperator> &oper)
{
  RC rc = RC::SUCCESS;

  switch (logical_operator.type()) {
    case LogicalOperatorType::CALC: {
      return create_plan(static_cast<CalcLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::TABLE_GET: {
      return create_plan(static_cast<TableGetLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::PREDICATE: {
      return create_plan(static_cast<PredicateLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::PROJECTION: {
      return create_plan(static_cast<ProjectLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::INSERT: {
      return create_plan(static_cast<InsertLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::DELETE: {
      return create_plan(static_cast<DeleteLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::UPDATE: {
      return create_plan(static_cast<UpdateLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::EXPLAIN: {
      return create_plan(static_cast<ExplainLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::JOIN: {
      return create_plan(static_cast<JoinLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::AGGRFUNC: {
      return create_plan(static_cast<AggrFuncLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::EXPRESSION: {
      return create_plan(static_cast<ExpressionLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::ORDERBY: {
      return create_plan(static_cast<OrderbyLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::GROUPBY: {
      return create_plan(static_cast<GroupbyLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::VALUELIST: {
      return create_plan(static_cast<ValueListLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::CREATE_SELECT: {
      return create_plan(static_cast<CreateSelectLogicalOperator &>(logical_operator), oper);
    } break;

    default: {
      return RC::INVALID_ARGUMENT;
    }
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(TableGetLogicalOperator &table_get_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<Expression>> &predicates = table_get_oper.predicates();
  // 看看是否有可以用于索引查找的表达式
  Table *table = table_get_oper.table();

  // Index *index = nullptr;
  // ValueExpr *value_expr = nullptr;
  // for (auto &expr : predicates) {
  //   if (expr->type() == ExprType::COMPARISON) {
  //     auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());
  //     // 简单处理，就找等值查询
  //     if (comparison_expr->comp() != EQUAL_TO) {
  //       continue;
  //     }

  //     unique_ptr<Expression> &left_expr = comparison_expr->left();
  //     unique_ptr<Expression> &right_expr = comparison_expr->right();
  //     // 左右比较的一边最少是一个值
  //     if (left_expr->type() != ExprType::VALUE && right_expr->type() != ExprType::VALUE) {
  //       continue;
  //     }

  //     FieldExpr *field_expr = nullptr;
  //     if (left_expr->type() == ExprType::FIELD) {
  //       ASSERT(right_expr->type() == ExprType::VALUE, "right expr should be a value expr while left is field expr");
  //       field_expr = static_cast<FieldExpr *>(left_expr.get());
  //       value_expr = static_cast<ValueExpr *>(right_expr.get());
  //     } else if (right_expr->type() == ExprType::FIELD) {
  //       ASSERT(left_expr->type() == ExprType::VALUE, "left expr should be a value expr while right is a field expr");
  //       field_expr = static_cast<FieldExpr *>(right_expr.get());
  //       value_expr = static_cast<ValueExpr *>(left_expr.get());
  //     }

  //     if (field_expr == nullptr) {
  //       continue;
  //     }

  //     const Field &field = field_expr->field();
  //     index = table->find_index_by_field(field.field_name());
  //     if (nullptr != index) {
  //       break;
  //     }
  //   }
  // }

  // if (index != nullptr) {
  //   ASSERT(value_expr != nullptr, "got an index but value expr is null ?");

  //   const Value &value = value_expr->get_value();
  //   IndexScanPhysicalOperator *index_scan_oper = new IndexScanPhysicalOperator(
  //         table, index, table_get_oper.readonly(), 
  //         &value, true /*left_inclusive*/, 
  //         &value, true /*right_inclusive*/);
          
  //   index_scan_oper->set_predicates(std::move(predicates));
  //   oper = unique_ptr<PhysicalOperator>(index_scan_oper);
  //   LOG_TRACE("use index scan");
  // } else {
    auto table_scan_oper = new TableScanPhysicalOperator(table, table_get_oper.readonly());
    table_scan_oper->set_predicates(std::move(predicates));
    oper = unique_ptr<PhysicalOperator>(table_scan_oper);
    LOG_TRACE("use table scan");
  // }

  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(PredicateLogicalOperator &pred_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &children_opers = pred_oper.children();
  ASSERT(children_opers.size() >= 1, "predicate logical operator's sub oper number should be more than 1");

  std::vector<unique_ptr<PhysicalOperator>> child_phy_opers;
  for (auto &it : children_opers) {
    LogicalOperator *child_oper = it.get();
    unique_ptr<PhysicalOperator> child_phy_oper;
    RC rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create child operator of predicate operator. rc=%s", strrc(rc));
      return rc;
    }
    child_phy_opers.emplace_back(std::move(child_phy_oper));
  }

  vector<unique_ptr<Expression>> &expressions = pred_oper.expressions();
  ASSERT(expressions.size() == 1, "predicate logical operator's children should be 1");

  unique_ptr<Expression> expression = std::move(expressions.front());
  if (pred_oper.has_sub_query()) {
    oper = unique_ptr<PhysicalOperator>(new PredicatePhysicalOperator(std::move(expression),
        pred_oper.sub_query_fields(),
        pred_oper.sub_query_opts(),
        pred_oper.both_is_sub_query(),
        pred_oper.sub_query_connector()));
  } else {
    oper = unique_ptr<PhysicalOperator>(new PredicatePhysicalOperator(std::move(expression)));
  }
  for (auto &child_phy_oper : child_phy_opers) {
    oper->add_child(std::move(child_phy_oper));
  }
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(ProjectLogicalOperator &project_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = project_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  ProjectPhysicalOperator *project_operator = new ProjectPhysicalOperator();
  // project_operator->add_expressions(std::move(project_oper.expressions()));

  if (child_phy_oper) {
    project_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(project_operator);

  LOG_TRACE("create a project physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(InsertLogicalOperator &insert_oper, unique_ptr<PhysicalOperator> &oper)
{
  Table *table = insert_oper.table();
  vector<Value> &values = insert_oper.values();
  InsertPhysicalOperator *insert_phy_oper = new InsertPhysicalOperator(table, std::move(values));
  oper.reset(insert_phy_oper);
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(DeleteLogicalOperator &delete_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = delete_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new DeletePhysicalOperator(delete_oper.table()));

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(UpdateLogicalOperator &update_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = update_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;
  std::vector<unique_ptr<PhysicalOperator>> child_physical_opers;

  RC rc = RC::SUCCESS;
  for (auto &child_oper_it : child_opers) {
    LogicalOperator *child_oper = child_oper_it.get();

    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
    if (child_physical_oper) {
      child_physical_opers.emplace_back(std::move(child_physical_oper));
    }
  }

  std::vector<std::string> &fields = update_oper.fields();
  std::vector<Value>       &values = update_oper.values();

  oper = unique_ptr<PhysicalOperator>(
      new UpdatePhysicalOperator(update_oper.table(), std::move(fields), std::move(values)));

  for (auto &child_oper : child_physical_opers) {
    oper->add_child(std::move(child_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ExplainLogicalOperator &explain_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = explain_oper.children();

  RC rc = RC::SUCCESS;
  unique_ptr<PhysicalOperator> explain_physical_oper(new ExplainPhysicalOperator);
  for (unique_ptr<LogicalOperator> &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create child physical operator. rc=%s", strrc(rc));
      return rc;
    }

    explain_physical_oper->add_child(std::move(child_physical_oper));
  }

  oper = std::move(explain_physical_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(JoinLogicalOperator &join_oper, unique_ptr<PhysicalOperator> &oper)
{
  RC rc = RC::SUCCESS;

  vector<unique_ptr<LogicalOperator>> &child_opers = join_oper.children();
  if (child_opers.size() != 2) {
    LOG_WARN("join operator should have 2 children, but have %d", child_opers.size());
    return RC::INTERNAL;
  }

  unique_ptr<PhysicalOperator> join_physical_oper(new NestedLoopJoinPhysicalOperator);
  for (auto &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical child oper. rc=%s", strrc(rc));
      return rc;
    }

    join_physical_oper->add_child(std::move(child_physical_oper));
  }

  oper = std::move(join_physical_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(CalcLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  RC rc = RC::SUCCESS;
  CalcPhysicalOperator *calc_oper = new CalcPhysicalOperator(std::move(logical_oper.expressions()));
  oper.reset(calc_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(AggrFuncLogicalOperator &aggrfunc_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = aggrfunc_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new AggrFuncPhysicalOperator(std::move(aggrfunc_oper.expressions()), std::move(aggrfunc_oper.aggr_list())));

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ExpressionLogicalOperator &expr_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = expr_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  ExpressionPhysicalOperator *expression_operator = new ExpressionPhysicalOperator(std::move(expr_oper.expressions()));

  if (child_phy_oper) {
    expression_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(expression_operator);

  LOG_TRACE("create a expression physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(OrderbyLogicalOperator &order_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = order_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  OrderbyPhysicalOperator *orderby_operator = new OrderbyPhysicalOperator(
      std::move(order_oper.fields()), std::move(order_oper.orders()), std::move(order_oper.asc()));

  if (child_phy_oper) {
    orderby_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(orderby_operator);

  LOG_TRACE("create a orderby physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(GroupbyLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = logical_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create group-by logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  GroupbyPhysicalOperator *groupby_operator = new GroupbyPhysicalOperator(
      logical_oper.exprs(), logical_oper.fields(), logical_oper.left(), logical_oper.right(), logical_oper.opts());

  if (child_phy_oper) {
    groupby_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(groupby_operator);

  LOG_TRACE("create a group-by physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ValueListLogicalOperator &value_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  ValueListPhysicalOperator *phy_oper = new ValueListPhysicalOperator(std::move(value_oper.values()));
  oper = unique_ptr<PhysicalOperator>(phy_oper);
  LOG_TRACE("create a value list physical operator");
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(
    CreateSelectLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = logical_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create create-select logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  CreateSelectPhysicalOperator *create_select_operator =
      new CreateSelectPhysicalOperator(logical_oper.create_table_stmt(), logical_oper.db());

  if (child_phy_oper) {
    create_select_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(create_select_operator);

  LOG_TRACE("create a create-select physical operator");
  return rc;
}
