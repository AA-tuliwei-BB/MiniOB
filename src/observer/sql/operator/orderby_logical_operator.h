#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

/**
 * @brief 表示从表中获取数据的算子
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class OrderbyLogicalOperator : public LogicalOperator
{
public:
  OrderbyLogicalOperator(const std::vector<Field> &fields, const std::vector<Field> &orders, const std::vector<bool> &asc);
  virtual ~OrderbyLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::ORDERBY;
  }

  std::vector<Field>& fields() { return fields_; }
  std::vector<Field>& orders() { return orders_; }
  std::vector<bool>  &asc() { return asc_; }

private:
  std::vector<Field> fields_;
  std::vector<Field> orders_;
  std::vector<bool> asc_; // 是否升序
};