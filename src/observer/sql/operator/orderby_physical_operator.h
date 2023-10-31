#pragma once

#include <memory>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"

class OrderbyPhysicalOperator : public PhysicalOperator
{
public:
  OrderbyPhysicalOperator(std::vector<Field> &&fields, std::vector<Field> &&orders, std::vector<bool> &&asc);

  virtual ~OrderbyPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::ORDERBY;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  std::vector<Field> fields_;
  std::vector<Field> orders_;
  std::vector<std::vector<Value>> rows_;
  std::vector<bool> asc_; // 是否升序
  SpecValueListTuple tuple_;
  int current_row_;
  bool emitted_ = false;
};