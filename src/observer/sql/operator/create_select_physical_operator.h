#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class CreateTableStmt;
class Table;
class Db;

class CreateSelectPhysicalOperator : public PhysicalOperator
{
public:
  CreateSelectPhysicalOperator(CreateTableStmt *create_table_stmt, Db *db) : create_table_stmt_(create_table_stmt), db_(db)
  {}

  virtual ~CreateSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::CREATE_SELECT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  Trx *trx_ = nullptr;
  CreateTableStmt *create_table_stmt_;
  Table *table_ = nullptr;
  Db *db_;
};