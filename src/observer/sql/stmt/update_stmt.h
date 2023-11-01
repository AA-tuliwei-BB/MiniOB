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

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class FieldMeta;
class FilterStmt;
class SelectStmt;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, const std::string *fields, const Value *values, int value_amount, FilterStmt *filter_stmt, std::vector<SelectStmt*>* sub_select = nullptr);

public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);

  StmtType type() const override
  {
    return StmtType::UPDATE;
  }

public:
  Table *table() const
  {
    return table_;
  }
  const std::string *fields() const
  {
    return fields_;
  }
  const Value *values() const
  {
    return values_;
  }
  int value_amount() const
  {
    return value_amount_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  std::vector<SelectStmt*>* sub_select() const
  {
    return sub_select_;
  }

private:
  Table *table_ = nullptr;
  const std::string *fields_ = nullptr;
  const Value *values_ = nullptr;
  /* 如果Value是undefined，取sub_select_的下一条stmt为set参数，否则取values_中Value为参数 */
  std::vector<SelectStmt*>* sub_select_ = nullptr;
  int value_amount_ = 0;
  FilterStmt *filter_stmt_ = nullptr;
};
