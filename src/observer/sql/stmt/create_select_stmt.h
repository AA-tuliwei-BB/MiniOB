#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class Db;
class CreateTableStmt;
class SelectStmt;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateSelectStmt : public Stmt
{
public:
  CreateSelectStmt(Db *db, CreateTableStmt *create_table_stmt, SelectStmt *select_stmt)
        : create_table_stmt_(create_table_stmt),
          select_stmt_(select_stmt),
          db_(db)
  {}
  virtual ~CreateSelectStmt() = default;

  StmtType type() const override { return StmtType::CREATE_SELECT; }

  CreateTableStmt *create_table_stmt() { return create_table_stmt_; }
  SelectStmt * select_stmt() { return select_stmt_; }
  Db *db() { return db_; }

  //static RC create(Db *db, const CreateSelectSqlNode &create_table, Stmt *&stmt);

private:
  CreateTableStmt *create_table_stmt_;
  SelectStmt * select_stmt_;
  Db *db_;
};