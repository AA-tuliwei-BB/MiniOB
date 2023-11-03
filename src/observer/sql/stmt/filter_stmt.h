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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;
class SelectStmt;

struct FilterObj 
{
  bool is_attr;
  std::unique_ptr<Expression> expression;
  FilterObj():is_attr(false), expression(nullptr) {}
  FilterObj(std::unique_ptr<Expression> expr){
    expression = std::move(expr);
    is_attr = expression->is_attr();
  }

  bool init(std::unique_ptr<Expression> expr){
    expression = std::move(expr);
    is_attr = expression->is_attr();
    return true;
  }
  
};

class FilterUnit 
{
public:
  FilterUnit() = default;
  FilterUnit(FilterObj &l, FilterObj &r){
    left_ = std::move(l);
    right_ = std::move(r);
  }
  
  FilterUnit(FilterObj &l, SelectStmt *r){
    left_ = std::move(l);
    right_sub_query_ = r;
    right_is_sub_query_ = true;
  }

  FilterUnit(SelectStmt *l, SelectStmt *r){
    left_sub_query_ = l;
    right_sub_query_ = r;
    left_is_sub_query_ = true;
    right_is_sub_query_ = true;
  }
  
  FilterUnit(FilterObj &l, std::vector<Value>& val) {
    value_list_.swap(val);
    left_ = std::move(l);
    right_is_value_list_ = true;
  }
  ~FilterUnit() = default;

  void set_comp(CompOp comp)
  {
    comp_ = comp;
  }

  CompOp comp() const
  {
    return comp_;
  }

  // void set_left(FilterObj &obj)
  // {
  //   left_ = obj;
  // }
  // void set_right(FilterObj &obj)
  // {
  //   right_ = obj;
  // }

  FilterObj left()
  {
    return std::move(left_);
  }
  FilterObj right()
  {
    return std::move(right_);
  }
  SelectStmt* left_query()
  {
    return left_sub_query_;
  }
  bool left_is_sub_query(){
    return left_is_sub_query_;
  }
  SelectStmt* right_query()
  {
    return right_sub_query_;
  }
  bool right_is_sub_query(){
    return right_is_sub_query_;
  }
  std::vector<Value>& value_list()
  {
    return value_list_;
  }
  bool right_is_value_list(){
    return right_is_value_list_;
  }

private:
  CompOp comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
  bool left_is_sub_query_ = false;
  SelectStmt* left_sub_query_;
  bool right_is_sub_query_ = false;
  SelectStmt* right_sub_query_;
  bool right_is_value_list_ = false;
  std::vector<Value> value_list_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt 
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

  void set_conj(bool conj) {  conjuction_type = conj;  }

  bool get_conj() {  return conjuction_type;  }
public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::vector<ConditionSqlNode *>& conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      ConditionSqlNode &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_;  // 有and/or两种关系，见conjuction_type
  bool conjuction_type;
};
