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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"
#include "join_physical_operator.h"

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator()
{}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  left_ = children_[0].get();
  right_ = children_[1].get();
  right_closed_ = true;
  round_done_ = true;

  if (!bufferred) {
    left_->open(trx);
    right_->open(trx);
    get_buffer();
    left_position  = 0;
    right_position = 0;
    left_->close();
    right_->close();
    bufferred = true;
  }

  rc = left_->open(trx);
  trx_ = trx;
  return rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  bool left_need_step = (left_tuple_ == nullptr);
  RC rc = RC::SUCCESS;
  if (round_done_) {
    left_need_step = true;
  } else {
    rc = right_next();
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_EOF) {
        left_need_step = true;
      } else {
        return rc;
      }
    } else {
      return rc;  // got one tuple from right
    }
  }

  if (left_need_step) {
    rc = left_next();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  rc = right_next();
  return rc;
}

RC NestedLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  if (!right_closed_) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close right oper. rc=%s", strrc(rc));
    } else {
      right_closed_ = true;
    }
  }
  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple()
{
  return &joined_tuple_;
}

RC NestedLoopJoinPhysicalOperator::get_buffer()
{
  if (left_->type() != PhysicalOperatorType::NESTED_LOOP_JOIN) {
    left_bufferred = true;
    RC rc = RC::SUCCESS;
    while ((rc = left_->next()) == RC::SUCCESS) {
      left_buffer.push_back(new RowTuple(*static_cast<RowTuple *>(left_->current_tuple())));
    }
    if (rc != RC::RECORD_EOF) {
      return rc;
    }
  }

  if (right_->type() != PhysicalOperatorType::NESTED_LOOP_JOIN) {
    right_bufferred = true;
    RC rc = RC::SUCCESS;
    while ((rc = right_->next()) == RC::SUCCESS) {
      right_buffer.push_back(new RowTuple(*static_cast<RowTuple *>(right_->current_tuple())));
    }
    if (rc != RC::RECORD_EOF) {
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC NestedLoopJoinPhysicalOperator::left_next()
{
  if (left_bufferred) {
    if (left_position == left_buffer.size()) {
      return RC::RECORD_EOF;
    }
    left_tuple_ = left_buffer[left_position];
    joined_tuple_.set_left(left_tuple_);
    left_position++;
    return RC::SUCCESS;
  }

  RC rc = RC::SUCCESS;
  rc = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple();
  joined_tuple_.set_left(left_tuple_);
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (right_bufferred) {
    if (round_done_) {
      right_position = 0;
      round_done_ = false;
    }
    if (right_position == right_buffer.size()) {
      round_done_ = true;
      return RC::RECORD_EOF;
    }
    right_tuple_ = right_buffer[right_position];
    joined_tuple_.set_right(right_tuple_);
    right_position++;
    return RC::SUCCESS;
  }

  if (round_done_) {
    if (!right_closed_) {
      rc = right_->close();
      right_closed_ = true;
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    rc = right_->open(trx_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    right_closed_ = false;

    round_done_ = false;
  }

  rc = right_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      round_done_ = true;
    }
    return rc;
  }

  right_tuple_ = right_->current_tuple();
  joined_tuple_.set_right(right_tuple_);
  return rc;
}
