/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "common/lang/comparator.h"


UpdateStmt::UpdateStmt(Table *table, const std::string *fields, const Value *values, int value_amount, FilterStmt *filter_stmt, std::vector<SelectStmt*>* sub_select)
    : table_(table), fields_(fields), values_(values), value_amount_(value_amount), filter_stmt_(filter_stmt), sub_select_(sub_select)
{}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::vector<SelectStmt *> *sub_select_stmts;
  sub_select_stmts = new std::vector<SelectStmt *>;
  for (auto &sub_sql_node : update.sub_select) {
    Stmt *sub_select_stmt = nullptr;
    RC rc = SelectStmt::create(db, sub_sql_node->selection, sub_select_stmt);
    if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create sub select statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
    sub_select_stmts->push_back(static_cast<SelectStmt *>(sub_select_stmt));
  }
  int select_size = sub_select_stmts->size(), select_index = 0;
  // TODO when update 多词条修改
  const Value *values = update.value.data();
  const std::string *fields = update.name.data();
  if(update.name.size() != update.value.size()){
    LOG_WARN("value size doesn't equal to field size.");
    return RC::INTERNAL;
  }

  const int value_num = update.name.size();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();

  // check field
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; ++i) {// 用于拓展多词条
    bool bFieldExists = false;
    if (values[i].attr_type() == CHARS || values[i].attr_type() == TEXTS) {
      if (values[i].length() > 65535) {
        LOG_ERROR("TEXT TOO LONG");
        return RC::INTERNAL;
      }
    }
    for (int j = 0; j < field_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      if (field_meta->name() == fields[i]) {
        bFieldExists = true;
        AttrType field_type = field_meta->type();
        AttrType value_type = values[i].attr_type();
        if(value_type == AttrType::UNDEFINED){
          value_type = sub_select_stmts->at(select_index++)->value_type();
        }
        // if (!common::field_type_compare_compatible_table[field_type][value_type] && (!values[i].is_null() || !field_meta->nullable())) {  // TODO try to convert the value type to field type
        //   LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
        //     table_name, field_meta->name(), field_type, value_type);
        //   return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        // }
        // else if(field_type != value_type && !update.value[i].try_cast(field_type)){
        //   LOG_WARN("unable to cast value type to field type. table=%s, field=%s, field type=%d, value_type=%d",
        //     table_name, field_meta->name(), field_type, value_type);
        //   return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        // }
      }
    }
    if (!bFieldExists) {
      LOG_WARN("field not found. table=%s, field=%s", table_name, fields[i].c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  // get filter_stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions, static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }



  stmt = new UpdateStmt(table, fields, values, value_num, filter_stmt, sub_select_stmts);
  return RC::SUCCESS;
}
