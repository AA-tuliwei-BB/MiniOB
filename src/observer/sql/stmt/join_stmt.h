#pragma once
#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/stmt/filter_stmt.h"

class JoinStmt
{
public:
    JoinStmt(std::vector<Table*> &tables_, int length, FilterStmt* stmt): filter_stmt(stmt) {
        tables.insert(tables.end(), tables_.end() - length, tables_.end());
    };
    virtual ~JoinStmt() = default;

    std::vector<Table*> tables;
    std::unique_ptr<FilterStmt> filter_stmt; 
    static RC create(Db *db, JoinSqlNode &join_sql, std::vector<Table*>& tables,  std::unordered_map<std::string, Table *> &table_map, JoinStmt *&stmt);
};