#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"

class AggrFuncPhysicalOperator : public PhysicalOperator
{
public:
  AggrFuncPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions, std::vector<AggrFuncExpr*> &&aggr_list)
    : expressions_(std::move(expressions)), tuple_(expressions_), aggr_list_(aggr_list)
  {}

  virtual ~AggrFuncPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGGRFUNC;
  }

  std::string name() const override { return "CALC"; }
  std::string param() const override { return ""; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
    return tuple_.cell_num();
  }

  Tuple *current_tuple() override
  {
    return &tuple_;
  }

  const std::vector<std::unique_ptr<Expression>> &expressions() const
  {
    return expressions_;
  }

private:
  std::vector<std::unique_ptr<Expression>> expressions_;
  std::vector<AggrFuncExpr*> aggr_list_;
  ExpressionTuple tuple_;
  bool emitted_ = false;
  Trx *trx_ = nullptr;
};
