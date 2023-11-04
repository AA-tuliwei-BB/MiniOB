#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/stmt/create_select_stmt.h"

class CreateSelectLogicalOperator : public LogicalOperator 
{
public:
  CreateSelectLogicalOperator() = default;
  CreateSelectLogicalOperator(CreateTableStmt *create_table_stmt, Db *db)
  {
    create_table_stmt_ = create_table_stmt;
    db_ = db;
  }

  virtual ~CreateSelectLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::CREATE_SELECT;
  }

  CreateTableStmt *create_table_stmt() { return create_table_stmt_; }

  Db *db() { return db_; }

private:
  // MYTODO 改用智能指针，避免内存泄漏
  CreateTableStmt *create_table_stmt_;
  Db *db_;
};