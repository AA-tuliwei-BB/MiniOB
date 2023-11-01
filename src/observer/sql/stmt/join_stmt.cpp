
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

RC JoinStmt::create(Db *db, JoinSqlNode &join_sql, std::vector<Table*>& tables,  std::unordered_map<std::string, Table *> &table_map, JoinStmt *&stmt) {
    if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  for (size_t i = 0; i < join_sql.join_list.size() / 2; i++) {
    const char *table_name = join_sql.join_list[i * 2].c_str();
      if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if(!join_sql.join_list[i * 2 + 1].empty()) {
      if(table_map.find(join_sql.join_list[i * 2 + 1]) == table_map.end()){
        table_map[join_sql.join_list[i * 2 + 1]] = table;
      } else {
        LOG_ERROR("name %s refers to multiple table", join_sql.join_list[i * 2].c_str());
        return RC::INVALID_ARGUMENT;
      }
    }
  }
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      tables[0],
      &table_map,
      join_sql.on_conditions,
      static_cast<int>(join_sql.on_conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  stmt = new JoinStmt(tables, join_sql.join_list.size() / 2, filter_stmt);
  return RC::SUCCESS;
}