
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ArithSqlNode *create_complex_expression(ArithSqlNode::Type type,
                                        ExprSqlNode *left,
                                        ExprSqlNode *right,
                                        const char *sql_string,
                                        YYLTYPE *llocp)
{
  ArithSqlNode *expr = new ArithSqlNode(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}
%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        UNIQUE
        INDEX
        CALC
        MAX_FUNC
        MIN_FUNC
        COUNT_FUNC
        AVG_FUNC
        SUM_FUNC
        LENGTH_FUNC
        ROUND_FUNC
        DATE_FORMAT_FUNC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        NULL_VAL
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        INNER
        JOIN
        FROM
        WHERE
        ORDER_BY
        GROUP_BY
        HAVING
        ASC
        AS
        AND
        OR
        NOT
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        LK
        EQ
        LT
        GT
        LE
        GE
        NE
        IS_OP
        IN_OP
        EXIST_OP
        

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  ExprSqlNode *                     complex_expr;
  std::vector<std::unique_ptr<JoinSqlNode>> *  join_attr;
  std::vector<std::unique_ptr<ExprSqlNode>> *  complex_expr_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode*> *  condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<std::unique_ptr<OrderBySqlNode>> * order_by_list;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              bools;
}

%token <number> NUMBER
%token <number> DATE
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <value>               value_in_expr
%type <number>              number
%type <comp>                comp_op
%type <comp>                exist_op
%type <attr_infos>          attr_def_list
%type <number>              null_def
%type <attr_info>           attr_def
%type <string>              alias_attr
%type <value_list>          value_list
%type <value_list>          non_null_value_list
%type <relation_list>       from
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      on_attr
%type <order_by_list>       order_by_list
%type <order_by_list>       order_by_stmt
%type <bools>               order_type
%type <complex_expr_list>   select_attr
%type <complex_expr_list>   group_by_stmt
%type <condition_list>      having
%type <relation_list>       rel_list
%type <relation_list>       id_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <complex_expr>        complex_expr
%type <complex_expr_list>   complex_expr_list
%type <complex_expr>        possible_argument
%type <join_attr>           join_attr
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            create_select_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            set_variable_list
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | create_select_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.unique = false;
      create_index.relation_name = $5;
      if ($8 != nullptr) {
        create_index.attribute_name.swap(*$8);
        delete $8;
      }
      create_index.attribute_name.push_back(std::string($7));
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.unique = true;
      create_index.relation_name = $6;
      if ($9 != nullptr) {
        create_index.attribute_name.swap(*$9);
        delete $9;
      }
      create_index.attribute_name.push_back(std::string($8));
      free($4);
      free($6);
      free($8);
    }
    ;

id_list:
    /* empty */
    {
      $$ = nullptr; 
    }
    | COMMA ID id_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else $$ = new std::vector<std::string>;
      $$->emplace_back(std::string($2));
      free($2);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;

create_select_stmt:
    CREATE TABLE ID AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = $$->create_select;
      create_select.relation_name = $3;
      free($3);
      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>($5));
      
    }
    | CREATE TABLE ID select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = $$->create_select;
      create_select.relation_name = $3;
      free($3);
      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>($4));
      
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = $$->create_select;
      create_select.relation_name = $3;
      free($3);
      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_select.attr_infos.swap(*src_attrs);
      }
      create_select.attr_infos.emplace_back(*$5);
      std::reverse(create_select.attr_infos.begin(), create_select.attr_infos.end());
      delete $5;

      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>($9));
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = $$->create_select;
      create_select.relation_name = $3;
      free($3);
      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_select.attr_infos.swap(*src_attrs);
      }
      create_select.attr_infos.emplace_back(*$5);
      std::reverse(create_select.attr_infos.begin(), create_select.attr_infos.end());
      delete $5;

      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>($8));
    }
    ;

create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = (bool)$6;
      free($1);
    }
    | ID type null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $$->type == AttrType::TEXTS ? 0 : 4;
      $$->nullable = (bool)$3;
      free($1);
    }
    ;
null_def:
    /* empty */
    {
      $$ = 1;
    }
    | NOT NULL_VAL
    {
      $$ = 0;
    }
    | NULL_VAL
    {
      $$ = 1;
    }
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    | TEXT_T   { $$=TEXTS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

non_null_value_list:
    COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |'-' NUMBER{
      $$ = new Value(-(int)$2);
      @$ = @2;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATE {
      $$ = new Value((date_t)$1);
      @$ = @1;
    }
    |NULL_VAL {
      $$ = new Value((null_t)0);
      @$ = @1;
    }
    ;

value_in_expr:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATE {
      $$ = new Value((date_t)$1);
      @$ = @1;
    }
    |NULL_VAL {
      $$ = new Value((null_t)0);
      @$ = @1;
    }
    ;
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID set_variable_stmt where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.name.swap($3->set_variable.name);
      $$->update.value.swap($3->set_variable.value);
      $$->update.sub_select.swap($3->set_variable.sub_select);
      if ($4 != nullptr) {
        $$->update.conditions.swap(*$4);
        delete $4;
      }
      delete $3;
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr from join_attr where group_by_stmt having order_by_stmt
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }
      
      if ($3 != nullptr) {
        $$->selection.relations.swap(*$3);
        std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
        delete $3;
      }
      
      if ($4 != nullptr) {
        $$->selection.joins.swap(*$4);
        std:reverse($$->selection.joins.begin(), $$->selection.joins.end());
        delete $4;
      }
      
      if ($5 != nullptr) {
        $$->selection.conditions.swap(*$5);
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.group_by_fields.swap(*$6);
        delete $6;
      }
      
      if ($7 != nullptr) {
        $$->selection.having_conditions.swap(*$7);
        delete $7;
      }

      if ($8 != nullptr){
        $$->selection.orders.swap(*$8);
        delete $8;
      }
    }
    ;

from:
    /* empty */
    {
      $$ = nullptr;
    }
    | FROM ID alias_attr rel_list
    {
      $$ = new std::vector<std::string>;
      if ($4 != nullptr) {
        $$->swap(*$4);
        delete $4;
      }
      $$->push_back($2);
      if($3 != nullptr) {
        $$->push_back(std::string($3));
      } else $$->push_back(std::string(""));
      free($2);
    }
    ;

join_attr:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER JOIN ID alias_attr rel_list on_attr join_attr
    {
      if($7 != nullptr){
        $$ = $7;
      } else $$ = new std::vector<std::unique_ptr<JoinSqlNode>>;
      std::unique_ptr<JoinSqlNode> tmp(new JoinSqlNode);
      if ($5 != nullptr) {
        tmp->join_list.swap(*$5);
        delete $5;
      }
      tmp->join_list.push_back(std::string($3));
      if($4 != nullptr) {
        tmp->join_list.push_back(std::string($4));
        free($4);
      } else tmp->join_list.push_back(std::string(""));
      free($3);

      if($6 != nullptr) {
        tmp->on_conditions.swap(*$6);
        delete $6;
      }
      $$->push_back(std::move(tmp));
    }
    ;

on_attr:
    /* empty */
    {
      $$ = nullptr;
    }
    | ON condition_list
    {
      $$ = $2;
    }
    ;

group_by_stmt:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP_BY complex_expr complex_expr_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else $$ = new std::vector<std::unique_ptr<ExprSqlNode>>;

      $$->push_back(std::unique_ptr<ExprSqlNode>($2));
      std::reverse($$->begin(), $$->end());
    }
    ;

having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list
    {
      $$ = $2;
    }
    ;

order_by_stmt:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER_BY complex_expr order_type order_by_list
    {
      if($4 != nullptr){
        $$ = $4;
      } else $$ = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      $$->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode($2, $3)));
      std::reverse($$->begin(), $$->end());
    }
    ;

order_type:
    /* empty */
    {
      $$ = true;
    }
    | ASC
    {
      $$ = true;
    }
    | DESC
    {
      $$ = false;
    }
    ;

order_by_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA complex_expr order_type order_by_list
    {
    if ($4 != nullptr) {
      $$ = $4;
    } else $$ = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      $$->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode($2, $3)));
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value_in_expr {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;


complex_expr:
    MAX_FUNC LBRACE complex_expr RBRACE {
      $$ = new AggrSqlNode(function_type::AGGR_MAX, $3, token_name(sql_string, &@$));     
    }
    | MIN_FUNC LBRACE complex_expr RBRACE {
      $$ = new AggrSqlNode(function_type::AGGR_MIN, $3, token_name(sql_string, &@$));
    }
    | COUNT_FUNC LBRACE complex_expr RBRACE {
      $$ = new AggrSqlNode(function_type::AGGR_COUNT, $3, token_name(sql_string, &@$));
    }
    | AVG_FUNC LBRACE complex_expr RBRACE{
      $$ = new AggrSqlNode(function_type::AGGR_AVG, $3, token_name(sql_string, &@$));
    }
    | SUM_FUNC LBRACE complex_expr RBRACE {
      $$ = new AggrSqlNode(function_type::AGGR_SUM, $3, token_name(sql_string, &@$));
    }

    | LENGTH_FUNC LBRACE complex_expr RBRACE {
      $$ = new FuncSqlNode(function_type::FUNC_LENGTH, $3, nullptr, token_name(sql_string, &@$)); 
    }
    | ROUND_FUNC LBRACE complex_expr possible_argument RBRACE {
      $$ = new FuncSqlNode(function_type::FUNC_ROUND, $3, $4, token_name(sql_string, &@$));
    }
    | DATE_FORMAT_FUNC LBRACE complex_expr possible_argument RBRACE {
      $$ = new FuncSqlNode(function_type::FUNC_DATE_FORMAT, $3, $4, token_name(sql_string, &@$));
    }
    | ID {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name = "";
      tmp->attribute_name = $1;
      tmp->need_extract = false;
      free($1);
      $$ = tmp;
    }
    | ID DOT ID {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name  = $1;
      tmp->attribute_name = $3;
      tmp->need_extract = false;
      free($1);
      free($3);
      $$ = tmp;
    }
    | '*' {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      attr->need_extract = true;
      $$ = attr;
    }
    | ID DOT '*' {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = $1;
      free($1);
      attr->attribute_name = "*";
      attr->need_extract = true;
      $$ = attr;
    }
    | complex_expr '+' complex_expr {
      $$ = create_complex_expression(ArithSqlNode::Type::ADD, $1, $3, sql_string, &@$);
      $$->need_extract = false;
    }
    | complex_expr '-' complex_expr {
      $$ = create_complex_expression(ArithSqlNode::Type::SUB, $1, $3, sql_string, &@$);
      $$->need_extract = false;
    }
    | complex_expr '*' complex_expr {
      $$ = create_complex_expression(ArithSqlNode::Type::MUL, $1, $3, sql_string, &@$);
      $$->need_extract = false;
    }
    | complex_expr '/' complex_expr {
      $$ = create_complex_expression(ArithSqlNode::Type::DIV, $1, $3, sql_string, &@$);
      $$->need_extract = false;
    }
    | LBRACE complex_expr RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
      $$->need_extract = $2->need_extract;
    }
    | '-' complex_expr %prec UMINUS {
      if($2->get_type() == ExprSqlNode::Type::VALUE_EXPR){
        ValueSqlNode* tmp = (ValueSqlNode*)$2;
        tmp->val.make_negative();
        $$ = (ExprSqlNode*)tmp;
      }else $$ = create_complex_expression(ArithSqlNode::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
      $$->need_extract = $2->need_extract;
    }
    | value_in_expr
    {
      $$ = new ValueSqlNode(*$1);
      $$->set_name(token_name(sql_string, &@$));
      $$->need_extract = false;
      delete $1;
    }
    ;

possible_argument:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA complex_expr
    {
      $$ = $2;
    }
    ;
complex_expr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA complex_expr alias_attr complex_expr_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if($3 != nullptr) {
        $2->set_name(std::string($3), true);
      }
      $$->emplace_back(std::unique_ptr<ExprSqlNode>($2));
    }
    ;

select_attr:
    complex_expr alias_attr complex_expr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if($2 != nullptr) {
        $1->set_name(std::string($2), true);
      }
        
      $$->emplace_back(std::unique_ptr<ExprSqlNode>($1));
    }
    ;

alias_attr:
    /* empty */
    {
      $$ = nullptr;
    }
    | AS ID {
      $$ = $2;
    }
    | ID {
      $$ = $1;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID alias_attr rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->push_back($2);
      if($3 != nullptr) {
        $$->push_back(std::string($3));
      } else $$->push_back(std::string(""));

      free($2);
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2; 
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode*>;
      $$->emplace_back($1);
    }
    | condition AND condition_list {
      $$ = $3;
      $1->set_conj(false);
      $$->emplace_back($1);
    }
    | condition OR condition_list {
      $$ = $3;
      $1->set_conj(true);
      $$->emplace_back($1);
    }
    ;
condition:
    complex_expr comp_op complex_expr
    {
      $$ = new ConditionSqlNode($1, $3, $2);
    }
    | complex_expr comp_op LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode($1, $4, $2);
    }
    | LBRACE select_stmt RBRACE comp_op complex_expr
    {
      $$ = new ConditionSqlNode($5, $2, $4);
      $$->reverse_op();
    }
    | complex_expr comp_op LBRACE value non_null_value_list RBRACE
    {
      $5->emplace_back(*$4);
      delete $4;
      $$ = new ConditionSqlNode($1, $5, $2);
    }
    | LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE 
    {
      $$ = new ConditionSqlNode($2, $6, $4);
    }
    | exist_op LBRACE select_stmt RBRACE 
    {
      $$ = new ConditionSqlNode((ExprSqlNode*)nullptr, $3, $1);
    }
    ;

exist_op:
    EXIST_OP { $$ = EXIST;  }
    | NOT EXIST_OP { $$ = NOT_EXIST;  }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS_OP { $$ = IS; }
    | IS_OP NOT { $$ = IS_NOT; }
    | LK { $$ = LIKE;  }
    | NOT LK { $$ = NOT_LIKE;  }
    | IN_OP { $$ = IN; }
    | NOT IN_OP { $$ = NOT_IN; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value set_variable_list
    {
      if($5 == nullptr)
        $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      else $$ = $5;

      $$->set_variable.name.push_back(std::string($2));
      $$->set_variable.value.push_back(*$4);
      free($2);
      delete $4;
    }
    | SET ID EQ LBRACE select_stmt RBRACE set_variable_list
    {
      if($7 == nullptr)
        $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      else $$ = $7;

      $$->set_variable.name.push_back(std::string($2));
      $$->set_variable.value.push_back(Value());
      $$->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>($5));
      free($2);
    }
    ;

set_variable_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID EQ value set_variable_list
    {
      if($5 == nullptr)
        $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      else $$ = $5;

      $$->set_variable.name.push_back(std::string($2));
      $$->set_variable.value.push_back(*$4);
      free($2);
      delete $4;
    }
    | COMMA ID EQ LBRACE select_stmt RBRACE set_variable_list
    {
      if($7 == nullptr)
        $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      else $$ = $7;

      $$->set_variable.name.push_back(std::string($2));
      $$->set_variable.value.push_back(Value());
      $$->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>($5));
      free($2);
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
