#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table, std::vector<std::string> &&fields, std::vector<Value> &&values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  const std::vector<std::string>& fields() const
  {
    return fields_;
  }
  std::vector<std::string>& fields()
  {
    return fields_;
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
  Table *table_ = nullptr;
  std::vector<std::string> fields_;
  std::vector<Value> values_;
};