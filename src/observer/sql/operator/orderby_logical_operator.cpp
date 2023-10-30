#include "orderby_logical_operator.h"

OrderbyLogicalOperator::OrderbyLogicalOperator(
    const std::vector<Field> &fields, const std::vector<Field> &orders, const std::vector<bool> &asc)
    : fields_(fields), orders_(orders), asc_(asc)
{}