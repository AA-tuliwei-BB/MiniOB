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
  AggrFuncLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions, std::vector<AggrFuncExpr*> &&aggr_list)
  {
    expressions_.swap(expressions);
    aggr_list_.swap(aggr_list);
  }

  virtual ~AggrFuncLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::AGGRFUNC; }

  std::vector<AggrFuncExpr*> &aggr_list()
  {
    return aggr_list_;
  }

private:
  std::vector<AggrFuncExpr*> aggr_list_;  
};