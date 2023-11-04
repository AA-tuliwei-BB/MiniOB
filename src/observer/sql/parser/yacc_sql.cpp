/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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

#line 126 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_UNIQUE = 8,                     /* UNIQUE  */
  YYSYMBOL_INDEX = 9,                      /* INDEX  */
  YYSYMBOL_CALC = 10,                      /* CALC  */
  YYSYMBOL_MAX_FUNC = 11,                  /* MAX_FUNC  */
  YYSYMBOL_MIN_FUNC = 12,                  /* MIN_FUNC  */
  YYSYMBOL_COUNT_FUNC = 13,                /* COUNT_FUNC  */
  YYSYMBOL_AVG_FUNC = 14,                  /* AVG_FUNC  */
  YYSYMBOL_SUM_FUNC = 15,                  /* SUM_FUNC  */
  YYSYMBOL_LENGTH_FUNC = 16,               /* LENGTH_FUNC  */
  YYSYMBOL_ROUND_FUNC = 17,                /* ROUND_FUNC  */
  YYSYMBOL_DATE_FORMAT_FUNC = 18,          /* DATE_FORMAT_FUNC  */
  YYSYMBOL_SELECT = 19,                    /* SELECT  */
  YYSYMBOL_DESC = 20,                      /* DESC  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_STRING_T = 33,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 34,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 35,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 36,                    /* TEXT_T  */
  YYSYMBOL_NULL_VAL = 37,                  /* NULL_VAL  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_INNER = 43,                     /* INNER  */
  YYSYMBOL_JOIN = 44,                      /* JOIN  */
  YYSYMBOL_FROM = 45,                      /* FROM  */
  YYSYMBOL_WHERE = 46,                     /* WHERE  */
  YYSYMBOL_ORDER_BY = 47,                  /* ORDER_BY  */
  YYSYMBOL_GROUP_BY = 48,                  /* GROUP_BY  */
  YYSYMBOL_HAVING = 49,                    /* HAVING  */
  YYSYMBOL_ASC = 50,                       /* ASC  */
  YYSYMBOL_AS = 51,                        /* AS  */
  YYSYMBOL_AND = 52,                       /* AND  */
  YYSYMBOL_OR = 53,                        /* OR  */
  YYSYMBOL_NOT = 54,                       /* NOT  */
  YYSYMBOL_SET = 55,                       /* SET  */
  YYSYMBOL_ON = 56,                        /* ON  */
  YYSYMBOL_LOAD = 57,                      /* LOAD  */
  YYSYMBOL_DATA = 58,                      /* DATA  */
  YYSYMBOL_INFILE = 59,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 60,                   /* EXPLAIN  */
  YYSYMBOL_LK = 61,                        /* LK  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_LT = 63,                        /* LT  */
  YYSYMBOL_GT = 64,                        /* GT  */
  YYSYMBOL_LE = 65,                        /* LE  */
  YYSYMBOL_GE = 66,                        /* GE  */
  YYSYMBOL_NE = 67,                        /* NE  */
  YYSYMBOL_IS_OP = 68,                     /* IS_OP  */
  YYSYMBOL_IN_OP = 69,                     /* IN_OP  */
  YYSYMBOL_EXIST_OP = 70,                  /* EXIST_OP  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_DATE = 72,                      /* DATE  */
  YYSYMBOL_FLOAT = 73,                     /* FLOAT  */
  YYSYMBOL_ID = 74,                        /* ID  */
  YYSYMBOL_SSS = 75,                       /* SSS  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '-'  */
  YYSYMBOL_78_ = 78,                       /* '*'  */
  YYSYMBOL_79_ = 79,                       /* '/'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command_wrapper = 83,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 84,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 85,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 86,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 87,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 88,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 89,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 90,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 91,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 92,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 93,         /* create_index_stmt  */
  YYSYMBOL_id_list = 94,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 95,           /* drop_index_stmt  */
  YYSYMBOL_create_select_stmt = 96,        /* create_select_stmt  */
  YYSYMBOL_create_table_stmt = 97,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_null_def = 100,                 /* null_def  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_insert_stmt = 103,              /* insert_stmt  */
  YYSYMBOL_value_list = 104,               /* value_list  */
  YYSYMBOL_non_null_value_list = 105,      /* non_null_value_list  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_value_in_expr = 107,            /* value_in_expr  */
  YYSYMBOL_delete_stmt = 108,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 109,              /* update_stmt  */
  YYSYMBOL_select_stmt = 110,              /* select_stmt  */
  YYSYMBOL_from = 111,                     /* from  */
  YYSYMBOL_join_attr = 112,                /* join_attr  */
  YYSYMBOL_on_attr = 113,                  /* on_attr  */
  YYSYMBOL_group_by_stmt = 114,            /* group_by_stmt  */
  YYSYMBOL_having = 115,                   /* having  */
  YYSYMBOL_order_by_stmt = 116,            /* order_by_stmt  */
  YYSYMBOL_order_type = 117,               /* order_type  */
  YYSYMBOL_order_by_list = 118,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_complex_expr = 122,             /* complex_expr  */
  YYSYMBOL_possible_argument = 123,        /* possible_argument  */
  YYSYMBOL_complex_expr_list = 124,        /* complex_expr_list  */
  YYSYMBOL_select_attr = 125,              /* select_attr  */
  YYSYMBOL_alias_attr = 126,               /* alias_attr  */
  YYSYMBOL_rel_list = 127,                 /* rel_list  */
  YYSYMBOL_where = 128,                    /* where  */
  YYSYMBOL_condition_list = 129,           /* condition_list  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_exist_op = 131,                 /* exist_op  */
  YYSYMBOL_comp_op = 132,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 133,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 134,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 135,        /* set_variable_stmt  */
  YYSYMBOL_set_variable_list = 136,        /* set_variable_list  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   489

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  332

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   232,   232,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   264,   270,   275,   281,   287,   293,
     299,   306,   312,   320,   336,   356,   359,   370,   381,   390,
     399,   416,   436,   455,   458,   471,   480,   492,   495,   499,
     504,   507,   508,   509,   510,   511,   514,   530,   533,   545,
     556,   560,   564,   568,   573,   577,   584,   588,   592,   597,
     601,   607,   619,   634,   678,   681,   698,   701,   728,   731,
     739,   742,   755,   758,   766,   769,   782,   785,   789,   797,
     800,   810,   820,   825,   836,   839,   842,   845,   848,   852,
     855,   864,   867,   870,   873,   876,   880,   883,   886,   889,
     897,   906,   913,   921,   925,   929,   933,   937,   942,   950,
     961,   964,   971,   974,   988,  1004,  1007,  1010,  1017,  1020,
    1036,  1039,  1045,  1048,  1052,  1057,  1064,  1068,  1072,  1077,
    1083,  1087,  1094,  1095,  1099,  1100,  1101,  1102,  1103,  1104,
    1105,  1106,  1107,  1108,  1109,  1110,  1114,  1127,  1135,  1146,
    1161,  1164,  1175,  1188,  1189
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "UNIQUE", "INDEX", "CALC", "MAX_FUNC",
  "MIN_FUNC", "COUNT_FUNC", "AVG_FUNC", "SUM_FUNC", "LENGTH_FUNC",
  "ROUND_FUNC", "DATE_FORMAT_FUNC", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "NULL_VAL", "HELP", "EXIT", "DOT", "INTO", "VALUES", "INNER",
  "JOIN", "FROM", "WHERE", "ORDER_BY", "GROUP_BY", "HAVING", "ASC", "AS",
  "AND", "OR", "NOT", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "LK", "EQ", "LT", "GT", "LE", "GE", "NE", "IS_OP", "IN_OP", "EXIST_OP",
  "NUMBER", "DATE", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "id_list", "drop_index_stmt", "create_select_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "null_def", "number",
  "type", "insert_stmt", "value_list", "non_null_value_list", "value",
  "value_in_expr", "delete_stmt", "update_stmt", "select_stmt", "from",
  "join_attr", "on_attr", "group_by_stmt", "having", "order_by_stmt",
  "order_type", "order_by_list", "calc_stmt", "expression_list",
  "expression", "complex_expr", "possible_argument", "complex_expr_list",
  "select_attr", "alias_attr", "rel_list", "where", "condition_list",
  "condition", "exist_op", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "set_variable_list", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-276)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-66)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     379,   139,    25,   -13,   251,   -55,    23,  -276,    -5,    27,
       0,  -276,  -276,  -276,  -276,  -276,     2,    20,   379,    99,
     100,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,    37,   123,    60,    72,    87,   -13,  -276,  -276,
    -276,  -276,  -276,   -13,  -276,  -276,   140,   136,   137,   138,
     143,   144,   147,   149,   150,   251,   109,   251,  -276,  -276,
      59,   121,  -276,  -276,    97,   103,   126,   116,   134,  -276,
    -276,  -276,  -276,    -3,   129,   154,  -276,   156,   -25,  -276,
     -13,   -13,   -13,   -13,   -13,   251,   251,   251,   251,   251,
     251,   251,   251,    11,   -57,  -276,   151,  -276,   251,   251,
     251,   251,   180,   159,   170,   172,   188,   188,   369,   160,
     162,   222,  -276,   186,   169,   197,  -276,  -276,     3,     3,
    -276,  -276,    43,    75,    81,   128,   145,   152,   161,   161,
    -276,  -276,  -276,  -276,    39,    39,  -276,  -276,   251,  -276,
     -18,   228,   188,   247,   113,  -276,  -276,   222,  -276,  -276,
    -276,  -276,  -276,   205,   258,   234,   257,   259,  -276,   211,
     253,  -276,  -276,  -276,  -276,  -276,  -276,  -276,   251,   267,
     269,    59,   270,   223,   254,   -30,   183,   229,  -276,   410,
    -276,    13,   277,   282,  -276,   272,  -276,   315,  -276,  -276,
    -276,  -276,  -276,   -15,   162,   316,   318,   273,    64,  -276,
    -276,   180,   274,  -276,   -18,   251,   300,   322,   324,  -276,
     -41,  -276,  -276,  -276,  -276,  -276,  -276,  -276,   298,  -276,
     301,   113,   113,   222,   258,   291,   280,   284,  -276,   320,
    -276,   259,    -1,   285,   330,  -276,   -18,   270,   204,   113,
     313,   -30,   334,   389,  -276,  -276,  -276,   233,    64,  -276,
    -276,   343,  -276,   390,  -276,  -276,   344,  -276,  -276,   222,
    -276,   330,   306,   354,   270,   326,  -276,  -276,   251,  -276,
     322,  -276,   319,   357,   358,   359,   377,   383,   351,   384,
     380,  -276,   222,   258,   -22,  -276,   386,   330,  -276,  -276,
     113,   170,     7,  -276,   183,    64,   387,   -30,   392,  -276,
     393,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,   402,
     394,   322,  -276,   258,   251,  -276,  -276,  -276,  -276,     7,
     402,  -276
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     163,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     9,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    70,    66,
      69,    67,    68,     0,   100,    91,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,     0,   111,   119,
     125,    74,    32,    31,     0,     0,     0,     0,     0,   157,
       1,   164,     2,     0,     0,     0,    30,     0,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,   127,     0,     0,
       0,     0,   122,     0,    76,     0,   130,   130,     0,     0,
       0,     0,    39,     0,     0,     0,    98,    93,    94,    95,
      96,    97,     0,     0,     0,     0,     0,     0,   120,   120,
     117,   110,   112,   126,   113,   114,   115,   116,     0,   124,
     125,     0,   130,     0,   132,    71,    72,     0,    65,    60,
      64,    62,    63,     0,   160,     0,     0,    43,    38,     0,
       0,    37,   101,   102,   103,   104,   105,   106,     0,     0,
       0,   125,   128,     0,    80,     0,     0,     0,   142,     0,
     131,   133,     0,     0,    61,     0,   158,     0,    51,    52,
      53,    54,    55,    47,     0,     0,     0,     0,   121,   107,
     108,   122,     0,    75,   125,     0,    82,    57,     0,   143,
       0,   152,   144,   145,   146,   147,   148,   149,   150,   154,
       0,   132,   132,     0,   160,     0,     0,     0,    49,     0,
      46,    43,    42,     0,    35,   123,   125,   128,   122,   132,
      84,     0,     0,     0,   153,   155,   151,     0,   136,   134,
     135,     0,   159,     0,   156,    50,     0,    48,    44,     0,
      41,    35,     0,     0,   128,    78,    81,    83,     0,    73,
      57,    56,     0,    70,    66,    69,    67,    68,     0,     0,
       0,   141,     0,   160,    47,    40,     0,    35,    33,   129,
     132,    76,    86,    58,     0,   138,    66,     0,     0,   137,
       0,   161,    45,    34,    36,    79,    77,    88,    87,    89,
       0,    57,   139,   160,     0,    85,   140,    59,   162,    86,
      89,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -276,  -276,   396,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -242,  -276,  -276,  -276,   190,   231,   153,
    -276,  -276,  -276,  -275,  -276,  -184,    22,  -276,  -276,   -77,
    -276,   131,  -276,  -276,  -276,  -276,   104,   107,  -276,   348,
     248,    -4,   309,  -208,  -276,  -146,  -237,  -103,  -223,  -276,
    -276,   192,  -276,  -276,   373,  -222,  -276
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   273,    31,    32,    33,   205,   167,   240,
     266,   203,    34,   252,   308,   164,    69,    35,    36,    37,
     114,   152,   301,   216,   250,   279,   319,   325,    38,    55,
      56,   189,   179,   149,    71,   112,   213,   155,   190,   191,
     192,   230,    39,    40,    41,   196,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   217,   126,   245,   182,   303,   122,   158,   259,   260,
     275,   237,   262,    47,   156,   238,     4,   141,     4,    72,
     254,   142,   238,   120,    48,    54,   277,   317,   255,   296,
      73,    45,   239,   106,    46,   211,    74,   299,   140,   239,
     276,   159,   160,   161,   168,   162,   327,   163,   121,   184,
     269,    91,    92,    93,    94,   314,   107,   318,    49,    50,
      51,   103,    52,   105,    53,   231,   232,   280,   247,    54,
     172,   311,    75,   289,    76,    54,    77,   315,    78,   293,
     193,    93,    94,   108,   109,   110,   111,   108,   109,   110,
     111,   132,   133,   134,   135,   136,   137,   138,   139,    80,
     274,   328,   173,    81,   144,   145,   146,   147,   174,   218,
     106,    83,    54,    54,    54,    54,    54,   110,   111,   108,
     109,   110,   111,   321,    57,    58,    59,    60,    61,    62,
      63,    64,    84,   107,    85,   108,   109,   110,   111,   186,
     108,   109,   110,   111,   181,    42,    86,    43,    44,   104,
      48,   108,   109,   110,   111,   175,   261,   108,   109,   110,
     111,    87,    95,    96,    97,   270,   113,   187,    90,    98,
      99,   115,   176,   100,   208,   101,   102,   116,   118,   177,
     290,    16,   103,   188,    49,    50,    51,    66,    52,   178,
      67,    68,   295,   119,    57,    58,    59,    60,    61,    62,
      63,    64,     4,   123,   108,   109,   110,   111,   148,    65,
     124,   248,   125,   151,   153,   310,    91,    92,    93,    94,
      48,   108,   109,   110,   111,   143,   258,   320,   108,   109,
     110,   111,   148,   150,   154,   165,   166,   108,   109,   110,
     111,     4,   169,   170,    57,    58,    59,    60,    61,    62,
      63,    64,     4,   103,    49,    50,    51,    66,    52,    65,
      67,    68,    57,    58,    59,    60,    61,    62,    63,    64,
     283,   171,   183,   185,   302,   197,   194,    65,   305,   207,
     108,   109,   110,   111,   105,   206,   195,   204,    48,   198,
     199,   200,   201,   202,   209,    88,   210,   214,   212,   219,
     103,    89,   215,   233,   284,   285,   286,    66,   287,   234,
     288,    68,    57,    58,    59,    60,    61,    62,    63,    64,
     329,   236,    49,    50,    51,    66,    52,   257,    67,    68,
      57,    58,    59,    60,    61,    62,    63,    64,    48,   128,
     129,   130,   131,   242,   243,   304,   235,   244,   246,   249,
     251,   253,   256,   263,   264,   265,    48,   267,   272,   271,
     278,   281,    57,    58,    59,    60,    61,    62,    63,    64,
     291,   294,    49,    50,    51,    66,    52,    65,    67,    68,
     297,   298,   300,     1,     2,   -65,   -60,   -64,    48,     3,
      49,    50,    51,    66,    52,   157,    67,    68,     4,     5,
       6,     7,     8,     9,    10,   -62,   158,   309,    11,    12,
      13,   -63,   307,   313,    79,   -61,   292,    14,    15,   322,
     323,   326,   306,    50,    51,    66,    52,   158,    67,    68,
     324,   268,   316,   330,    16,   241,    17,   331,   127,    18,
     159,   160,   161,   220,   162,   282,   163,   312,   180,   117,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,   159,   160,   161,   220,   162,     0,   163,     0,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111
};

static const yytype_int16 yycheck[] =
{
       4,   185,    27,   211,   150,   280,    83,    37,   231,   232,
     247,    26,   234,    26,   117,    37,    19,    74,    19,    74,
      61,    78,    37,    26,    37,     3,   249,    20,    69,   271,
       7,     6,    54,    51,     9,   181,    41,   274,    27,    54,
     248,    71,    72,    73,   121,    75,   321,    77,    51,   152,
      51,    76,    77,    78,    79,   297,    74,    50,    71,    72,
      73,    65,    75,    67,    77,    52,    53,   251,   214,    47,
      27,   293,    45,   257,    74,    53,    74,   300,    58,   263,
     157,    78,    79,    76,    77,    78,    79,    76,    77,    78,
      79,    95,    96,    97,    98,    99,   100,   101,   102,     0,
     246,   323,    27,     3,   108,   109,   110,   111,    27,   186,
      51,    74,    90,    91,    92,    93,    94,    78,    79,    76,
      77,    78,    79,   307,    11,    12,    13,    14,    15,    16,
      17,    18,     9,    74,    74,    76,    77,    78,    79,    26,
      76,    77,    78,    79,   148,     6,    74,     8,     9,    40,
      37,    76,    77,    78,    79,    27,   233,    76,    77,    78,
      79,    74,    26,    26,    26,   242,    45,    54,    28,    26,
      26,    74,    27,    26,   178,    26,    26,    74,    62,    27,
     257,    55,   186,    70,    71,    72,    73,    74,    75,    28,
      77,    78,   269,    59,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    74,    76,    77,    78,    79,    28,    26,
      56,   215,    56,    43,    42,   292,    76,    77,    78,    79,
      37,    76,    77,    78,    79,    74,   230,   304,    76,    77,
      78,    79,    28,    74,    46,    75,    74,    76,    77,    78,
      79,    19,    56,    74,    11,    12,    13,    14,    15,    16,
      17,    18,    19,   257,    71,    72,    73,    74,    75,    26,
      77,    78,    11,    12,    13,    14,    15,    16,    17,    18,
      37,    74,    44,    26,   278,    41,    71,    26,   282,    26,
      76,    77,    78,    79,   288,    74,    28,    28,    37,    32,
      33,    34,    35,    36,    27,    47,    27,    74,    28,    70,
     304,    53,    48,    26,    71,    72,    73,    74,    75,    27,
      77,    78,    11,    12,    13,    14,    15,    16,    17,    18,
     324,     6,    71,    72,    73,    74,    75,    26,    77,    78,
      11,    12,    13,    14,    15,    16,    17,    18,    37,    91,
      92,    93,    94,    27,    26,    26,    74,    74,    74,    49,
      28,    27,    54,    62,    74,    71,    37,    37,    28,    74,
      47,    27,    11,    12,    13,    14,    15,    16,    17,    18,
      27,    27,    71,    72,    73,    74,    75,    26,    77,    78,
      74,    27,    56,     4,     5,    28,    28,    28,    37,    10,
      71,    72,    73,    74,    75,    26,    77,    78,    19,    20,
      21,    22,    23,    24,    25,    28,    37,    27,    29,    30,
      31,    28,    28,    27,    18,    28,    26,    38,    39,    27,
      27,    27,    71,    72,    73,    74,    75,    37,    77,    78,
      28,   241,   301,   329,    55,   204,    57,   330,    90,    60,
      71,    72,    73,    54,    75,   253,    77,   294,   139,    76,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    71,    72,    73,    54,    75,    -1,    77,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    19,    20,    21,    22,    23,    24,
      25,    29,    30,    31,    38,    39,    55,    57,    60,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    95,    96,    97,   103,   108,   109,   110,   119,   133,
     134,   135,     6,     8,     9,     6,     9,    26,    37,    71,
      72,    73,    75,    77,   107,   120,   121,    11,    12,    13,
      14,    15,    16,    17,    18,    26,    74,    77,    78,   107,
     122,   125,    74,     7,    41,    45,    74,    74,    58,    83,
       0,     3,   137,    74,     9,    74,    74,    74,   121,   121,
      28,    76,    77,    78,    79,    26,    26,    26,    26,    26,
      26,    26,    26,   122,    40,   122,    51,    74,    76,    77,
      78,    79,   126,    45,   111,    74,    74,   135,    62,    59,
      26,    51,   110,    74,    56,    56,    27,   120,   121,   121,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
      27,    74,    78,    74,   122,   122,   122,   122,    28,   124,
      74,    43,   112,    42,    46,   128,   128,    26,    37,    71,
      72,    73,    75,    77,   106,    75,    74,    99,   110,    56,
      74,    74,    27,    27,    27,    27,    27,    27,    28,   123,
     123,   122,   126,    44,   128,    26,    26,    54,    70,   122,
     129,   130,   131,   110,    71,    28,   136,    41,    32,    33,
      34,    35,    36,   102,    28,    98,    74,    26,   122,    27,
      27,   126,    28,   127,    74,    48,   114,   106,   110,    70,
      54,    61,    62,    63,    64,    65,    66,    67,    68,    69,
     132,    52,    53,    26,    27,    74,     6,    26,    37,    54,
     100,    99,    27,    26,    74,   124,    74,   126,   122,    49,
     115,    28,   104,    27,    61,    69,    54,    26,   122,   129,
     129,   110,   136,    62,    74,    71,   101,    37,    98,    51,
     110,    74,    28,    94,   126,   127,   124,   129,    47,   116,
     106,    27,   132,    37,    71,    72,    73,    75,    77,   106,
     110,    27,    26,   106,    27,   110,    94,    74,    27,   127,
      56,   113,   122,   104,    26,   122,    71,    28,   105,    27,
     110,   136,   100,    27,    94,   129,   112,    20,    50,   117,
     110,   106,    27,    27,    28,   118,    27,   104,   136,   122,
     117,   118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    96,    96,
      96,    96,    97,    98,    98,    99,    99,   100,   100,   100,
     101,   102,   102,   102,   102,   102,   103,   104,   104,   105,
     106,   106,   106,   106,   106,   106,   107,   107,   107,   107,
     107,   108,   109,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   117,   118,
     118,   119,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   124,   124,   125,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   133,   134,   135,   135,
     136,   136,   136,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     5,     4,
       9,     8,     7,     0,     3,     6,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     8,     0,     3,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     8,     0,     4,     0,     7,     0,     2,
       0,     3,     0,     2,     0,     4,     0,     1,     1,     0,
       4,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     4,     4,     4,     4,     4,     4,     5,     5,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     2,     1,
       0,     2,     0,     4,     3,     0,     2,     1,     0,     4,
       0,     2,     0,     1,     3,     3,     3,     5,     5,     6,
       7,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     7,     2,     5,     7,
       0,     5,     7,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 233 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1923 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 264 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 270 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1940 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 275 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1948 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 281 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1956 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 287 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 293 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 299 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1982 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 306 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1990 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 312 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2000 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.unique = false;
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      create_index.attribute_name.push_back(std::string((yyvsp[-2].string)));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 337 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.unique = true;
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      create_index.attribute_name.push_back(std::string((yyvsp[-2].string)));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2040 "yacc_sql.cpp"
    break;

  case 35: /* id_list: %empty  */
#line 356 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr; 
    }
#line 2048 "yacc_sql.cpp"
    break;

  case 36: /* id_list: COMMA ID id_list  */
#line 360 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else (yyval.relation_list) = new std::vector<std::string>;
      (yyval.relation_list)->emplace_back(std::string((yyvsp[-1].string)));
      free((yyvsp[-1].string));
    }
#line 2060 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 371 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 38: /* create_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 382 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = (yyval.sql_node)->create_select;
      create_select.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node)));
      
    }
#line 2085 "yacc_sql.cpp"
    break;

  case 39: /* create_select_stmt: CREATE TABLE ID select_stmt  */
#line 391 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = (yyval.sql_node)->create_select;
      create_select.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node)));
      
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 40: /* create_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 400 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = (yyval.sql_node)->create_select;
      create_select.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));
      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_select.attr_infos.swap(*src_attrs);
      }
      create_select.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_select.attr_infos.begin(), create_select.attr_infos.end());
      delete (yyvsp[-4].attr_info);

      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node)));
    }
#line 2119 "yacc_sql.cpp"
    break;

  case 41: /* create_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 417 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = (yyval.sql_node)->create_select;
      create_select.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));
      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_select.attr_infos.swap(*src_attrs);
      }
      create_select.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_select.attr_infos.begin(), create_select.attr_infos.end());
      delete (yyvsp[-3].attr_info);

      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node)));
    }
#line 2140 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 437 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2160 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: %empty  */
#line 455 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2168 "yacc_sql.cpp"
    break;

  case 44: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 459 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 472 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type null_def  */
#line 481 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = (yyval.attr_info)->type == AttrType::TEXTS ? 0 : 4;
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 47: /* null_def: %empty  */
#line 492 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 48: /* null_def: NOT NULL_VAL  */
#line 496 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2224 "yacc_sql.cpp"
    break;

  case 49: /* null_def: NULL_VAL  */
#line 500 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2232 "yacc_sql.cpp"
    break;

  case 50: /* number: NUMBER  */
#line 504 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2238 "yacc_sql.cpp"
    break;

  case 51: /* type: INT_T  */
#line 507 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2244 "yacc_sql.cpp"
    break;

  case 52: /* type: STRING_T  */
#line 508 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2250 "yacc_sql.cpp"
    break;

  case 53: /* type: FLOAT_T  */
#line 509 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2256 "yacc_sql.cpp"
    break;

  case 54: /* type: DATE_T  */
#line 510 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2262 "yacc_sql.cpp"
    break;

  case 55: /* type: TEXT_T  */
#line 511 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2268 "yacc_sql.cpp"
    break;

  case 56: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 515 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2284 "yacc_sql.cpp"
    break;

  case 57: /* value_list: %empty  */
#line 530 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 533 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2306 "yacc_sql.cpp"
    break;

  case 59: /* non_null_value_list: COMMA value value_list  */
#line 545 "yacc_sql.y"
                            { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 556 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2329 "yacc_sql.cpp"
    break;

  case 61: /* value: '-' NUMBER  */
#line 560 "yacc_sql.y"
               {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2338 "yacc_sql.cpp"
    break;

  case 62: /* value: FLOAT  */
#line 564 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2347 "yacc_sql.cpp"
    break;

  case 63: /* value: SSS  */
#line 568 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2357 "yacc_sql.cpp"
    break;

  case 64: /* value: DATE  */
#line 573 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 65: /* value: NULL_VAL  */
#line 577 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 66: /* value_in_expr: NUMBER  */
#line 584 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2384 "yacc_sql.cpp"
    break;

  case 67: /* value_in_expr: FLOAT  */
#line 588 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2393 "yacc_sql.cpp"
    break;

  case 68: /* value_in_expr: SSS  */
#line 592 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2403 "yacc_sql.cpp"
    break;

  case 69: /* value_in_expr: DATE  */
#line 597 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2412 "yacc_sql.cpp"
    break;

  case 70: /* value_in_expr: NULL_VAL  */
#line 601 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2421 "yacc_sql.cpp"
    break;

  case 71: /* delete_stmt: DELETE FROM ID where  */
#line 608 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 72: /* update_stmt: UPDATE ID set_variable_stmt where  */
#line 620 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->update.name.swap((yyvsp[-1].sql_node)->set_variable.name);
      (yyval.sql_node)->update.value.swap((yyvsp[-1].sql_node)->set_variable.value);
      (yyval.sql_node)->update.sub_select.swap((yyvsp[-1].sql_node)->set_variable.sub_select);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      delete (yyvsp[-1].sql_node);
    }
#line 2452 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT select_attr from join_attr where group_by_stmt having order_by_stmt  */
#line 635 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].complex_expr_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].complex_expr_list));
        delete (yyvsp[-6].complex_expr_list);
      }
      
      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
        delete (yyvsp[-5].relation_list);
      }
      
      if ((yyvsp[-4].join_attr) != nullptr) {
        (yyval.sql_node)->selection.joins.swap(*(yyvsp[-4].join_attr));
        std:reverse((yyval.sql_node)->selection.joins.begin(), (yyval.sql_node)->selection.joins.end());
        delete (yyvsp[-4].join_attr);
      }
      
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].complex_expr_list) != nullptr) {
        (yyval.sql_node)->selection.group_by_fields.swap(*(yyvsp[-2].complex_expr_list));
        delete (yyvsp[-2].complex_expr_list);
      }
      
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.orders.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2496 "yacc_sql.cpp"
    break;

  case 74: /* from: %empty  */
#line 678 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 75: /* from: FROM ID alias_attr rel_list  */
#line 682 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list)->swap(*(yyvsp[0].relation_list));
        delete (yyvsp[0].relation_list);
      }
      (yyval.relation_list)->push_back((yyvsp[-2].string));
      if((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->push_back(std::string((yyvsp[-1].string)));
      } else (yyval.relation_list)->push_back(std::string(""));
      free((yyvsp[-2].string));
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 76: /* join_attr: %empty  */
#line 698 "yacc_sql.y"
    {
      (yyval.join_attr) = nullptr;
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 77: /* join_attr: INNER JOIN ID alias_attr rel_list on_attr join_attr  */
#line 702 "yacc_sql.y"
    {
      if((yyvsp[0].join_attr) != nullptr){
        (yyval.join_attr) = (yyvsp[0].join_attr);
      } else (yyval.join_attr) = new std::vector<std::unique_ptr<JoinSqlNode>>;
      std::unique_ptr<JoinSqlNode> tmp(new JoinSqlNode);
      if ((yyvsp[-2].relation_list) != nullptr) {
        tmp->join_list.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }
      tmp->join_list.push_back(std::string((yyvsp[-4].string)));
      if((yyvsp[-3].string) != nullptr) {
        tmp->join_list.push_back(std::string((yyvsp[-3].string)));
        free((yyvsp[-3].string));
      } else tmp->join_list.push_back(std::string(""));
      free((yyvsp[-4].string));

      if((yyvsp[-1].condition_list) != nullptr) {
        tmp->on_conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      (yyval.join_attr)->push_back(std::move(tmp));
    }
#line 2556 "yacc_sql.cpp"
    break;

  case 78: /* on_attr: %empty  */
#line 728 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2564 "yacc_sql.cpp"
    break;

  case 79: /* on_attr: ON condition_list  */
#line 732 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 80: /* group_by_stmt: %empty  */
#line 739 "yacc_sql.y"
    {
      (yyval.complex_expr_list) = nullptr;
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 81: /* group_by_stmt: GROUP_BY complex_expr complex_expr_list  */
#line 743 "yacc_sql.y"
    {
      if((yyvsp[0].complex_expr_list) != nullptr){
        (yyval.complex_expr_list) = (yyvsp[0].complex_expr_list);
      } else (yyval.complex_expr_list) = new std::vector<std::unique_ptr<ExprSqlNode>>;

      (yyval.complex_expr_list)->push_back(std::unique_ptr<ExprSqlNode>((yyvsp[-1].complex_expr)));
      std::reverse((yyval.complex_expr_list)->begin(), (yyval.complex_expr_list)->end());
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 82: /* having: %empty  */
#line 755 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 83: /* having: HAVING condition_list  */
#line 759 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2609 "yacc_sql.cpp"
    break;

  case 84: /* order_by_stmt: %empty  */
#line 766 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 85: /* order_by_stmt: ORDER_BY complex_expr order_type order_by_list  */
#line 770 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 86: /* order_type: %empty  */
#line 782 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 87: /* order_type: ASC  */
#line 786 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 88: /* order_type: DESC  */
#line 790 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 89: /* order_by_list: %empty  */
#line 797 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 90: /* order_by_list: COMMA complex_expr order_type order_by_list  */
#line 801 "yacc_sql.y"
    {
    if ((yyvsp[0].order_by_list) != nullptr) {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
    }
#line 2674 "yacc_sql.cpp"
    break;

  case 91: /* calc_stmt: CALC expression_list  */
#line 811 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 92: /* expression_list: expression  */
#line 821 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 93: /* expression_list: expression COMMA expression_list  */
#line 826 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '+' expression  */
#line 836 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '-' expression  */
#line 839 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression '*' expression  */
#line 842 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '/' expression  */
#line 845 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2739 "yacc_sql.cpp"
    break;

  case 98: /* expression: LBRACE expression RBRACE  */
#line 848 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2748 "yacc_sql.cpp"
    break;

  case 99: /* expression: '-' expression  */
#line 852 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 100: /* expression: value_in_expr  */
#line 855 "yacc_sql.y"
                    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 101: /* complex_expr: MAX_FUNC LBRACE complex_expr RBRACE  */
#line 864 "yacc_sql.y"
                                        {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MAX, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));     
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 102: /* complex_expr: MIN_FUNC LBRACE complex_expr RBRACE  */
#line 867 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MIN, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2782 "yacc_sql.cpp"
    break;

  case 103: /* complex_expr: COUNT_FUNC LBRACE complex_expr RBRACE  */
#line 870 "yacc_sql.y"
                                            {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_COUNT, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 104: /* complex_expr: AVG_FUNC LBRACE complex_expr RBRACE  */
#line 873 "yacc_sql.y"
                                         {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_AVG, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 105: /* complex_expr: SUM_FUNC LBRACE complex_expr RBRACE  */
#line 876 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_SUM, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 106: /* complex_expr: LENGTH_FUNC LBRACE complex_expr RBRACE  */
#line 880 "yacc_sql.y"
                                             {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_LENGTH, (yyvsp[-1].complex_expr), nullptr, token_name(sql_string, &(yyloc))); 
    }
#line 2814 "yacc_sql.cpp"
    break;

  case 107: /* complex_expr: ROUND_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 883 "yacc_sql.y"
                                                              {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_ROUND, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 108: /* complex_expr: DATE_FORMAT_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 886 "yacc_sql.y"
                                                                    {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_DATE_FORMAT, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 109: /* complex_expr: ID  */
#line 889 "yacc_sql.y"
         {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name = "";
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 110: /* complex_expr: ID DOT ID  */
#line 897 "yacc_sql.y"
                {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name  = (yyvsp[-2].string);
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2857 "yacc_sql.cpp"
    break;

  case 111: /* complex_expr: '*'  */
#line 906 "yacc_sql.y"
          {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      attr->need_extract = true;
      (yyval.complex_expr) = attr;
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 112: /* complex_expr: ID DOT '*'  */
#line 913 "yacc_sql.y"
                 {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      attr->attribute_name = "*";
      attr->need_extract = true;
      (yyval.complex_expr) = attr;
    }
#line 2882 "yacc_sql.cpp"
    break;

  case 113: /* complex_expr: complex_expr '+' complex_expr  */
#line 921 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::ADD, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2891 "yacc_sql.cpp"
    break;

  case 114: /* complex_expr: complex_expr '-' complex_expr  */
#line 925 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::SUB, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 115: /* complex_expr: complex_expr '*' complex_expr  */
#line 929 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::MUL, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2909 "yacc_sql.cpp"
    break;

  case 116: /* complex_expr: complex_expr '/' complex_expr  */
#line 933 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::DIV, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 117: /* complex_expr: LBRACE complex_expr RBRACE  */
#line 937 "yacc_sql.y"
                                 {
      (yyval.complex_expr) = (yyvsp[-1].complex_expr);
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = (yyvsp[-1].complex_expr)->need_extract;
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 118: /* complex_expr: '-' complex_expr  */
#line 942 "yacc_sql.y"
                                    {
      if((yyvsp[0].complex_expr)->get_type() == ExprSqlNode::Type::VALUE_EXPR){
        ValueSqlNode* tmp = (ValueSqlNode*)(yyvsp[0].complex_expr);
        tmp->val.make_negative();
        (yyval.complex_expr) = (ExprSqlNode*)tmp;
      }else (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::NEGATIVE, (yyvsp[0].complex_expr), nullptr, sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = (yyvsp[0].complex_expr)->need_extract;
    }
#line 2941 "yacc_sql.cpp"
    break;

  case 119: /* complex_expr: value_in_expr  */
#line 951 "yacc_sql.y"
    {
      (yyval.complex_expr) = new ValueSqlNode(*(yyvsp[0].value));
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = false;
      delete (yyvsp[0].value);
    }
#line 2952 "yacc_sql.cpp"
    break;

  case 120: /* possible_argument: %empty  */
#line 961 "yacc_sql.y"
    {
      (yyval.complex_expr) = nullptr;
    }
#line 2960 "yacc_sql.cpp"
    break;

  case 121: /* possible_argument: COMMA complex_expr  */
#line 965 "yacc_sql.y"
    {
      (yyval.complex_expr) = (yyvsp[0].complex_expr);
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 122: /* complex_expr_list: %empty  */
#line 971 "yacc_sql.y"
    {
      (yyval.complex_expr_list) = nullptr;
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 123: /* complex_expr_list: COMMA complex_expr alias_attr complex_expr_list  */
#line 974 "yacc_sql.y"
                                                      {
      if ((yyvsp[0].complex_expr_list) != nullptr) {
        (yyval.complex_expr_list) = (yyvsp[0].complex_expr_list);
      } else {
        (yyval.complex_expr_list) = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if((yyvsp[-1].string) != nullptr) {
        (yyvsp[-2].complex_expr)->set_name(std::string((yyvsp[-1].string)), true);
      }
      (yyval.complex_expr_list)->emplace_back(std::unique_ptr<ExprSqlNode>((yyvsp[-2].complex_expr)));
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 124: /* select_attr: complex_expr alias_attr complex_expr_list  */
#line 988 "yacc_sql.y"
                                              {
      if ((yyvsp[0].complex_expr_list) != nullptr) {
        (yyval.complex_expr_list) = (yyvsp[0].complex_expr_list);
      } else {
        (yyval.complex_expr_list) = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if((yyvsp[-1].string) != nullptr) {
        (yyvsp[-2].complex_expr)->set_name(std::string((yyvsp[-1].string)), true);
      }
        
      (yyval.complex_expr_list)->emplace_back(std::unique_ptr<ExprSqlNode>((yyvsp[-2].complex_expr)));
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 125: /* alias_attr: %empty  */
#line 1004 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 126: /* alias_attr: AS ID  */
#line 1007 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 127: /* alias_attr: ID  */
#line 1010 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 128: /* rel_list: %empty  */
#line 1017 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 129: /* rel_list: COMMA ID alias_attr rel_list  */
#line 1020 "yacc_sql.y"
                                   {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->push_back((yyvsp[-2].string));
      if((yyvsp[-1].string) != nullptr) {
        (yyval.relation_list)->push_back(std::string((yyvsp[-1].string)));
      } else (yyval.relation_list)->push_back(std::string(""));

      free((yyvsp[-2].string));
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1036 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition_list  */
#line 1039 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list); 
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 132: /* condition_list: %empty  */
#line 1045 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3083 "yacc_sql.cpp"
    break;

  case 133: /* condition_list: condition  */
#line 1048 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 134: /* condition_list: condition AND condition_list  */
#line 1052 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->set_conj(false);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3102 "yacc_sql.cpp"
    break;

  case 135: /* condition_list: condition OR condition_list  */
#line 1057 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->set_conj(true);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3112 "yacc_sql.cpp"
    break;

  case 136: /* condition: complex_expr comp_op complex_expr  */
#line 1065 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), (yyvsp[-1].comp));
    }
#line 3120 "yacc_sql.cpp"
    break;

  case 137: /* condition: complex_expr comp_op LBRACE select_stmt RBRACE  */
#line 1069 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-4].complex_expr), (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 138: /* condition: LBRACE select_stmt RBRACE comp_op complex_expr  */
#line 1073 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[0].complex_expr), (yyvsp[-3].sql_node), (yyvsp[-1].comp));
      (yyval.condition)->reverse_op();
    }
#line 3137 "yacc_sql.cpp"
    break;

  case 139: /* condition: complex_expr comp_op LBRACE value non_null_value_list RBRACE  */
#line 1078 "yacc_sql.y"
    {
      (yyvsp[-1].value_list)->emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      (yyval.condition) = new ConditionSqlNode((yyvsp[-5].complex_expr), (yyvsp[-1].value_list), (yyvsp[-4].comp));
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 140: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1084 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-5].sql_node), (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3155 "yacc_sql.cpp"
    break;

  case 141: /* condition: exist_op LBRACE select_stmt RBRACE  */
#line 1088 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((ExprSqlNode*)nullptr, (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3163 "yacc_sql.cpp"
    break;

  case 142: /* exist_op: EXIST_OP  */
#line 1094 "yacc_sql.y"
             { (yyval.comp) = EXIST;  }
#line 3169 "yacc_sql.cpp"
    break;

  case 143: /* exist_op: NOT EXIST_OP  */
#line 1095 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXIST;  }
#line 3175 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: EQ  */
#line 1099 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3181 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: LT  */
#line 1100 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3187 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: GT  */
#line 1101 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3193 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: LE  */
#line 1102 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3199 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: GE  */
#line 1103 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3205 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: NE  */
#line 1104 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3211 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: IS_OP  */
#line 1105 "yacc_sql.y"
            { (yyval.comp) = IS; }
#line 3217 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: IS_OP NOT  */
#line 1106 "yacc_sql.y"
                { (yyval.comp) = IS_NOT; }
#line 3223 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: LK  */
#line 1107 "yacc_sql.y"
         { (yyval.comp) = LIKE;  }
#line 3229 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: NOT LK  */
#line 1108 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;  }
#line 3235 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: IN_OP  */
#line 1109 "yacc_sql.y"
            { (yyval.comp) = IN; }
#line 3241 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: NOT IN_OP  */
#line 1110 "yacc_sql.y"
                { (yyval.comp) = NOT_IN; }
#line 3247 "yacc_sql.cpp"
    break;

  case 156: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1115 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3261 "yacc_sql.cpp"
    break;

  case 157: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1128 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3270 "yacc_sql.cpp"
    break;

  case 158: /* set_variable_stmt: SET ID EQ value set_variable_list  */
#line 1136 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3285 "yacc_sql.cpp"
    break;

  case 159: /* set_variable_stmt: SET ID EQ LBRACE select_stmt RBRACE set_variable_list  */
#line 1147 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-5].string)));
      (yyval.sql_node)->set_variable.value.push_back(Value());
      (yyval.sql_node)->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>((yyvsp[-2].sql_node)));
      free((yyvsp[-5].string));
    }
#line 3300 "yacc_sql.cpp"
    break;

  case 160: /* set_variable_list: %empty  */
#line 1161 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 3308 "yacc_sql.cpp"
    break;

  case 161: /* set_variable_list: COMMA ID EQ value set_variable_list  */
#line 1165 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3323 "yacc_sql.cpp"
    break;

  case 162: /* set_variable_list: COMMA ID EQ LBRACE select_stmt RBRACE set_variable_list  */
#line 1176 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-5].string)));
      (yyval.sql_node)->set_variable.value.push_back(Value());
      (yyval.sql_node)->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>((yyvsp[-2].sql_node)));
      free((yyvsp[-5].string));
    }
#line 3338 "yacc_sql.cpp"
    break;


#line 3342 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1191 "yacc_sql.y"

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
