#pragma once

#include <memory>
#include <vector>

#include "sql/operator/logical_operator.h"

/**
 * @brief 聚合函数算子描述
 * @details 可以看OptimizeStage中相关的代码
 */
class AggrFuncLogicalOperator : public LogicalOperator
{
public:
  AggrFuncLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions)
  {
    expressions_.swap(expressions);
  }

  virtual ~AggrFuncLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::AGGRFUNC; }
};