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
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    MAX_FUNC = 265,                /* MAX_FUNC  */
    MIN_FUNC = 266,                /* MIN_FUNC  */
    COUNT_FUNC = 267,              /* COUNT_FUNC  */
    AVG_FUNC = 268,                /* AVG_FUNC  */
    SUM_FUNC = 269,                /* SUM_FUNC  */
    LENGTH_FUNC = 270,             /* LENGTH_FUNC  */
    ROUND_FUNC = 271,              /* ROUND_FUNC  */
    DATE_FORMAT_FUNC = 272,        /* DATE_FORMAT_FUNC  */
    SELECT = 273,                  /* SELECT  */
    DESC = 274,                    /* DESC  */
    SHOW = 275,                    /* SHOW  */
    SYNC = 276,                    /* SYNC  */
    INSERT = 277,                  /* INSERT  */
    DELETE = 278,                  /* DELETE  */
    UPDATE = 279,                  /* UPDATE  */
    LBRACE = 280,                  /* LBRACE  */
    RBRACE = 281,                  /* RBRACE  */
    COMMA = 282,                   /* COMMA  */
    TRX_BEGIN = 283,               /* TRX_BEGIN  */
    TRX_COMMIT = 284,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 285,            /* TRX_ROLLBACK  */
    INT_T = 286,                   /* INT_T  */
    STRING_T = 287,                /* STRING_T  */
    FLOAT_T = 288,                 /* FLOAT_T  */
    DATE_T = 289,                  /* DATE_T  */
    NULL_VAL = 290,                /* NULL_VAL  */
    HELP = 291,                    /* HELP  */
    EXIT = 292,                    /* EXIT  */
    DOT = 293,                     /* DOT  */
    INTO = 294,                    /* INTO  */
    VALUES = 295,                  /* VALUES  */
    FROM = 296,                    /* FROM  */
    WHERE = 297,                   /* WHERE  */
    AS = 298,                      /* AS  */
    AND = 299,                     /* AND  */
    NOT = 300,                     /* NOT  */
    SET = 301,                     /* SET  */
    ON = 302,                      /* ON  */
    LOAD = 303,                    /* LOAD  */
    DATA = 304,                    /* DATA  */
    INFILE = 305,                  /* INFILE  */
    EXPLAIN = 306,                 /* EXPLAIN  */
    LK = 307,                      /* LK  */
    EQ = 308,                      /* EQ  */
    LT = 309,                      /* LT  */
    GT = 310,                      /* GT  */
    LE = 311,                      /* LE  */
    GE = 312,                      /* GE  */
    NE = 313,                      /* NE  */
    NUMBER = 314,                  /* NUMBER  */
    DATE = 315,                    /* DATE  */
    FLOAT = 316,                   /* FLOAT  */
    ID = 317,                      /* ID  */
    SSS = 318,                     /* SSS  */
    UMINUS = 319                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  ExprSqlNode *                     complex_expr;
  std::vector<std::unique_ptr<ExprSqlNode>> *  complex_expr_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode*> *  condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  char *                            string;
  int                               number;
  float                             floats;

#line 148 "yacc_sql.hpp"

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
