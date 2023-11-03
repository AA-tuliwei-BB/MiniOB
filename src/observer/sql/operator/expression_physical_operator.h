#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 表达式物理算子
 * @ingroup PhysicalOperator
 */
class ExpressionPhysicalOperator : public PhysicalOperator
{
public:
  ExpressionPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions)
      : expressions_(std::move(expressions)), tuple_(expressions_)
  {
    is_constant_ = true;
    Value test;
    for(auto &it : expressions_){
      if(it->try_get_value(test) != RC::SUCCESS){
        is_constant_ = false;
        break;
      }
    }
  }

  virtual ~ExpressionPhysicalOperator() = default;

  /*
    void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions)
    {
      expressions_ = std::move(expressions);
    }
    void add_projection(const Table *table, const FieldMeta *field);
  */

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::EXPRESSION;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
    return tuple_.cell_num();
  }

  Tuple *current_tuple() override;

private:
  // ProjectTuple tuple_;
  std::vector<std::unique_ptr<Expression>> expressions_;
  ExpressionTuple tuple_;
  bool is_constant_;
  bool constant_over_ = false;
};
