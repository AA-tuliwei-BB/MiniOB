#include "sql/operator/expression_logical_operator.h"

ExpressionLogicalOperator::ExpressionLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions)
{
  expressions_ = std::move(expressions);
}