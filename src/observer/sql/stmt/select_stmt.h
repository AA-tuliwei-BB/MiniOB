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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/stmt/join_stmt.h"


class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);
  static RC create_sub_query(Db* db, SelectSqlNode &select_sql, Stmt* &stmt, std::unordered_map<std::string, Table *>* father_table_map);

public:
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<Field> &query_fields() const
  {
    return query_fields_;
  }
  const std::vector<int> &query_fields_size() const
  {
    return query_fields_size_;
  }
  const std::vector<std::string> &alias() const
  {
    return alias_;
  }
  const AttrType value_type() const
  {
    return expression_type;
  }
  std::vector<AggrFuncExpr*> &aggr_list()
  {
    return aggr_list_;
  }
  std::vector<std::unique_ptr<Expression>> &expression()
  {
    return expressions_;
  }
  int from_size() const {
    return table_size_in_from;
  }
  std::vector<std::unique_ptr<JoinStmt>> &joins(){
    return joins_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  bool is_aggregate() const
  {
    return is_aggregate_;
  }
  const std::vector<Field>& orders_fields() const
  {
    return orders_fields_;
  }
  const std::vector<bool>& asc() const
  {
    return asc_;
  }

  const std::vector<std::string>& field_name() const
  {
    return field_name_;
  }

  std::vector<AggrFuncExpr *> &having_left() { return having_left_; }
  std::vector<AggrFuncExpr *> &having_right() { return having_right_; }
  std::vector<Field>          &group_fields() { return group_fields_; }
  std::vector<CompOp>         &having_opts() { return having_opts_; }

private:
  bool is_aggregate_;
  std::vector<std::string> alias_;
  std::vector<std::string> field_name_;
  std::vector<std::unique_ptr<Expression>> expressions_;
  std::vector<Field> query_fields_;
  std::vector<int> query_fields_size_;
  std::vector<Table *> tables_;
  int table_size_in_from;
  AttrType expression_type;
  std::vector<AggrFuncExpr*> aggr_list_; 
  FilterStmt *filter_stmt_ = nullptr;

  // having
  std::vector<AggrFuncExpr*> having_left_; 
  std::vector<AggrFuncExpr*> having_right_; 
  std::vector<Field> group_fields_;
  std::vector<CompOp> having_opts_;

  std::vector<std::unique_ptr<JoinStmt>> joins_;
  std::vector<Field> orders_fields_;
  std::vector<bool> asc_; // 是否升序
  enum class Type{
    IN,
    EXIST,
    NOT_IN,
    NOT_EXIST
  };
  Type type_;
};