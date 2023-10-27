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
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
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
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }
  std::vector<Field> query_fields;
  std::vector<std::unique_ptr<Expression>> expressions;
  std::vector<std::string> alias;
  bool is_aggregate;
  for (int i = static_cast<int>(select_sql.expressions.size()) - 1; i >= 0; i--) {
    ExprSqlNode &cur = *select_sql.expressions[i];
    if(cur.need_extract){
      int last_query_field = query_fields.size();
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }
      int cur_query_field = query_fields.size();
      for(int j = last_query_field; j < cur_query_field; ++j){
        std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), &query_fields[j]);
        if(build_result.second != RC::SUCCESS){
          LOG_WARN("fail to build expression. error code = %d.", build_result.second);
          return build_result.second;
        }
        
        ExprType expressionType = build_result.first->type();
        if(i != static_cast<int>(select_sql.expressions.size()) - 1){
          if(is_aggregate ^ (expressionType == ExprType::AGGRFUNC)){
            LOG_WARN("mixed expression type(id = %d) in select statement.", static_cast<int>(expressionType));
          return RC::INVALID_ARGUMENT;
          }
        }else is_aggregate = (expressionType == ExprType::AGGRFUNC);
        alias.push_back(cur.name);
        expressions.push_back(std::move(build_result.first));
      }
    }else {
      std::pair<std::unique_ptr<Expression>, RC> build_result = build_expression(&cur, tables, table_map, query_fields, std::string(db->name()), nullptr);
      if(build_result.second != RC::SUCCESS){
        LOG_WARN("fail to build expression. error code = %d.", build_result.second);
        return build_result.second;
      }
      ExprType expressionType = build_result.first->type();
      if(expressionType != ExprType::FIELD && expressionType != ExprType::FUNCTION && expressionType != ExprType::STAR && expressionType != ExprType::AGGRFUNC && expressionType != ExprType::ARITHMETIC){
        LOG_WARN("invalid expression type(id = %d) in select statement.", static_cast<int>(expressionType));
        return RC::INVALID_ARGUMENT;
      }
      if(i != static_cast<int>(select_sql.expressions.size()) - 1){
        if(is_aggregate ^ (expressionType == ExprType::AGGRFUNC)){
          LOG_WARN("mixed expression type(id = %d) in select statement.", static_cast<int>(expressionType));
        return RC::INVALID_ARGUMENT;
        }
      }else is_aggregate = (expressionType == ExprType::AGGRFUNC);

      
      alias.push_back(cur.name);
      expressions.push_back(std::move(build_result.first));
    }
    
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions,
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->is_aggregate_ = expressions[0]->type() == ExprType::AGGRFUNC;
  select_stmt->expressions_.swap(expressions);
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->alias_.swap(alias);
  select_stmt->filter_stmt_ = filter_stmt;
  
  stmt = select_stmt;
  return RC::SUCCESS;
}

