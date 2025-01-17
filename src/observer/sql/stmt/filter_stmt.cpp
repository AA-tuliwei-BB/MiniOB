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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/lang/comparator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
  std::vector<ConditionSqlNode *>& conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, *conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }
  if(condition_num != 0)
    tmp_stmt->set_conj(conditions[condition_num - 1]->conjunction_type);
  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;
  int left_attr, right_attr;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  

  std::vector<Table*> table_wrap;
  std::vector<Field> field_wrap;
  std::pair<std::unique_ptr<Expression>, RC> left_parse, right_parse;
  SelectStmt* left_stmt, *right_stmt;
  FilterObj left, right;
  table_wrap.push_back(default_table);
  // 如果是EXIST，是参数为sub_query的单目运算符
  if (comp == EXIST || comp == NOT_EXIST) {
    Stmt* tmp;
    if(!condition.right_is_sub_query) {
      LOG_ERROR("Exist operator needs a sub query");
      return RC::INVALID_ARGUMENT;
    }
    rc = SelectStmt::create_sub_query(db, condition.right_sub_query->selection, tmp, tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("Error when parsing arithmatic expression sql node's right sub_query, error_code = %d.", rc);
      return rc;
    }
    SelectStmt* sub_query_stmt = static_cast<SelectStmt*>(tmp);
    
    FilterObj left;
    filter_unit = new FilterUnit(left, static_cast<SelectStmt*>(sub_query_stmt));
    filter_unit->set_comp(comp);
    return rc;
  }

  if(condition.left_is_sub_query) {
    Stmt* tmp;
    rc = SelectStmt::create_sub_query(db, condition.left_sub_query->selection, tmp, tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("Error when parsing arithmatic expression sql node's left sub_query, error_code = %d.", rc);
      return rc;
    }
    left_stmt = static_cast<SelectStmt*>(tmp);
    left_attr = left_stmt->value_type();
  } else {
    left_parse = build_expression(condition.left_expression.get(), table_wrap, *tables, field_wrap, db->name(), nullptr, nullptr);
    if(left_parse.second != RC::SUCCESS){
    LOG_WARN("Error when parsing arithmatic expression sql node's left son, error_code = %d.", left_parse.second);
    return left_parse.second;
    }
    left.init(std::move(left_parse.first));
    left_attr = left.expression->value_type();
  }
  
  if (condition.right_is_sub_query) {
    Stmt* tmp;
    rc = SelectStmt::create_sub_query(db, condition.right_sub_query->selection, tmp, tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("Error when parsing arithmatic expression sql node's right sub_query, error_code = %d.", rc);
      return rc;
    }
    right_stmt = static_cast<SelectStmt*>(tmp);
    right_attr = right_stmt->value_type();
    if (!common::field_type_compare_compatible_table[left_attr][right_attr]) {
      // 不能比较的两个字段， 要把信息传给客户端
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    if(condition.left_is_sub_query)
      filter_unit = new FilterUnit(left_stmt, right_stmt);
    else filter_unit = new FilterUnit(left, right_stmt);
    
  } else if(condition.right_is_value_list) {
    for(auto &it : condition.value_list) {
      if (!common::field_type_compare_compatible_table[left_attr][it.attr_type()]) {
      // 不能比较的两个字段， 要把信息传给客户端
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    filter_unit = new FilterUnit(left, condition.value_list);
  } else {
    right_parse = build_expression(condition.right_expression.get(), table_wrap, *tables, field_wrap, db->name(), nullptr, nullptr);
    if(right_parse.second != RC::SUCCESS){
    LOG_WARN("Error when parsing arithmatic expression sql node's right son, error_code = %d.", right_parse.second);
    return right_parse.second;
    }
    
    FilterObj right(std::move(right_parse.first));
    right_attr = right.expression->value_type();
    // 检查两个类型是否能够比较
    if (!common::field_type_compare_compatible_table[left_attr][right_attr]) {
      // 不能比较的两个字段， 要把信息传给客户端
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    
    if(condition.left_is_sub_query) {
      LOG_WARN("left and right should have been swapped!");
      return RC::INTERNAL;
    }
    filter_unit = new FilterUnit(left, right);
  }
  
  
  filter_unit->set_comp(comp);

  return rc;
}
