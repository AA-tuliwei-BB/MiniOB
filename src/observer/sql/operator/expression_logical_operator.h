#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "storage/field/field.h"

/**
 * @brief expression 表示表达式
 * @ingroup LogicalOperator
 * @details 表达式算子
 */
class ExpressionLogicalOperator : public LogicalOperator 
{
public:
  virtual ~ExpressionLogicalOperator() = default;
  ExpressionLogicalOperator(std::vector<std::unique_ptr<Expression>>&& expressions);

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::EXPRESSION;
  }

  std::vector<std::unique_ptr<Expression>> &expressions()
  {
    return expressions_;
  }
  const std::vector<std::unique_ptr<Expression>> &expressions() const
  {
    return expressions_;
  }

private:
};
