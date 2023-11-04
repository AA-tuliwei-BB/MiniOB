#pragma once

#include <memory>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"

class GroupbyPhysicalOperator : public PhysicalOperator
{
public:
  GroupbyPhysicalOperator() = default;
  GroupbyPhysicalOperator(std::vector<AggrFuncExpr *> exprs, std::vector<Field> fields,
      std::vector<AggrFuncExpr *> left, std::vector<AggrFuncExpr *> right, std::vector<CompOp> opts)
      : exprs_(exprs), fields_(fields), left_(left), right_(right), opts_(opts)
  {}

  virtual ~GroupbyPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::GROUPBY;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  void reset();
  RC add(Tuple *tuple);
  RC check_same(Tuple *tuple, bool &result);
  RC filter(bool &result);
  RC get_tuple();

  Tuple *current_tuple() override;

private:
  std::vector<Field> fields_;
  std::vector<AggrFuncExpr *> exprs_;
  std::vector<AggrFuncExpr *> left_;
  std::vector<AggrFuncExpr *> right_;
  std::vector<CompOp> opts_;

  ValueListTuple tuple_;
  std::vector<Value> last_values;
  bool start_ = false;
  bool end_ = false;
};