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
// Created by Wangyunlai on 2022/12/13.
//

#include "sql/operator/predicate_logical_operator.h"

PredicateLogicalOperator::PredicateLogicalOperator(std::unique_ptr<Expression> expression)
{
  expressions_.emplace_back(std::move(expression));
}

PredicateLogicalOperator::PredicateLogicalOperator(std::unique_ptr<Expression> expr,
    std::vector<FieldExpr> &sub_query_fields, std::vector<CompOp> &sub_query_opts, std::vector<int8_t> both_sub, bool connector)
    : sub_query_fields_(sub_query_fields), sub_query_opts_(sub_query_opts), both_is_sub_query_(both_sub), sub_query_connector_(connector)
{
  expressions_.emplace_back(std::move(expr));
  ASSERT(sub_query_fields_.size() == sub_query_opts_.size(), "invalid sub query: size not equal");
}
