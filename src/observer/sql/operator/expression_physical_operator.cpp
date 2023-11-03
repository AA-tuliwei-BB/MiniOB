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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/expression_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ExpressionPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    constant_over_ = false;
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  if (parent_tuple_ != nullptr) {
    child->set_parent_tuple(get_parent_tuple());
  }

  constant_over_ = false;
  return RC::SUCCESS;
}

RC ExpressionPhysicalOperator::next()
{
  if (children_.empty()) {
    if(is_constant_) {
      if (!constant_over_) {
        constant_over_ = true;
        return RC::SUCCESS;
      } else {
        return RC::RECORD_EOF;
      }
    }
    return RC::RECORD_EOF;
  }
  RC rc = children_[0]->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  tuple_.set_child_tuple(children_[0]->current_tuple());
  return RC::SUCCESS;
}

RC ExpressionPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *ExpressionPhysicalOperator::current_tuple()
{
  // tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}