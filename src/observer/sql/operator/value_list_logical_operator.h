#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class ValueListLogicalOperator : public LogicalOperator 
{
public:
  ValueListLogicalOperator() = default;
  ValueListLogicalOperator(const std::vector<Value> &values)
  {
    values_ = values;
  }

  virtual ~ValueListLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::VALUELIST;
  }

  const std::vector<Value>& values() const
  {
    return values_;
  }
  std::vector<Value>& values()
  {
    return values_;
  }

private:
  std::vector<Value> values_;
};