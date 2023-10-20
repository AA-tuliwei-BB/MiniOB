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
    return LogicalOperatorType::PROJECTION;
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
//! 投影映射的字段名称
  //! 并不是所有的select都会查看表字段，也可能是常量数字、字符串，
  //! 或者是执行某个函数。所以这里应该是表达式Expression。
  //! 不过现在简单处理，就使用字段来描述
  // std::vector<Expression> expressions_;
  // 逻辑算子自带expressions
};
