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

#include "common/log/log.h"
#include "sql/operator/predicate_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "predicate_physical_operator.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr,
    std::vector<FieldExpr> sub_query_fields, std::vector<CompOp> sub_query_opts, bool connector)
    : expression_(std::move(expr)),
      sub_query_fields_(sub_query_fields),
      sub_query_opts_(sub_query_opts),
      sub_query_connector_(connector)
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
  ASSERT(sub_query_fields_.size() == sub_query_opts_.size(), "invalid sub query: size not equal");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  // if (children_.size() != 1) {
  //   LOG_WARN("predicate operator must has one child");
  //   return RC::INTERNAL;
  // }

  trx_ = trx;
  return children_[0]->open(trx);
}

RC PredicatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    JoinedTuple join_tuple;
    if (parent_tuple_ != nullptr)
    {
      join_tuple.set_left(tuple);
      join_tuple.set_right(get_parent_tuple());
      tuple = &join_tuple;
    }

    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (value.get_boolean() && sub_query_connector_ == true) {
      return rc;
    }
    if (!value.get_boolean() && sub_query_connector_ == false) {
      continue;
    }

    bool passed = !sub_query_connector_;
    int sub_num = sub_query_fields_.size();
    for (int i = 0; i < sub_num; ++i) {
      if (i + 1 == children_.size()) {
        return RC::INTERNAL;
      }
      bool result;
      RC rc = execute_sub_query(sub_query_fields_[i], sub_query_opts_[i], children_[i + 1].get(), tuple, result);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      if (result && sub_query_connector_ == true) {
        return rc;
      }
      if (!result && sub_query_connector_ == false) {
        passed = false;
        break;
      }
    }
    if (passed) {
      return RC::SUCCESS;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

RC PredicatePhysicalOperator::execute_sub_query(FieldExpr &left, CompOp &op, PhysicalOperator *right, Tuple *tuple, bool &result)
{
  right->set_parent_tuple(tuple);
  Value left_value;
  RC rc = left.get_value(*tuple, left_value);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = right->open(trx_);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  switch (op)
  {
  case IN:
  case NOT_IN: {
    result = (op == IN) ? false : true;
    while ((rc = right->next()) == RC::SUCCESS) {
      Value right_value;
      right->current_tuple()->cell_at(0, right_value);
      if (0 == left_value.compare(right_value)) {
        if (op == IN) {
          result = true;
        } else {
          result = false;
        }
        break;
      }
    }
  } break;

  case EXIST:
  case NOT_EXIST: {
    result = (right->next() == RC::SUCCESS);
    if (NOT_EXIST) {
      result = !result;
    }
  } break;
  
  default: {
    if ((rc = right->next()) == RC::SUCCESS) {
      Value right_value;
      right->current_tuple()->cell_at(0, right_value);
      rc = ComparisonExpr::compare_value_static(left_value, right_value, op, result);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      if((rc = right->next()) != RC::RECORD_EOF) {
        LOG_WARN("more than 1 child tuple in sub query or error in sub query, error=%s", strrc(rc));
        right->close();
        return RC::INVALID_ARGUMENT;
      }
    } else {
      LOG_WARN("fail to reach child tuple in sub query");
      right->close();
      return rc;
    }
  } break;
  }

  rc = right->close();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return RC::SUCCESS;
}
