/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    UNIQUE = 263,                  /* UNIQUE  */
    INDEX = 264,                   /* INDEX  */
    CALC = 265,                    /* CALC  */
    MAX_FUNC = 266,                /* MAX_FUNC  */
    MIN_FUNC = 267,                /* MIN_FUNC  */
    COUNT_FUNC = 268,              /* COUNT_FUNC  */
    AVG_FUNC = 269,                /* AVG_FUNC  */
    SUM_FUNC = 270,                /* SUM_FUNC  */
    LENGTH_FUNC = 271,             /* LENGTH_FUNC  */
    ROUND_FUNC = 272,              /* ROUND_FUNC  */
    DATE_FORMAT_FUNC = 273,        /* DATE_FORMAT_FUNC  */
    SELECT = 274,                  /* SELECT  */
    DESC = 275,                    /* DESC  */
    SHOW = 276,                    /* SHOW  */
    SYNC = 277,                    /* SYNC  */
    INSERT = 278,                  /* INSERT  */
    DELETE = 279,                  /* DELETE  */
    UPDATE = 280,                  /* UPDATE  */
    LBRACE = 281,                  /* LBRACE  */
    RBRACE = 282,                  /* RBRACE  */
    COMMA = 283,                   /* COMMA  */
    TRX_BEGIN = 284,               /* TRX_BEGIN  */
    TRX_COMMIT = 285,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 286,            /* TRX_ROLLBACK  */
    INT_T = 287,                   /* INT_T  */
    STRING_T = 288,                /* STRING_T  */
    FLOAT_T = 289,                 /* FLOAT_T  */
    DATE_T = 290,                  /* DATE_T  */
    TEXT_T = 291,                  /* TEXT_T  */
    NULL_VAL = 292,                /* NULL_VAL  */
    HELP = 293,                    /* HELP  */
    EXIT = 294,                    /* EXIT  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    INNER = 298,                   /* INNER  */
    JOIN = 299,                    /* JOIN  */
    FROM = 300,                    /* FROM  */
    WHERE = 301,                   /* WHERE  */
    ORDER_BY = 302,                /* ORDER_BY  */
    ASC = 303,                     /* ASC  */
    AS = 304,                      /* AS  */
    AND = 305,                     /* AND  */
    NOT = 306,                     /* NOT  */
    SET = 307,                     /* SET  */
    ON = 308,                      /* ON  */
    LOAD = 309,                    /* LOAD  */
    DATA = 310,                    /* DATA  */
    INFILE = 311,                  /* INFILE  */
    EXPLAIN = 312,                 /* EXPLAIN  */
    LK = 313,                      /* LK  */
    EQ = 314,                      /* EQ  */
    LT = 315,                      /* LT  */
    GT = 316,                      /* GT  */
    LE = 317,                      /* LE  */
    GE = 318,                      /* GE  */
    NE = 319,                      /* NE  */
    IS_OP = 320,                   /* IS_OP  */
    IN_OP = 321,                   /* IN_OP  */
    EXIST_OP = 322,                /* EXIST_OP  */
    NUMBER = 323,                  /* NUMBER  */
    DATE = 324,                    /* DATE  */
    FLOAT = 325,                   /* FLOAT  */
    ID = 326,                      /* ID  */
    SSS = 327,                     /* SSS  */
    UMINUS = 328                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 136 "yacc_sql.y"

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

#line 160 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
