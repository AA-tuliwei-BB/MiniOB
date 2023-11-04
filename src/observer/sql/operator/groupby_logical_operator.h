#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

/**
 * @brief 表示从表中获取数据的算子
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class GroupbyLogicalOperator : public LogicalOperator
{
public:
  GroupbyLogicalOperator(std::vector<AggrFuncExpr *> exprs, std::vector<Field> fields, std::vector<AggrFuncExpr *> left,
      std::vector<AggrFuncExpr *> right, std::vector<CompOp> opts)
      : exprs_(exprs), fields_(fields), left_(left), right_(right), opts_(opts)
  {}
  virtual ~GroupbyLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::GROUPBY;
  }

  std::vector<Field>          &fields() { return fields_; }
  std::vector<AggrFuncExpr *> &exprs() { return exprs_; }
  std::vector<AggrFuncExpr *> &left() { return left_; }
  std::vector<AggrFuncExpr *> &right() { return right_; }
  std::vector<CompOp>         &opts() { return opts_; }

private:
  std::vector<Field> fields_;
  std::vector<AggrFuncExpr *> exprs_;
  std::vector<AggrFuncExpr *> left_;
  std::vector<AggrFuncExpr *> right_;
  std::vector<CompOp> opts_;
};