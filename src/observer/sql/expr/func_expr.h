#pragma once

#include "sql/expr/expression.h"

/**
 * @brief 函数表达式
 * @ingroup Expression
 */
class FuncExpr : public Expression
{
public:
  enum class Type {
    LENGTH,
    ROUND,
    FORMAT,
  };

public:
  FuncExpr(Type type, Expression *son);
  FuncExpr(Type type, std::unique_ptr<Expression> son);
  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNCTION; }

  AttrType value_type() const override;
  bool is_attr() const { return true; }
  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type func_type() const { return func_type_; }

  std::unique_ptr<Expression> &son() { return son_; }

  void set_format_string(std::string str) { format_string_ = str; }
  void set_round_bits(int bits) { round_bits_ = bits; }

private:
  RC calc_value(const Value &son_value, Value &value) const;
  
private:
  Type func_type_;
  std::unique_ptr<Expression> son_;
  std::string format_string_;
  int round_bits_;
};