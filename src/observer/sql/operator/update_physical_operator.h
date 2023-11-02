#pragma once

#include "sql/operator/physical_operator.h"

class Trx;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<std::string> &&fields, std::vector<Value> &&values)
      : table_(table), fields_(fields), values_(values)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::DELETE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  Table *table_ = nullptr;
  std::vector<std::string> fields_;
  std::vector<Value> values_;
  std::map<RID, bool> visited;
  Trx *trx_ = nullptr;
  bool morethan1row = false;
};