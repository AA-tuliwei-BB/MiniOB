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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"

/**
 * @brief 谓词/过滤逻辑算子
 * @ingroup LogicalOperator
 */
class PredicateLogicalOperator : public LogicalOperator 
{
public:
  PredicateLogicalOperator(std::unique_ptr<Expression> expression);
  PredicateLogicalOperator(std::unique_ptr<Expression> expr, std::vector<FieldExpr> &sub_query_fields,
      std::vector<CompOp> &sub_query_opts, std::vector<int8_t> both_sub, bool connector);
  virtual ~PredicateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::PREDICATE;
  }

  bool has_sub_query() { return sub_query_opts_.size() != 0; }

  std::vector<int8_t> &both_is_sub_query() { return both_is_sub_query_; }
  std::vector<FieldExpr> &sub_query_fields() { return sub_query_fields_; }
  std::vector<CompOp> &sub_query_opts() { return sub_query_opts_; }
  bool sub_query_connector() { return sub_query_connector_; }
  void set_table_get(std::unique_ptr<LogicalOperator> table_get_oper) {
    if(children_.empty()) {
      children_.push_back(std::move(table_get_oper));
    } else children_[0] = std::move(table_get_oper);
  }
private:
  std::vector<int8_t> both_is_sub_query_;
  std::vector<FieldExpr> sub_query_fields_;
  std::vector<CompOp> sub_query_opts_;
  // false->and, true->or;
  bool sub_query_connector_ = true;
};
