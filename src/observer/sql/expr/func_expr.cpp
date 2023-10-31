#include "sql/expr/func_expr.h"
#include <cmath>
#include "func_expr.h"

FuncExpr::FuncExpr(Type type, Expression *son) : func_type_(type), son_(son) { round_bits_ = 0; }

FuncExpr::FuncExpr(Type type, std::unique_ptr<Expression> son) : func_type_(type), son_(std::move(son))
{
  round_bits_ = 0;
}

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
  return UNDEFINED;
}

RC FuncExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value son_value;
  RC rc = son_->get_value(tuple, son_value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("can't get son_value");
    return rc;
  }
  return calc_value(son_value, value);
}

RC FuncExpr::try_get_value(Value &value) const
{
  Value son_value;
  RC rc = son_->try_get_value(son_value);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return calc_value(son_value, value);
}

RC FuncExpr::calc_value(const Value &son_value, Value &value) const
{
  switch (func_type_)
  {
  case Type::LENGTH: {
    if (son_value.attr_type() != CHARS) {
      return RC::INTERNAL;
    }
    value.set_int(son_value.get_string().length());
  } break;
  case Type::ROUND: {
    if (son_value.attr_type() != FLOATS) {
      return RC::INTERNAL;
    }
    if (round_bits_ == 0) {
      value.set_int(int(std::round(son_value.get_float())));
    } else {
      double Pow = pow(10, round_bits_);
      value.set_float(std::round(son_value.get_float() * Pow) / Pow);
    }
  } break;

  case Type::FORMAT: {
    if (son_value.attr_type() != DATES) {
      return RC::INTERNAL;
    }
    int         date = son_value.get_int();
    std::string formatted(format_string_);
    std::string year(std::to_string(date / 10000));
    while (year.size() < 4) {
      year = "0" + year;
    }
    std::string little_year(std::to_string(date / 10000 % 100));
    if (little_year.size() == 1) {
      little_year = "0" + little_year;
    }
    std::string month(std::to_string(date / 100 % 100));
    if (month.size() == 1) {
      month = "0" + month;
    }
    std::string day(std::to_string(date % 100));
    if (day.size() == 1) {
      day = "0" + day;
    }
    size_t found_place;
    while ((found_place = formatted.find("%Y")) != std::string::npos) {
      formatted.replace(found_place, 2, year);
    }
    while ((found_place = formatted.find("%y")) != std::string::npos) {
      formatted.replace(found_place, 2, little_year);
    }
    while ((found_place = formatted.find("%m")) != std::string::npos) {
      formatted.replace(found_place, 2, month);
    }
    while ((found_place = formatted.find("%d")) != std::string::npos) {
      formatted.replace(found_place, 2, day);
    }
    value.set_string(formatted.c_str());
  } break;
  default:
    break;
  }
  return RC::SUCCESS;
}