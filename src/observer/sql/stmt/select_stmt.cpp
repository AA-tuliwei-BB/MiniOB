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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  std::unique_ptr<std::unordered_map<std::string, Table*>> table_map = std::unique_ptr<std::unordered_map<std::string, Table*>>(new std::unordered_map<std::string, Table*>);
  RC rc = create_sub_query(db, select_sql, stmt, table_map.get());
  return rc;
}

RC SelectStmt::create_sub_query(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, std::unordered_map<std::string, Table *>* father_table_map)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map(*father_table_map);
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < select_sql.relations.size() / 2; i++) {
    const char *table_name = select_sql.relations[i * 2 + 1].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    if(!select_sql.relations[i * 2].empty()) {
      if(table_map.find(select_sql.relations[i * 2]) == table_map.end() || father_table_map->find(select_sql.relations[i * 2]) != father_table_map->end()){
        table_map[select_sql.relations[i * 2]] = table;
      } else {
        LOG_ERROR("name %s refers to multiple table", select_sql.relations[i * 2].c_str());
        return RC::INVALID_ARGUMENT;
      }
    } else {
      if(table_map.find(select_sql.relations[i * 2 + 1]) == table_map.end() ||father_table_map->find(select_sql.relations[i * 2 + 1]) != father_table_map->end()){
        table_map[select_sql.relations[i * 2 + 1]] = table;
      } else {
        LOG_ERROR("name %s refers to multiple table", select_sql.relations[i * 2 + 1].c_str());
        return RC::INVALID_ARGUMENT;
      }
    }
  }
  std::vector<std::unique_ptr<JoinStmt>> joins;
  int from_size = tables.size();
  for(auto &it : select_sql.joins){
    JoinStmt* tmp;
    if((rc = JoinStmt::create(db, *it, tables, table_map, tmp)) != RC::SUCCESS){
      LOG_WARN("fail to create join stmt");
      return rc;
    }
    joins.push_back(std::unique_ptr<JoinStmt>(tmp));
  }

  // collect query fields in `select` statement
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }
  std::vector<Field> query_fields;
  std::vector<int> query_fields_size;
  std::vector<std::unique_ptr<Expression>> expressions;
  std::vector<AggrFuncExpr*> aggr_list;
  std::vector<std::string> alias, field_name;
  bool is_aggregate = (select_sql.expressions.size() != 0) ? select_sql.expressions[0]->is_aggregate : false;
  if(select_sql.group_by_fields.empty()) {
    for (int i = static_cast<int>(select_sql.expressions.size()) - 1; i >= 0; i--) {
      ExprSqlNode &cur = *select_sql.expressions[i];
      if(cur.is_aggregate ^ is_aggregate){
        LOG_WARN("mixed aggregate expression and non-aggregate type in one select statement.");
        return RC::INVALID_ARGUMENT;
      }
      if(cur.need_extract){
        if(cur.have_alias) {
          LOG_WARN("star expression shouldn't have alias");
          return RC::INVALID_ARGUMENT;
        }
        int last_query_field = query_fields.size();
        if(cur.get_type() == ExprSqlNode::Type::REL_ATTR_EXPR)
        {
          RelAttrSqlNode &rel = *static_cast<RelAttrSqlNode*>(&cur);
          if(rel.relation_name.empty()) {
            for (Table *table : tables) {
              wildcard_fields(table, query_fields);
            }
          } else {
            if(table_map.find(rel.relation_name) != table_map.end()) {
              Table* cur_table = table_map[rel.relation_name];
              wildcard_fields(cur_table, query_fields);

            } else {
              LOG_WARN("unable to find table %s", rel.relation_name);
              return RC::SCHEMA_TABLE_NOT_EXIST;
            }
          }
        } else {
          LOG_WARN("star expression should be on the top");
          return RC::INVALID_ARGUMENT;
        }
        int cur_query_field = query_fields.size();
        for(int j = last_query_field; j < cur_query_field; ++j){
          field_name.push_back(query_fields[j].field_name());
          std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), &query_fields[j], &aggr_list);
          if(build_result.second != RC::SUCCESS){
            LOG_WARN("fail to build expression. error code = %d.", build_result.second);
            return build_result.second;
          }
          
          ExprType expressionType = build_result.first->type();
          alias.push_back(cur.name);
          expressions.push_back(std::move(build_result.first));
          query_fields_size.push_back(j + 1);
        }
      } else {
        if(cur.get_type() == ExprSqlNode::Type::REL_ATTR_EXPR && !cur.have_alias) {
          RelAttrSqlNode &rel = *static_cast<RelAttrSqlNode*>(&cur);
          field_name.push_back(rel.attribute_name);
        } else field_name.push_back(cur.name);
        std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), nullptr, &aggr_list);
        if(build_result.second != RC::SUCCESS){
          LOG_WARN("fail to build expression. error code = %d.", build_result.second);
          return build_result.second;
        }
        ExprType expressionType = build_result.first->type();
        if(expressionType != ExprType::FIELD && expressionType != ExprType::FUNCTION && expressionType != ExprType::STAR && expressionType != ExprType::AGGRFUNC && expressionType != ExprType::ARITHMETIC && expressionType != ExprType::VALUE){
          LOG_WARN("invalid expression type(id = %d) in select statement.", static_cast<int>(expressionType));
          return RC::INVALID_ARGUMENT;
        }
        
        
        alias.push_back(cur.name);
        expressions.push_back(std::move(build_result.first));
        query_fields_size.push_back(query_fields.size());
      }
      
    }

    LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());
  } else {
    for (int i = static_cast<int>(select_sql.expressions.size()) - 1; i >= 0; i--) {
      ExprSqlNode &cur = *select_sql.expressions[i];
      if(cur.need_extract){
        if(cur.have_alias) {
          LOG_WARN("star expression shouldn't have alias");
          return RC::INVALID_ARGUMENT;
        }
        int last_query_field = query_fields.size();
        if(cur.get_type() == ExprSqlNode::Type::REL_ATTR_EXPR)
        {
          RelAttrSqlNode &rel = *static_cast<RelAttrSqlNode*>(&cur);
          if(rel.relation_name.empty()) {
            for (Table *table : tables) {
              wildcard_fields(table, query_fields);
            }
          } else {
            if(table_map.find(rel.relation_name) != table_map.end()) {
              Table* cur_table = table_map[rel.relation_name];
              wildcard_fields(cur_table, query_fields);
            } else {
              LOG_WARN("unable to find table %s", rel.relation_name);
              return RC::SCHEMA_TABLE_NOT_EXIST;
            }
          }
        } else for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
        int cur_query_field = query_fields.size();
        for(int j = last_query_field; j < cur_query_field; ++j){
          std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), &query_fields[j], nullptr);
          if(build_result.second != RC::SUCCESS){
            LOG_WARN("fail to build expression. error code = %d.", build_result.second);
            return build_result.second;
          }
          
          if(build_result.first->type() != ExprType::AGGRFUNC) {
            AggrFuncExpr* tmp = new AggrFuncExpr(AggrFuncExpr::Type::CONST_FIELD, std::move(build_result.first));
            aggr_list.push_back(tmp);
          } else aggr_list.push_back(static_cast<AggrFuncExpr*>(build_result.first.get()));
          ExprType expressionType = build_result.first->type();
          alias.push_back(cur.name);
          expressions.push_back(std::move(build_result.first));
          query_fields_size.push_back(j + 1);
        }
      }  else {
        std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), nullptr, nullptr);
        if(build_result.second != RC::SUCCESS){
          LOG_WARN("fail to build expression. error code = %d.", build_result.second);
          return build_result.second;
        }
        ExprType expressionType = build_result.first->type();
        
        if(build_result.first->type() != ExprType::AGGRFUNC) {
            AggrFuncExpr* tmp = new AggrFuncExpr(AggrFuncExpr::Type::CONST_FIELD, std::move(build_result.first));
            aggr_list.push_back(tmp);
        } else aggr_list.push_back(static_cast<AggrFuncExpr*>(build_result.first.get()));
        if(expressionType != ExprType::FIELD && expressionType != ExprType::FUNCTION && expressionType != ExprType::STAR && expressionType != ExprType::AGGRFUNC && expressionType != ExprType::ARITHMETIC && expressionType != ExprType::VALUE){
          LOG_WARN("invalid expression type(id = %d) in select statement.", static_cast<int>(expressionType));
          return RC::INVALID_ARGUMENT;
        }
        
        alias.push_back(cur.name);
        expressions.push_back(std::move(build_result.first));
        query_fields_size.push_back(query_fields.size());
      }

    }
  }
  

  // create filter statement in `where` statement

  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions,
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  //create order-by statement
  std::vector<Field> orders_fields;
  std::vector<bool> asc;
  for (auto &it : select_sql.orders) {
    OrderBySqlNode *cur = it.get();
    std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(cur->attrs.get(), tables, table_map, query_fields, std::string(db->name()), nullptr, nullptr);
    if(build_result.second != RC::SUCCESS){
      LOG_WARN("fail to build expression. error code = %d.", build_result.second);
      return build_result.second;
    }
    if(build_result.first->type() == ExprType::FIELD){
      FieldExpr* tmp = static_cast<FieldExpr*>(build_result.first.get());
      orders_fields.push_back(tmp->field());
      asc.push_back(cur->isAscending);
    } else {
      LOG_WARN("non-field type in order-by isn't supported now");
      return RC::UNIMPLENMENT;
    }
  }

  std::vector<AggrFuncExpr*> having_left; 
  std::vector<AggrFuncExpr*> having_right; 
  std::vector<Field> group_fields;
  std::vector<CompOp> having_opts;
  //create group-by statement
  if (!select_sql.group_by_fields.empty()) {
    for(auto &it : select_sql.group_by_fields) {
      std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(it.get(), tables, table_map, query_fields, std::string(db->name()), nullptr, nullptr);
      if(build_result.second != RC::SUCCESS){
        LOG_WARN("fail to build expression. error code = %d.", build_result.second);
        return build_result.second;
      }

      if (build_result.first->type() == ExprType::FIELD) {
        FieldExpr* tmp = static_cast<FieldExpr*>(build_result.first.get());
        group_fields.push_back(tmp->field());
      } else {
        LOG_WARN("non-field type in group-by isn't supported now");
        return RC::UNIMPLENMENT;
      }
    }
  }

  //create having statement
  if(!select_sql.having_conditions.empty()) {
    for(auto &it : select_sql.having_conditions) {
      having_opts.push_back(it->comp);
      std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(it->left_expression.get(), tables, table_map, query_fields, std::string(db->name()), nullptr, nullptr);
      if(build_result.second != RC::SUCCESS){
        LOG_WARN("fail to build expression. error code = %d.", build_result.second);
        return build_result.second;
      }
      if(build_result.first->type() != ExprType::AGGRFUNC) {
        AggrFuncExpr* tmp = new AggrFuncExpr(AggrFuncExpr::Type::CONST_FIELD, std::move(build_result.first));
        having_left.push_back(tmp);
      } else having_left.push_back(static_cast<AggrFuncExpr*>(build_result.first.release()));

      build_result = build_expression(it->right_expression.get(), tables, table_map, query_fields, std::string(db->name()), nullptr, nullptr);
      if(build_result.second != RC::SUCCESS){
        LOG_WARN("fail to build expression. error code = %d.", build_result.second);
        return build_result.second;
      }
      if(build_result.first->type() != ExprType::AGGRFUNC) {
        AggrFuncExpr* tmp = new AggrFuncExpr(AggrFuncExpr::Type::CONST_FIELD, std::move(build_result.first));
        having_right.push_back(tmp);
      } else having_right.push_back(static_cast<AggrFuncExpr*>(build_result.first.release()));
    }
  }
  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->is_aggregate_ = is_aggregate;
  select_stmt->expression_type = !group_fields.empty() || expressions.empty() ? UNDEFINED : expressions[0]->value_type();
  select_stmt->expressions_.swap(expressions);
  select_stmt->query_fields_size_.swap(query_fields_size);
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->alias_.swap(alias);
  select_stmt->aggr_list_.swap(aggr_list);
  select_stmt->joins_.swap(joins);
  select_stmt->table_size_in_from = from_size;
  select_stmt->orders_fields_.swap(orders_fields);
  select_stmt->asc_.swap(asc);
  select_stmt->having_left_.swap(having_left);
  select_stmt->having_right_.swap(having_right);
  select_stmt->having_opts_.swap(having_opts);
  select_stmt->group_fields_.swap(group_fields);
  select_stmt->field_name_.swap(field_name);
  select_stmt->filter_stmt_ = filter_stmt;
  
  stmt = select_stmt;
  return RC::SUCCESS;
}