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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "common/lang/comparator.h"
#include "expression.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
    : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr()
{}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr()
{}


RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  return compare_value_static(left, right, comp_, result);
}

RC ComparisonExpr::compare_value_static(const Value &left, const Value &right, const CompOp &comp, bool &result)
{
  RC rc = RC::SUCCESS;
  if(comp == LIKE || comp == NOT_LIKE){
    result = common::like_match(left.get_string(), right.get_string());
    if(comp == NOT_LIKE) result = !result;
    return rc;
  }
  result = false;
  if(comp != IS && comp != IS_NOT && (left.is_null() || right.is_null())) return rc;
  int cmp_result = left.compare(right);
  switch (comp) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case IS: {
      result = cmp_result == 0 && !(left.is_null() ^ right.is_null()); 
    } break;
    case IS_NOT: {
      result = cmp_result != 0 || (left.is_null() ^ right.is_null()); 
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS &&
      right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }
  
  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  if (left_value.is_null() || right_value.is_null()) {
    value.set_null();
    return RC::SUCCESS;
  }

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          value.set_null();
          // NOTE: 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          // value.set_int(numeric_limits<int>::max());
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          value.set_null();
          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          // value.set_float(numeric_limits<float>::max());
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if(arithmetic_type_ != Type::NEGATIVE){
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

/////////////////////////////////////////////////////////////////////////////////////////

AggrFuncExpr::AggrFuncExpr(Type type, Expression *son) : func_type_(type), son_(son) { count_ = 0; }

AggrFuncExpr::AggrFuncExpr(Type type, std::unique_ptr<Expression> son) : func_type_(type), son_(std::move(son))
{
  count_ = 0;
}

AttrType AggrFuncExpr::value_type() const
{
  switch (func_type_) {
  case Type::AVG_FUNC : {
    return FLOATS;
  } break;
  case Type::COUNT_FUNC: {
    return INTS;
  } 
  case Type::MIN_FUNC:
  case Type::MAX_FUNC:
  case Type::SUM_FUNC: {
    return son_->value_type();
  }
  default:
    return UNDEFINED;
    break;
  }
}

RC AggrFuncExpr::add_value(const Tuple &tuple)
{
  RC rc = RC::SUCCESS;

  if (son_->type() == ExprType::STAR) {
    if (func_type_ == Type::COUNT_FUNC) {
      count_++;
      return rc;
    } else {
      return RC::INTERNAL;
    }
  }

  Value son_value;
  rc = son_->get_value(tuple, son_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of son expression. rc=%s", strrc(rc));
    return rc;
  }

  if (son_value.is_null()) {
    return RC::SUCCESS;
  }
  if (func_type_ == Type::COUNT_FUNC) {
    count_++;
    return RC::SUCCESS;
  }

  if (count_++ == 0) {
    sum_.set_value(son_value);
    min_.set_value(son_value);
    max_.set_value(son_value);
    return RC::SUCCESS;
  }

  if (func_type_ == Type::CONST_FIELD) {
    if (son_value.compare(min_) != 0) {
      return RC::INTERNAL;
    }
    return RC::SUCCESS;
  }

  switch (son_value.attr_type())
  {
  case INTS: {
    sum_.set_int(sum_.get_int() + son_value.get_int());
    min_.set_int(std::min(min_.get_int(), son_value.get_int()));
    max_.set_int(std::max(max_.get_int(), son_value.get_int()));
  } break;
  case FLOATS: {
    sum_.set_float(sum_.get_float() + son_value.get_float());
    min_.set_float(std::min(min_.get_float(), son_value.get_float()));
    max_.set_float(std::max(max_.get_float(), son_value.get_float()));
  } break;
  case TEXTS:
  case CHARS: {
    min_.set_string(std::min(min_.get_string(), son_value.get_string()).c_str());
    max_.set_string(std::max(max_.get_string(), son_value.get_string()).c_str());
  } break;
  case DATES: {
    sum_.set_int(sum_.get_int() + son_value.get_int());
    if (min_.compare(son_value) > 0) {
      min_.set_value(son_value);
    }
    if (max_.compare(son_value) < 0) {
      max_.set_value(son_value);
    }
  } break;

  default:
    return RC::INTERNAL;
  }
  return rc;
}

RC AggrFuncExpr::get_value(Value &value) const
{
  if (count_ == 0 && func_type_ != Type::COUNT_FUNC) {
    value.set_null();
    return RC::SUCCESS;
  }

  switch (func_type_)
  {
  case Type::CONST_FIELD: {
    value.set_value(min_);
  } break;

  case Type::COUNT_FUNC: {
    value.set_int(count_);
  } break;

  case Type::AVG_FUNC: {
    if (sum_.attr_type() == INTS || sum_.attr_type() == DATES) {
      value.set_float((float)sum_.get_int() / count_);
    } else {
      value.set_float(sum_.get_float() / count_);
    }
  } break;

  case Type::SUM_FUNC: {
    if (sum_.attr_type() == INTS || sum_.attr_type() == DATES) {
      value.set_int(sum_.get_int());
    } else {
      value.set_float(sum_.get_float());
    }
  } break;

  case Type::MIN_FUNC: {
    value.set_value(min_);
  } break;
  case Type::MAX_FUNC: {
    value.set_value(max_);
  } break;

  default:
    return RC::INTERNAL;
    break;
  }
  return RC::SUCCESS;
}

RC AggrFuncExpr::try_get_value(Value &value) const
{
  if(finished){
    return get_value(value);
  }
  Value son_value;
  RC rc = son_->try_get_value(son_value);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (func_type_ == Type::COUNT_FUNC) {
    if (son_value.is_null()) {
      value.set_int(0);
    } else {
      value.set_int(1);
    }
  } else {
    value.set_value(son_value);
  }
  return RC::SUCCESS;
}