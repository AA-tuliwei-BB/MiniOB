#pragma once

#include <vector>
#include "sql/operator/physical_operator.h"

class Value;

/**
 * @brief Value列表物理算子
 * @ingroup PhysicalOperator
 * @details 用于将Value列表转换为物理算子,为了方便实现的接口，如sub query
 */
class ValueListPhysicalOperator : public PhysicalOperator
{
public:
  ValueListPhysicalOperator() {}
  ValueListPhysicalOperator(std::vector<Value> &list) { list_ = list; }
  ValueListPhysicalOperator(std::vector<Value> &&list) { list_ = std::move(list); }

  virtual ~ValueListPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::VALUE_LIST;
  }

  RC open(Trx *) override
  {
    started_ = false;
    return RC::SUCCESS;
  }

  RC next() override
  {
    if (!started_) {
      started_ = true;
      iterator_ = list_.begin();
    } else if (iterator_ != list_.end()) {
      ++iterator_;
    }
    return iterator_ == list_.end() ? RC::RECORD_EOF : RC::SUCCESS;
  }

  RC close() override
  {
    iterator_ = list_.end();
    return RC::SUCCESS;
  }

  Tuple *current_tuple() override
  {
    if (iterator_ == list_.end()) {
      return nullptr;
    }
    std::vector<Value> vec;
    vec.push_back(*iterator_);
    tuple_.set_cells(vec);
    return &tuple_;
  }

private:
  std::vector<Value> list_;
  std::vector<Value>::iterator iterator_;
  ValueListTuple tuple_;
  bool started_ = false;
};
