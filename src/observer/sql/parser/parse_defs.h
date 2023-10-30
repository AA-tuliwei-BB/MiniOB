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
// Created by Meiyi
//

#pragma once

#include <stddef.h>
#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "sql/parser/value.h"
#include "common/rc.h"

class Expression;

/**
 * @defgroup SQLParser SQL Parser 
 */

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */

enum function_type{
  NO_FUNCTION,
  AGGR_MAX,
  AGGR_MIN,
  AGGR_COUNT,
  AGGR_AVG,
  AGGR_SUM,
  FUNC_LENGTH,
  FUNC_ROUND,
  FUNC_DATE_FORMAT,
};



struct ExprSqlNode{
  enum Type{
  VALUE_EXPR,
  REL_ATTR_EXPR,
  FUNC_EXPR,
  AGGR_FUNC_EXPR,
  ARITHMATIC_EXPR,
};
  ExprSqlNode() = default;
  virtual ~ExprSqlNode() = default;

  virtual ExprSqlNode::Type get_type() const = 0;
  virtual RC set_name(std::string n){
    name = n;
    return RC::SUCCESS;
  }
  std::string name;
  bool need_extract, is_aggregate;
};

struct ValueSqlNode : public ExprSqlNode
{
  Value val;
  ValueSqlNode(Value v):val(v) {
     is_aggregate = false;
     need_extract = false;
  }
  virtual ~ValueSqlNode() = default;
  ExprSqlNode::Type get_type() const{
     return VALUE_EXPR;
  };
  RC set_name(std::string n){
    if(!name.empty())
      return RC::SUCCESS;
    name = n;
    return RC::SUCCESS;
  }
};

struct RelAttrSqlNode : public ExprSqlNode
{
  std::string relation_name;   ///< relation name (may be NULL) 表名
  std::string attribute_name;  ///< attribute name              属性名
  RelAttrSqlNode(){
    is_aggregate = false;
    need_extract = false;
  }
  ExprSqlNode::Type get_type() const{
     return REL_ATTR_EXPR; 
  };
  RC set_name(bool table_disable){
    if(!name.empty())
      return RC::SUCCESS;
    if(relation_name.empty() || table_disable)
      name = attribute_name;
    else name = relation_name + '.' + attribute_name;
    return RC::SUCCESS;
  }
};

struct ArithSqlNode : public ExprSqlNode
{
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };
  std::unique_ptr<ExprSqlNode> left;
  std::unique_ptr<ExprSqlNode> right;
  ArithSqlNode::Type operation_type;

  ArithSqlNode(ArithSqlNode::Type t, ExprSqlNode* l, ExprSqlNode* r):operation_type(t), left(l), right(r) {
    if(operation_type == Type::NEGATIVE){
      need_extract = l->need_extract;
      is_aggregate = l->is_aggregate;
    }else{
      need_extract = l->need_extract || r->need_extract;
      is_aggregate = l->is_aggregate || r->is_aggregate;
    }
  }
  virtual ~ArithSqlNode() = default;
  ExprSqlNode::Type get_type() const{
     return ARITHMATIC_EXPR; 
  };
  RC set_name(std::string n){
    if(!name.empty())
      return RC::SUCCESS;
    name = n;
    return RC::SUCCESS;
  }
  RC set_name(){
    if(!name.empty()) return RC::SUCCESS;
    switch (operation_type) {
      case Type::ADD: {
        name =  left->name + "+" + right->name;
      } break;
      case Type::SUB: {
         name =  left->name + "-" + right->name;
      } break;
      case Type::MUL: {
         name =  left->name + "*" + right->name;
      } break;
      case Type::DIV: {
         name =  left->name + "/" + right->name;
      } break;
      case Type::NEGATIVE: {
         name =  "-" + left->name ;
      }
    }
    return RC::SUCCESS;
  }
};

struct AggrSqlNode : public ExprSqlNode{
  function_type func_type;
  std::unique_ptr<ExprSqlNode> son;
  // std::string function_name;
  AggrSqlNode(function_type t, ExprSqlNode* s, std::string n):func_type(t), son(s) {
    need_extract = (t == function_type::AGGR_COUNT) ? false : son->need_extract;
    is_aggregate = true;
    ExprSqlNode::set_name(n);
  }
  virtual ~AggrSqlNode() = default;
  ExprSqlNode::Type get_type() const{
     return AGGR_FUNC_EXPR; 
  };
  // RC set_name(){
  //   if(!name.empty())
  //     return RC::SUCCESS;
  //   name = function_name + "(" + son->name + ")";
  //   return RC::SUCCESS;
  // }
};

struct FuncSqlNode : public ExprSqlNode{
  function_type func_type;
  std::unique_ptr<ExprSqlNode> son, attr;
  // std::string function_name;
  FuncSqlNode(function_type t, ExprSqlNode* s, ExprSqlNode* a, std::string n):func_type(t), son(s), attr(a) {
    need_extract = son->need_extract;
    is_aggregate = son->is_aggregate;
    ExprSqlNode::set_name(n);
  }
  
  virtual ~FuncSqlNode() = default;
  ExprSqlNode::Type get_type() const{
     return FUNC_EXPR; 
  };
  // RC set_name(){
  //   if(!name.empty())
  //     return RC::SUCCESS;
  //   if(func_type == function_type::FUNC_LENGTH)
  //   name = function_name + "(" + son->name + ")";
  //   else name = function_name + "(" + son->name + "," + attr->name + ")";
  //   return RC::SUCCESS;
  // }
};

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp 
{
  EQUAL_TO,     ///< "="
  LESS_EQUAL,   ///< "<="
  NOT_EQUAL,    ///< "<>"
  LESS_THAN,    ///< "<"
  GREAT_EQUAL,  ///< ">="
  GREAT_THAN,   ///< ">"
  LIKE,         ///< LIKE
  NOT_LIKE,     ///< NOT_LIKE
  IS,           ///< IS
  IS_NOT,       ///< IS_NOT
  NO_OP
};

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode
{

  std::unique_ptr<ExprSqlNode>  left_expression;       ///<条件语句的左表达式          
  CompOp                        comp;                  ///< comparison operator
  std::unique_ptr<ExprSqlNode>  right_expression;      ///< 条件语句的右表达式
  ConditionSqlNode(ExprSqlNode* l, ExprSqlNode* r, CompOp c):left_expression(l), right_expression(r), comp(c) {}
  ConditionSqlNode(const ConditionSqlNode& other) = delete;
  ConditionSqlNode operator=(const ConditionSqlNode& other) = delete;
  ~ConditionSqlNode() = default;
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */

struct SelectSqlNode
{
  std::vector<std::unique_ptr<ExprSqlNode>>        expressions;    ///< expressions in select clause
  std::vector<std::string>        relations;     ///< 查询的表
  std::vector<ConditionSqlNode*>   conditions;    ///< 查询条件，使用AND串联起来多个条件
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<Expression *> expressions;  ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string        relation_name;  ///< Relation to insert into
  std::vector<Value> values;         ///< 要插入的值
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string                   relation_name;  ///< Relation to delete from
  std::vector<ConditionSqlNode*> conditions;
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string                   relation_name;         ///< Relation to update
  std::vector<std::string>      name;                  ///< 更新的字段的名称
  std::vector<Value>            value;                 ///< 更新的字段的值
  std::vector<ConditionSqlNode*> conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode
{
  AttrType    type;       ///< Type of attribute
  std::string name;       ///< Attribute name
  size_t      length;     ///< Length of attribute
  bool        nullable = false;  ///< Whether attribute can be null value
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string                  relation_name;         ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;            ///< attributes
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  std::string index_name;      ///< Index name
  std::string relation_name;   ///< Relation name
  std::string attribute_name;  ///< Attribute name
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  // vector<std::pair<std::string, Value>> val_list;
  std::vector<std::string> name;
  std::vector<Value>       value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int         line;
  int         column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,        ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE, ///< 设置变量
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag       flag;
  ErrorSqlNode              error;
  CalcSqlNode               calc;
  SelectSqlNode             selection;
  InsertSqlNode             insertion;
  DeleteSqlNode             deletion;
  UpdateSqlNode             update;
  CreateTableSqlNode        create_table;
  DropTableSqlNode          drop_table;
  CreateIndexSqlNode        create_index;
  DropIndexSqlNode          drop_index;
  DescTableSqlNode          desc_table;
  LoadDataSqlNode           load_data;
  ExplainSqlNode            explain;
  SetVariableSqlNode        set_variable;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes()
  {
    return sql_nodes_;
  }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
