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
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include <memory>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"

class FilterStmt;

/**
 * @brief 过滤/谓词物理算子
 * @ingroup PhysicalOperator
 */
class PredicatePhysicalOperator : public PhysicalOperator
{
public:
  PredicatePhysicalOperator(std::unique_ptr<Expression> expr);

  PredicatePhysicalOperator(std::unique_ptr<Expression> expr, std::vector<FieldExpr> sub_query_fields,
      std::vector<CompOp> sub_query_opts, std::vector<int8_t> both_sub, bool connector);

  virtual ~PredicatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::PREDICATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  RC execute_sub_query(FieldExpr &left, CompOp &op, PhysicalOperator *right, Tuple *tuple, bool &result);
  RC execute_sub_query(PhysicalOperator *left, CompOp &op, PhysicalOperator *right, Tuple *tuple, bool &result);

private:
  std::unique_ptr<Expression> expression_;
  std::vector<int8_t> both_is_sub_query_;
  std::vector<FieldExpr> sub_query_fields_;
  std::vector<CompOp> sub_query_opts_;
  // false->and, true -> or;
  bool sub_query_connector_ = false; // And / Or
  Trx *trx_ = nullptr;
};
