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

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type func_type() const { return func_type_; }

  std::unique_ptr<Expression> &son() { return son_; }

private:
  RC calc_value(const Value &son, Value &value) const;
  
private:
  Type func_type_;
  std::unique_ptr<Expression> son_;
  std::string format_string_;
};