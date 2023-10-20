#include "sql/expr/func_expr.h"

FuncExpr::FuncExpr(Type type, Expression *son) : func_type_(type), son_(son) {}

FuncExpr::FuncExpr(Type type, std::unique_ptr<Expression> son) : func_type_(type), son_(std::move(son)) {}

AttrType FuncExpr::value_type() const
{
  switch (func_type_)
  {
  case Type::LENGTH:
    return INTS;
  case Type::ROUND:
    return INTS;
  case Type::FORMAT:
    return CHARS;
  default:
    break;
  }
}

RC FuncExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value son_value;
  RC rc = get_value(tuple, son_value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("can't get son_value");
    return rc;
  }

  switch (func_type_)
  {
  case Type::LENGTH: {
    if (son_value.attr_type() != CHARS) {
      return RC::INTERNAL;
    }
    value.set_int(son_value.get_string().length());
  } break;
  case Type::ROUND: {

  } break;
  case Type::FORMAT: {

  } break;
  default:
    break;
  }
}