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

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/create_index_stmt.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/drop_table_stmt.h"
#include "sql/stmt/desc_table_stmt.h"
#include "sql/stmt/help_stmt.h"
#include "sql/stmt/show_tables_stmt.h"
#include "sql/stmt/trx_begin_stmt.h"
#include "sql/stmt/trx_end_stmt.h"
#include "sql/stmt/exit_stmt.h"
#include "sql/stmt/set_variable_stmt.h"
#include "sql/stmt/load_data_stmt.h"
#include "sql/stmt/calc_stmt.h"

RC Stmt::create_stmt(Db *db, ParsedSqlNode &sql_node, Stmt *&stmt)
{
  stmt = nullptr;

  switch (sql_node.flag) {
    case SCF_INSERT: {
      return InsertStmt::create(db, sql_node.insertion, stmt);
    }
    case SCF_DELETE: {
      return DeleteStmt::create(db, sql_node.deletion, stmt);
    }
    case SCF_UPDATE: {
      return UpdateStmt::create(db, sql_node.update, stmt);
    }
    case SCF_SELECT: {
      return SelectStmt::create(db, sql_node.selection, stmt);
    }

    case SCF_EXPLAIN: {
      return ExplainStmt::create(db, sql_node.explain, stmt);
    }

    case SCF_CREATE_INDEX: {
      return CreateIndexStmt::create(db, sql_node.create_index, stmt);
    }

    case SCF_CREATE_TABLE: {
      return CreateTableStmt::create(db, sql_node.create_table, stmt);
    }

    case SCF_DROP_TABLE: {
      return DropTableStmt::create(db, sql_node.drop_table, stmt);
    }

    case SCF_DESC_TABLE: {
      return DescTableStmt::create(db, sql_node.desc_table, stmt);
    }

    case SCF_HELP: {
      return HelpStmt::create(stmt);
    }

    case SCF_SHOW_TABLES: {
      return ShowTablesStmt::create(db, stmt);
    }

    case SCF_BEGIN: {
      return TrxBeginStmt::create(stmt);
    }

    case SCF_COMMIT:
    case SCF_ROLLBACK: {
      return TrxEndStmt::create(sql_node.flag, stmt);
    }

    case SCF_EXIT: {
      return ExitStmt::create(stmt);
    }

    case SCF_SET_VARIABLE: {
      return SetVariableStmt::create(sql_node.set_variable, stmt);
    }

    case SCF_LOAD_DATA: {
      return LoadDataStmt::create(db, sql_node.load_data, stmt);
    }

    case SCF_CALC: {
      return CalcStmt::create(sql_node.calc, stmt);
    }

    default: {
      LOG_INFO("Command::type %d doesn't need to create statement.", sql_node.flag);
    } break;
  }
  return RC::UNIMPLENMENT;
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

std::pair<std::unique_ptr<Expression>, RC> build_expression(ExprSqlNode* father,
std::vector<Table *> &tables, 
std::unordered_map<std::string, Table *> &table_map,
std::vector<Field> &query_fields,
std::string db_name){
  switch (father->get_type())
  {
  case ExprSqlNode::Type::REL_ATTR_EXPR:{
    RelAttrSqlNode *relation_attr = (RelAttrSqlNode *)father;
    relation_attr->set_name();
    if (common::is_blank(relation_attr->relation_name.c_str()) &&
        0 == strcmp(relation_attr->attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }
      return std::make_pair(std::unique_ptr<Expression>(new StarExpr()), RC::SUCCESS);
    } else if (!common::is_blank(relation_attr->relation_name.c_str())) {
      const char *table_name = relation_attr->relation_name.c_str();
      const char *field_name = relation_attr->attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::SCHEMA_FIELD_MISSING);
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
        return std::make_pair(std::unique_ptr<Expression>(new StarExpr()), RC::SUCCESS);
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::SCHEMA_FIELD_MISSING);
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
          return std::make_pair(std::unique_ptr<Expression>(new StarExpr()), RC::SUCCESS);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db_name, table->name(), field_name);
            return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::SCHEMA_FIELD_MISSING);
          }

          query_fields.push_back(Field(table, field_meta));
          
          std::unique_ptr<Expression> result(new FieldExpr(table, field_meta));
          if(!relation_attr->alias_name.empty())
          result->set_name(relation_attr->name);
          return std::make_pair(std::move(result), RC::SUCCESS);
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr->attribute_name.c_str());
        return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::SCHEMA_FIELD_MISSING);
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr->attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db_name, table->name(), relation_attr->attribute_name.c_str());
        return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::SCHEMA_FIELD_MISSING);
      }

      query_fields.push_back(Field(table, field_meta));
      std::unique_ptr<Expression> result(new FieldExpr(table, field_meta));
      if(!relation_attr->alias_name.empty())
        result->set_name(relation_attr->name);
      return std::make_pair(std::move(result), RC::SUCCESS);
    }
  }
  break;
  case ExprSqlNode::Type::VALUE_EXPR:{
    ValueSqlNode &cur = *(ValueSqlNode*)father;
    std::unique_ptr<Expression> result(new ValueExpr(cur.val));
    result->set_name(cur.name);
    return std::make_pair(std::move(result), RC::SUCCESS);
  } 
  break;
  case ExprSqlNode::Type::AGGR_FUNC_EXPR:{
    AggrSqlNode &cur = *(AggrSqlNode*)father;
    cur.set_name();
    std::pair<std::unique_ptr<Expression>, RC> son_parse = 
    build_expression(cur.son.get(), tables, table_map, query_fields, db_name);
    if(son_parse.second != RC::SUCCESS){
      LOG_WARN("Error when parsing type = %d expression sql node, error_code = %d.", cur.get_type(), son_parse.second);
      return std::make_pair(std::unique_ptr<Expression>(nullptr), son_parse.second);
    }
    std::unique_ptr<AggrFuncExpr> result(new AggrFuncExpr(
    static_cast<AggrFuncExpr::Type>(static_cast<int>(cur.func_type) - 1), std::move(son_parse.first)));
    result->set_name(cur.name);
    return std::make_pair(std::move(result), RC::SUCCESS);
  }
  break;
  case ExprSqlNode::Type::FUNC_EXPR:{
   FuncSqlNode &cur = *(FuncSqlNode*)father;
    cur.set_name();
    std::pair<std::unique_ptr<Expression>, RC> son_parse = 
    build_expression(cur.son.get(), tables, table_map, query_fields, db_name);
    if(son_parse.second != RC::SUCCESS){
      LOG_WARN("Error when parsing type = %d expression sql node, error_code = %d.", cur.get_type(), son_parse.second);
      return std::make_pair(std::unique_ptr<Expression>(nullptr), son_parse.second);
    }
    FuncExpr::Type result_type;
    switch (cur.func_type)
    {
    case function_type::FUNC_LENGTH:
      result_type = FuncExpr::Type::LENGTH;
      break;
    case function_type::FUNC_ROUND:
      result_type = FuncExpr::Type::ROUND;
      break;
      case function_type::FUNC_DATE_FORMAT:
      result_type = FuncExpr::Type::FORMAT;
      break;
    default:
      break;
    }
    std::unique_ptr<FuncExpr> result(new FuncExpr(result_type, std::move(son_parse.first)));
    result->set_name(cur.name);
    return std::make_pair(std::move(result), RC::SUCCESS);
  }
  break;
  case ExprSqlNode::Type::ARITHMATIC_EXPR:{
    const ArithSqlNode &cur = *(ArithSqlNode*)father;
    std::pair<std::unique_ptr<Expression>, RC> left_parse = 
    build_expression(cur.left.get(), tables, table_map, query_fields, db_name);
    if(left_parse.second != RC::SUCCESS){
    LOG_WARN("Error when parsing arithmatic expression sql node's left son, error_code = %d.", left_parse.second);
    return std::make_pair(std::unique_ptr<Expression>(nullptr), left_parse.second);
    }

    std::pair<std::unique_ptr<Expression>, RC> right_parse = 
    build_expression(cur.right.get(), tables, table_map, query_fields, db_name);
    if(right_parse.second != RC::SUCCESS){
    LOG_WARN("Error when parsing arithmatic expression sql node's right son, error_code = %d.", right_parse.second);
    return std::make_pair(std::unique_ptr<Expression>(nullptr), right_parse.second);
    }
    
    ArithmeticExpr::Type result_type;
    // switch (cur.operation_type)
    // {
    //   case ArithSqlNode::Type::ADD:
    //     result_type = ArithmeticExpr::Type::ADD;
    //     break;
    //   case ArithSqlNode::Type::SUB:
    //     result_type = ArithmeticExpr::Type::SUB;
    //     break;
    //   case ArithSqlNode::Type::MUL:
    //     result_type = ArithmeticExpr::Type::MUL;
    //     break;
    //   case ArithSqlNode::Type::DIV:
    //     result_type = ArithmeticExpr::Type::DIV;
    //     break;
    //   case ArithSqlNode::Type::NEGATIVE:
    //     result_type = ArithmeticExpr::Type::NEGATIVE;
    //     break;
    //   default:
    //     LOG_WARN("Unknown operator type, type = %d.", cur.operation_type);
    //     return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::INVALID_ARGUMENT);
    //     break;
    // }
    
    std::unique_ptr<ArithmeticExpr> result(new ArithmeticExpr(static_cast<ArithmeticExpr::Type>(cur.operation_type), std::move(left_parse.first), std::move(right_parse.first)));
    result->set_name(cur.name);
    return std::make_pair(std::move(result), RC::SUCCESS);
  }
  default:
    LOG_WARN("invalid expression type. type = %d.", static_cast<int>(father->get_type()));
    return std::make_pair(std::unique_ptr<Expression>(nullptr), RC::INVALID_ARGUMENT);
  break;
  }
}