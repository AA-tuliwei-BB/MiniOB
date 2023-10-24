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

struct FilterObj 
{
  bool is_attr;
  std::unique_ptr<Expression> expression;

  bool init(std::unique_ptr<Expression> expr){
    switch (expr->type())
    {
    case ExprType::AGGRFUNC:
    case ExprType::ARITHMETIC:
    case ExprType::CAST:
    case ExprType::VALUE:
      /* code */
      is_attr = false;
      break;
    case ExprType::FIELD:
    case ExprType::FUNCTION:
      is_attr = true;
    default:
      return false;
    }
    expression = std::move(expr);
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

private:
  CompOp comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
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

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::vector<ConditionSqlNode *>& conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      ConditionSqlNode &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};
