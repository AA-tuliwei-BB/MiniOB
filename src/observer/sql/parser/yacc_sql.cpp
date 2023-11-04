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
  YYSYMBOL_ASC = 48,                       /* ASC  */
  YYSYMBOL_AS = 49,                        /* AS  */
  YYSYMBOL_AND = 50,                       /* AND  */
  YYSYMBOL_OR = 51,                        /* OR  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_SET = 53,                       /* SET  */
  YYSYMBOL_ON = 54,                        /* ON  */
  YYSYMBOL_LOAD = 55,                      /* LOAD  */
  YYSYMBOL_DATA = 56,                      /* DATA  */
  YYSYMBOL_INFILE = 57,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 58,                   /* EXPLAIN  */
  YYSYMBOL_LK = 59,                        /* LK  */
  YYSYMBOL_EQ = 60,                        /* EQ  */
  YYSYMBOL_LT = 61,                        /* LT  */
  YYSYMBOL_GT = 62,                        /* GT  */
  YYSYMBOL_LE = 63,                        /* LE  */
  YYSYMBOL_GE = 64,                        /* GE  */
  YYSYMBOL_NE = 65,                        /* NE  */
  YYSYMBOL_IS_OP = 66,                     /* IS_OP  */
  YYSYMBOL_IN_OP = 67,                     /* IN_OP  */
  YYSYMBOL_EXIST_OP = 68,                  /* EXIST_OP  */
  YYSYMBOL_NUMBER = 69,                    /* NUMBER  */
  YYSYMBOL_DATE = 70,                      /* DATE  */
  YYSYMBOL_FLOAT = 71,                     /* FLOAT  */
  YYSYMBOL_ID = 72,                        /* ID  */
  YYSYMBOL_SSS = 73,                       /* SSS  */
  YYSYMBOL_74_ = 74,                       /* '+'  */
  YYSYMBOL_75_ = 75,                       /* '-'  */
  YYSYMBOL_76_ = 76,                       /* '*'  */
  YYSYMBOL_77_ = 77,                       /* '/'  */
  YYSYMBOL_UMINUS = 78,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 79,                  /* $accept  */
  YYSYMBOL_commands = 80,                  /* commands  */
  YYSYMBOL_command_wrapper = 81,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 82,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 83,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 84,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 85,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 86,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 87,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 88,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 89,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 90,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 91,         /* create_index_stmt  */
  YYSYMBOL_id_list = 92,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 93,           /* drop_index_stmt  */
  YYSYMBOL_create_select_stmt = 94,        /* create_select_stmt  */
  YYSYMBOL_create_table_stmt = 95,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 96,             /* attr_def_list  */
  YYSYMBOL_attr_def = 97,                  /* attr_def  */
  YYSYMBOL_null_def = 98,                  /* null_def  */
  YYSYMBOL_number = 99,                    /* number  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_insert_stmt = 101,              /* insert_stmt  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_non_null_value_list = 103,      /* non_null_value_list  */
  YYSYMBOL_value = 104,                    /* value  */
  YYSYMBOL_value_in_expr = 105,            /* value_in_expr  */
  YYSYMBOL_delete_stmt = 106,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 107,              /* update_stmt  */
  YYSYMBOL_select_stmt = 108,              /* select_stmt  */
  YYSYMBOL_from = 109,                     /* from  */
  YYSYMBOL_join_attr = 110,                /* join_attr  */
  YYSYMBOL_on_attr = 111,                  /* on_attr  */
  YYSYMBOL_order_by_stmt = 112,            /* order_by_stmt  */
  YYSYMBOL_order_type = 113,               /* order_type  */
  YYSYMBOL_order_by_list = 114,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 115,                /* calc_stmt  */
  YYSYMBOL_expression_list = 116,          /* expression_list  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_complex_expr = 118,             /* complex_expr  */
  YYSYMBOL_possible_argument = 119,        /* possible_argument  */
  YYSYMBOL_complex_expr_list = 120,        /* complex_expr_list  */
  YYSYMBOL_select_attr = 121,              /* select_attr  */
  YYSYMBOL_alias_attr = 122,               /* alias_attr  */
  YYSYMBOL_rel_list = 123,                 /* rel_list  */
  YYSYMBOL_where = 124,                    /* where  */
  YYSYMBOL_condition_list = 125,           /* condition_list  */
  YYSYMBOL_condition = 126,                /* condition  */
  YYSYMBOL_exist_op = 127,                 /* exist_op  */
  YYSYMBOL_comp_op = 128,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 129,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 130,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 131,        /* set_variable_stmt  */
  YYSYMBOL_set_variable_list = 132,        /* set_variable_list  */
  YYSYMBOL_opt_semicolon = 133             /* opt_semicolon  */
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
#define YYLAST   463

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  158
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
       2,     2,    76,    74,     2,    75,     2,    77,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    78
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   228,   228,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   260,   266,   271,   277,   283,   289,
     295,   302,   308,   316,   332,   352,   355,   366,   377,   386,
     406,   425,   428,   441,   450,   462,   465,   469,   474,   477,
     478,   479,   480,   481,   484,   500,   503,   515,   526,   530,
     534,   538,   543,   547,   554,   558,   562,   567,   571,   577,
     589,   604,   638,   641,   658,   661,   688,   691,   698,   701,
     714,   717,   721,   729,   732,   742,   752,   757,   768,   771,
     774,   777,   780,   784,   787,   796,   799,   802,   805,   808,
     812,   815,   818,   821,   829,   838,   845,   853,   857,   861,
     865,   869,   874,   882,   893,   896,   903,   906,   919,   933,
     936,   939,   946,   949,   965,   968,   974,   977,   981,   986,
     993,   997,  1001,  1006,  1012,  1016,  1023,  1024,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1043,  1056,  1064,  1075,  1090,  1093,  1104,  1117,  1118
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
  "JOIN", "FROM", "WHERE", "ORDER_BY", "ASC", "AS", "AND", "OR", "NOT",
  "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "LK", "EQ", "LT", "GT",
  "LE", "GE", "NE", "IS_OP", "IN_OP", "EXIST_OP", "NUMBER", "DATE",
  "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt", "id_list",
  "drop_index_stmt", "create_select_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "null_def", "number", "type", "insert_stmt",
  "value_list", "non_null_value_list", "value", "value_in_expr",
  "delete_stmt", "update_stmt", "select_stmt", "from", "join_attr",
  "on_attr", "order_by_stmt", "order_type", "order_by_list", "calc_stmt",
  "expression_list", "expression", "complex_expr", "possible_argument",
  "complex_expr_list", "select_attr", "alias_attr", "rel_list", "where",
  "condition_list", "condition", "exist_op", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "set_variable_list",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-265)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-64)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     369,   136,     9,   -21,   227,   -52,    15,  -265,   -17,   -10,
       1,  -265,  -265,  -265,  -265,  -265,    18,     6,   369,    68,
      74,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,    48,   114,    69,    75,    76,   -21,  -265,  -265,
    -265,  -265,  -265,   -21,  -265,  -265,    61,   137,   138,   140,
     149,   150,   151,   152,   177,   227,   100,   227,  -265,  -265,
     264,   106,  -265,  -265,    90,   132,   153,   148,   163,  -265,
    -265,  -265,  -265,    20,   135,   155,  -265,   175,   -19,  -265,
     -21,   -21,   -21,   -21,   -21,   227,   227,   227,   227,   227,
     227,   227,   227,    10,   -55,  -265,   158,  -265,   227,   227,
     227,   227,   203,   161,   189,   204,   201,   201,   341,   197,
     193,   253,   224,   208,   209,  -265,  -265,    -2,    -2,  -265,
    -265,    34,    95,   125,   147,   160,   192,   200,   200,  -265,
    -265,  -265,  -265,    42,    42,  -265,  -265,   227,  -265,    11,
     239,   201,   258,   113,  -265,  -265,   253,  -265,  -265,  -265,
    -265,  -265,   216,   259,   248,    -3,   262,  -265,   214,   266,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,   227,   268,   274,
     264,   284,   271,   297,   -28,   142,   263,  -265,   379,  -265,
      82,   319,   320,  -265,   286,  -265,   340,  -265,  -265,  -265,
    -265,  -265,   -14,   193,   332,   334,   289,    26,  -265,  -265,
     203,   298,  -265,    11,   227,  -265,   343,   345,  -265,   -40,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,   323,  -265,   245,
     113,   113,   253,   259,   316,   305,   326,  -265,   360,  -265,
     262,   352,   330,   375,  -265,    11,   284,     5,   -28,   377,
     290,  -265,  -265,  -265,   179,    26,  -265,  -265,   378,  -265,
     359,  -265,  -265,   382,  -265,  -265,   253,   375,   346,   386,
     284,   361,  -265,  -265,   389,   343,  -265,   293,   391,   392,
     393,   395,   397,   311,   398,   406,  -265,   253,   259,   -24,
    -265,   408,   375,  -265,  -265,   113,   189,   227,  -265,  -265,
     142,    26,   409,   -28,   420,  -265,   421,  -265,  -265,  -265,
    -265,  -265,  -265,     5,   422,   343,  -265,   259,   389,  -265,
    -265,  -265,  -265
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     157,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     9,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    68,    64,
      67,    65,    66,     0,    94,    85,    86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   105,   113,
     119,    72,    32,    31,     0,     0,     0,     0,     0,   151,
       1,   158,     2,     0,     0,     0,    30,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,     0,   121,     0,     0,
       0,     0,   116,     0,    74,     0,   124,   124,     0,     0,
       0,     0,     0,     0,     0,    92,    87,    88,    89,    90,
      91,     0,     0,     0,     0,     0,     0,   114,   114,   111,
     104,   106,   120,   107,   108,   109,   110,     0,   118,   119,
       0,   124,     0,   126,    69,    70,     0,    63,    58,    62,
      60,    61,     0,   154,     0,     0,    41,    38,     0,     0,
      37,    95,    96,    97,    98,    99,   100,     0,     0,     0,
     119,   122,     0,    78,     0,     0,     0,   136,     0,   125,
     127,     0,     0,    59,     0,   152,     0,    49,    50,    51,
      52,    53,    45,     0,     0,     0,     0,   115,   101,   102,
     116,     0,    73,   119,     0,    71,    55,     0,   137,     0,
     146,   138,   139,   140,   141,   142,   143,   144,   148,     0,
     126,   126,     0,   154,     0,     0,     0,    47,     0,    44,
      41,    40,     0,    35,   117,   119,   122,    80,     0,     0,
       0,   147,   149,   145,     0,   130,   128,   129,     0,   153,
       0,   150,    48,     0,    46,    42,     0,    35,     0,     0,
     122,    76,    82,    81,    83,    55,    54,     0,    68,    64,
      67,    65,    66,     0,     0,     0,   135,     0,   154,    45,
      39,     0,    35,    33,   123,   126,    74,     0,    79,    56,
       0,   132,    64,     0,     0,   131,     0,   155,    43,    34,
      36,    77,    75,    80,     0,    55,   133,   154,    83,   134,
      57,   156,    84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -265,  -265,   388,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -253,  -265,  -265,  -265,   196,   247,   162,
    -265,  -265,  -265,  -264,  -265,  -182,    23,  -265,  -265,  -120,
    -265,   156,  -265,  -265,   144,   141,  -265,   368,   241,    -4,
     322,   251,  -265,  -146,  -206,  -107,  -224,  -265,  -265,   212,
    -265,  -265,   387,  -229,  -265
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   269,    31,    32,    33,   204,   166,   239,
     263,   202,    34,   249,   304,   163,    69,    35,    36,    37,
     114,   151,   296,   215,   274,   298,    38,    55,    56,   103,
     178,   148,    71,   112,   212,   154,   189,   190,   191,   229,
      39,    40,    41,   195,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   167,   216,   181,   259,    47,   256,   257,   125,   157,
     155,   299,   236,   237,   291,    45,    48,   140,    46,   251,
      72,   141,    73,   237,    74,   272,    54,   252,   238,   197,
     198,   199,   200,   201,   210,    75,   192,   139,   238,   310,
     271,   158,   159,   160,   183,   161,   120,   162,    49,    50,
      51,   320,    52,   273,    53,    91,    92,    93,    94,   307,
     106,   171,    78,   105,   294,   217,   275,   246,    80,   121,
      54,   311,   284,    76,    93,    94,    54,    81,   288,   108,
     109,   110,   111,   107,   108,   109,   110,   111,   321,    90,
      77,   131,   132,   133,   134,   135,   136,   137,   138,   270,
     108,   109,   110,   111,   143,   144,   145,   146,   108,   109,
     110,   111,   258,    54,    54,    54,    54,    54,   110,   111,
      83,   315,   172,    84,    57,    58,    59,    60,    61,    62,
      63,    64,   230,   231,   285,    91,    92,    93,    94,   185,
     104,    85,    42,   180,    43,    44,   290,    86,    87,   188,
      48,   113,   173,    57,    58,    59,    60,    61,    62,    63,
      64,     4,   115,    95,    96,   186,    97,   306,    65,   108,
     109,   110,   111,   207,   174,    98,    99,   100,   101,    48,
     314,   187,    49,    50,    51,    66,    52,   175,    67,    68,
      57,    58,    59,    60,    61,    62,    63,    64,     4,   108,
     109,   110,   111,   102,   116,    65,    16,   122,   118,   123,
     247,    49,    50,    51,    66,    52,   278,    67,    68,   176,
     119,   108,   109,   110,   111,   255,   188,   188,   177,   124,
     142,   147,   150,   149,   108,   109,   110,   111,    57,    58,
      59,    60,    61,    62,    63,    64,   152,   153,   279,   280,
     281,    66,   282,    65,   283,    68,    57,    58,    59,    60,
      61,    62,    63,    64,    48,   165,   108,   109,   110,   111,
     164,   254,     4,   301,   108,   109,   110,   111,   168,   105,
     169,   170,    48,   182,   184,   193,   205,   194,    88,   196,
     203,   188,   206,   313,    89,   208,    49,    50,    51,    66,
      52,   209,    67,    68,    57,    58,    59,    60,    61,    62,
      63,    64,   211,   106,    49,    50,    51,    66,    52,   300,
      67,    68,    57,    58,    59,    60,    61,    62,    63,    64,
      48,   218,   127,   128,   129,   130,   107,    65,   108,   109,
     110,   111,   219,   213,   214,   232,   235,   233,    48,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   234,   241,
     242,   243,    49,    50,    51,    66,    52,   156,    67,    68,
     245,   248,   250,     1,     2,   253,   260,   261,   157,     3,
     302,    50,    51,    66,    52,   287,    67,    68,     4,     5,
       6,     7,     8,     9,    10,   262,   157,   264,    11,    12,
      13,   266,   267,   268,   276,   286,    79,    14,    15,   289,
     158,   159,   160,   293,   161,   295,   162,   297,   292,   -63,
     -58,   -62,    16,   -60,    17,   -61,   303,    18,   158,   159,
     160,   219,   161,   305,   162,   309,   265,   -59,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   316,   317,   319,
     240,   308,   312,   108,   109,   110,   111,   318,   126,   322,
     179,   244,   277,   117
};

static const yytype_int16 yycheck[] =
{
       4,   121,   184,   149,   233,    26,   230,   231,    27,    37,
     117,   275,    26,    37,   267,     6,    37,    72,     9,    59,
      72,    76,     7,    37,    41,    20,     3,    67,    52,    32,
      33,    34,    35,    36,   180,    45,   156,    27,    52,   292,
     246,    69,    70,    71,   151,    73,    26,    75,    69,    70,
      71,   315,    73,    48,    75,    74,    75,    76,    77,   288,
      49,    27,    56,    67,   270,   185,   248,   213,     0,    49,
      47,   295,   254,    72,    76,    77,    53,     3,   260,    74,
      75,    76,    77,    72,    74,    75,    76,    77,   317,    28,
      72,    95,    96,    97,    98,    99,   100,   101,   102,   245,
      74,    75,    76,    77,   108,   109,   110,   111,    74,    75,
      76,    77,   232,    90,    91,    92,    93,    94,    76,    77,
      72,   303,    27,     9,    11,    12,    13,    14,    15,    16,
      17,    18,    50,    51,   254,    74,    75,    76,    77,    26,
      40,    72,     6,   147,     8,     9,   266,    72,    72,   153,
      37,    45,    27,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    72,    26,    26,    52,    26,   287,    26,    74,
      75,    76,    77,   177,    27,    26,    26,    26,    26,    37,
     300,    68,    69,    70,    71,    72,    73,    27,    75,    76,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    74,
      75,    76,    77,    26,    72,    26,    53,    72,    60,    54,
     214,    69,    70,    71,    72,    73,    37,    75,    76,    27,
      57,    74,    75,    76,    77,   229,   230,   231,    28,    54,
      72,    28,    43,    72,    74,    75,    76,    77,    11,    12,
      13,    14,    15,    16,    17,    18,    42,    46,    69,    70,
      71,    72,    73,    26,    75,    76,    11,    12,    13,    14,
      15,    16,    17,    18,    37,    72,    74,    75,    76,    77,
      73,    26,    19,   277,    74,    75,    76,    77,    54,   283,
      72,    72,    37,    44,    26,    69,    72,    28,    47,    41,
      28,   295,    26,   297,    53,    27,    69,    70,    71,    72,
      73,    27,    75,    76,    11,    12,    13,    14,    15,    16,
      17,    18,    28,    49,    69,    70,    71,    72,    73,    26,
      75,    76,    11,    12,    13,    14,    15,    16,    17,    18,
      37,    68,    91,    92,    93,    94,    72,    26,    74,    75,
      76,    77,    52,    72,    47,    26,     6,    27,    37,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    72,    27,
      26,    72,    69,    70,    71,    72,    73,    26,    75,    76,
      72,    28,    27,     4,     5,    52,    60,    72,    37,    10,
      69,    70,    71,    72,    73,    26,    75,    76,    19,    20,
      21,    22,    23,    24,    25,    69,    37,    37,    29,    30,
      31,    49,    72,    28,    27,    27,    18,    38,    39,    27,
      69,    70,    71,    27,    73,    54,    75,    28,    72,    28,
      28,    28,    53,    28,    55,    28,    28,    58,    69,    70,
      71,    52,    73,    27,    75,    27,   240,    28,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    27,    27,    27,
     203,   289,   296,    74,    75,    76,    77,   313,    90,   318,
     138,   210,   250,    76
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    19,    20,    21,    22,    23,    24,
      25,    29,    30,    31,    38,    39,    53,    55,    58,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    93,    94,    95,   101,   106,   107,   108,   115,   129,
     130,   131,     6,     8,     9,     6,     9,    26,    37,    69,
      70,    71,    73,    75,   105,   116,   117,    11,    12,    13,
      14,    15,    16,    17,    18,    26,    72,    75,    76,   105,
     118,   121,    72,     7,    41,    45,    72,    72,    56,    81,
       0,     3,   133,    72,     9,    72,    72,    72,   117,   117,
      28,    74,    75,    76,    77,    26,    26,    26,    26,    26,
      26,    26,    26,   118,    40,   118,    49,    72,    74,    75,
      76,    77,   122,    45,   109,    72,    72,   131,    60,    57,
      26,    49,    72,    54,    54,    27,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,    27,
      72,    76,    72,   118,   118,   118,   118,    28,   120,    72,
      43,   110,    42,    46,   124,   124,    26,    37,    69,    70,
      71,    73,    75,   104,    73,    72,    97,   108,    54,    72,
      72,    27,    27,    27,    27,    27,    27,    28,   119,   119,
     118,   122,    44,   124,    26,    26,    52,    68,   118,   125,
     126,   127,   108,    69,    28,   132,    41,    32,    33,    34,
      35,    36,   100,    28,    96,    72,    26,   118,    27,    27,
     122,    28,   123,    72,    47,   112,   104,   108,    68,    52,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   128,
      50,    51,    26,    27,    72,     6,    26,    37,    52,    98,
      97,    27,    26,    72,   120,    72,   122,   118,    28,   102,
      27,    59,    67,    52,    26,   118,   125,   125,   108,   132,
      60,    72,    69,    99,    37,    96,    49,    72,    28,    92,
     122,   123,    20,    48,   113,   104,    27,   128,    37,    69,
      70,    71,    73,    75,   104,   108,    27,    26,   104,    27,
     108,    92,    72,    27,   123,    54,   111,    28,   114,   102,
      26,   118,    69,    28,   103,    27,   108,   132,    98,    27,
      92,   125,   110,   118,   108,   104,    27,    27,   113,    27,
     102,   132,   114
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    91,    92,    92,    93,    94,    94,
      95,    96,    96,    97,    97,    98,    98,    98,    99,   100,
     100,   100,   100,   100,   101,   102,   102,   103,   104,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   105,   106,
     107,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   113,   114,   114,   115,   116,   116,   117,   117,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   120,   120,   121,   122,
     122,   122,   123,   123,   124,   124,   125,   125,   125,   125,
     126,   126,   126,   126,   126,   126,   127,   127,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     129,   130,   131,   131,   132,   132,   132,   133,   133
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     5,     9,
       7,     0,     3,     6,     3,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     8,     0,     3,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     6,     0,     4,     0,     7,     0,     2,     0,     4,
       0,     1,     1,     0,     4,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     4,     4,     4,     4,     4,
       4,     5,     5,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     0,     2,     0,     4,     3,     0,
       2,     1,     0,     4,     0,     2,     0,     1,     3,     3,
       3,     5,     5,     6,     7,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
       7,     2,     5,     7,     0,     5,     7,     0,     1
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
#line 229 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1908 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 260 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 266 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 271 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 277 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 283 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1949 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 289 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 295 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 302 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 308 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1985 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 317 "yacc_sql.y"
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
#line 2005 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 333 "yacc_sql.y"
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
#line 2025 "yacc_sql.cpp"
    break;

  case 35: /* id_list: %empty  */
#line 352 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr; 
    }
#line 2033 "yacc_sql.cpp"
    break;

  case 36: /* id_list: COMMA ID id_list  */
#line 356 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else (yyval.relation_list) = new std::vector<std::string>;
      (yyval.relation_list)->emplace_back(std::string((yyvsp[-1].string)));
      free((yyvsp[-1].string));
    }
#line 2045 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 367 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2057 "yacc_sql.cpp"
    break;

  case 38: /* create_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 378 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
      CreateSelectSqlNode &create_select = (yyval.sql_node)->create_select;
      create_select.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_select.select_node = std::move(std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node)));
      
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 39: /* create_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 387 "yacc_sql.y"
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
#line 2091 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 407 "yacc_sql.y"
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
#line 2111 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 425 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2119 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 429 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 442 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type null_def  */
#line 451 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = (yyval.attr_info)->type == AttrType::TEXTS ? 0 : 4;
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2159 "yacc_sql.cpp"
    break;

  case 45: /* null_def: %empty  */
#line 462 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2167 "yacc_sql.cpp"
    break;

  case 46: /* null_def: NOT NULL_VAL  */
#line 466 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2175 "yacc_sql.cpp"
    break;

  case 47: /* null_def: NULL_VAL  */
#line 470 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2183 "yacc_sql.cpp"
    break;

  case 48: /* number: NUMBER  */
#line 474 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2189 "yacc_sql.cpp"
    break;

  case 49: /* type: INT_T  */
#line 477 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2195 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 478 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2201 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 479 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2207 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 480 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2213 "yacc_sql.cpp"
    break;

  case 53: /* type: TEXT_T  */
#line 481 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2219 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 485 "yacc_sql.y"
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
#line 2235 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 500 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 503 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 57: /* non_null_value_list: COMMA value value_list  */
#line 515 "yacc_sql.y"
                            { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2271 "yacc_sql.cpp"
    break;

  case 58: /* value: NUMBER  */
#line 526 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2280 "yacc_sql.cpp"
    break;

  case 59: /* value: '-' NUMBER  */
#line 530 "yacc_sql.y"
               {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2289 "yacc_sql.cpp"
    break;

  case 60: /* value: FLOAT  */
#line 534 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 538 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2308 "yacc_sql.cpp"
    break;

  case 62: /* value: DATE  */
#line 543 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 63: /* value: NULL_VAL  */
#line 547 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 64: /* value_in_expr: NUMBER  */
#line 554 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 65: /* value_in_expr: FLOAT  */
#line 558 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 66: /* value_in_expr: SSS  */
#line 562 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 67: /* value_in_expr: DATE  */
#line 567 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 68: /* value_in_expr: NULL_VAL  */
#line 571 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2372 "yacc_sql.cpp"
    break;

  case 69: /* delete_stmt: DELETE FROM ID where  */
#line 578 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 70: /* update_stmt: UPDATE ID set_variable_stmt where  */
#line 590 "yacc_sql.y"
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
#line 2403 "yacc_sql.cpp"
    break;

  case 71: /* select_stmt: SELECT select_attr from join_attr where order_by_stmt  */
#line 605 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].complex_expr_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-4].complex_expr_list));
        delete (yyvsp[-4].complex_expr_list);
      }
      
      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
        delete (yyvsp[-3].relation_list);
      }
      
      if ((yyvsp[-2].join_attr) != nullptr) {
        (yyval.sql_node)->selection.joins.swap(*(yyvsp[-2].join_attr));
        std:reverse((yyval.sql_node)->selection.joins.begin(), (yyval.sql_node)->selection.joins.end());
        delete (yyvsp[-2].join_attr);
      }
      
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.orders.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2437 "yacc_sql.cpp"
    break;

  case 72: /* from: %empty  */
#line 638 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2445 "yacc_sql.cpp"
    break;

  case 73: /* from: FROM ID alias_attr rel_list  */
#line 642 "yacc_sql.y"
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
#line 2462 "yacc_sql.cpp"
    break;

  case 74: /* join_attr: %empty  */
#line 658 "yacc_sql.y"
    {
      (yyval.join_attr) = nullptr;
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 75: /* join_attr: INNER JOIN ID alias_attr rel_list on_attr join_attr  */
#line 662 "yacc_sql.y"
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
#line 2497 "yacc_sql.cpp"
    break;

  case 76: /* on_attr: %empty  */
#line 688 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 77: /* on_attr: ON condition_list  */
#line 692 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 78: /* order_by_stmt: %empty  */
#line 698 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 79: /* order_by_stmt: ORDER_BY complex_expr order_type order_by_list  */
#line 702 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 80: /* order_type: %empty  */
#line 714 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2542 "yacc_sql.cpp"
    break;

  case 81: /* order_type: ASC  */
#line 718 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2550 "yacc_sql.cpp"
    break;

  case 82: /* order_type: DESC  */
#line 722 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2558 "yacc_sql.cpp"
    break;

  case 83: /* order_by_list: %empty  */
#line 729 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2566 "yacc_sql.cpp"
    break;

  case 84: /* order_by_list: COMMA complex_expr order_type order_by_list  */
#line 733 "yacc_sql.y"
    {
    if ((yyvsp[0].order_by_list) != nullptr) {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
    }
#line 2578 "yacc_sql.cpp"
    break;

  case 85: /* calc_stmt: CALC expression_list  */
#line 743 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression  */
#line 753 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression COMMA expression_list  */
#line 758 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '+' expression  */
#line 768 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2619 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '-' expression  */
#line 771 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2627 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '*' expression  */
#line 774 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2635 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '/' expression  */
#line 777 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 92: /* expression: LBRACE expression RBRACE  */
#line 780 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 93: /* expression: '-' expression  */
#line 784 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 94: /* expression: value_in_expr  */
#line 787 "yacc_sql.y"
                    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 95: /* complex_expr: MAX_FUNC LBRACE complex_expr RBRACE  */
#line 796 "yacc_sql.y"
                                        {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MAX, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));     
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 96: /* complex_expr: MIN_FUNC LBRACE complex_expr RBRACE  */
#line 799 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MIN, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 97: /* complex_expr: COUNT_FUNC LBRACE complex_expr RBRACE  */
#line 802 "yacc_sql.y"
                                            {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_COUNT, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 98: /* complex_expr: AVG_FUNC LBRACE complex_expr RBRACE  */
#line 805 "yacc_sql.y"
                                         {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_AVG, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 99: /* complex_expr: SUM_FUNC LBRACE complex_expr RBRACE  */
#line 808 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_SUM, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2710 "yacc_sql.cpp"
    break;

  case 100: /* complex_expr: LENGTH_FUNC LBRACE complex_expr RBRACE  */
#line 812 "yacc_sql.y"
                                             {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_LENGTH, (yyvsp[-1].complex_expr), nullptr, token_name(sql_string, &(yyloc))); 
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 101: /* complex_expr: ROUND_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 815 "yacc_sql.y"
                                                              {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_ROUND, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 102: /* complex_expr: DATE_FORMAT_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 818 "yacc_sql.y"
                                                                    {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_DATE_FORMAT, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 103: /* complex_expr: ID  */
#line 821 "yacc_sql.y"
         {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name = "";
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 104: /* complex_expr: ID DOT ID  */
#line 829 "yacc_sql.y"
                {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name  = (yyvsp[-2].string);
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 105: /* complex_expr: '*'  */
#line 838 "yacc_sql.y"
          {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      attr->need_extract = true;
      (yyval.complex_expr) = attr;
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 106: /* complex_expr: ID DOT '*'  */
#line 845 "yacc_sql.y"
                 {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      attr->attribute_name = "*";
      attr->need_extract = true;
      (yyval.complex_expr) = attr;
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 107: /* complex_expr: complex_expr '+' complex_expr  */
#line 853 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::ADD, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 108: /* complex_expr: complex_expr '-' complex_expr  */
#line 857 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::SUB, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 109: /* complex_expr: complex_expr '*' complex_expr  */
#line 861 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::MUL, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 110: /* complex_expr: complex_expr '/' complex_expr  */
#line 865 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::DIV, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 111: /* complex_expr: LBRACE complex_expr RBRACE  */
#line 869 "yacc_sql.y"
                                 {
      (yyval.complex_expr) = (yyvsp[-1].complex_expr);
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = (yyvsp[-1].complex_expr)->need_extract;
    }
#line 2832 "yacc_sql.cpp"
    break;

  case 112: /* complex_expr: '-' complex_expr  */
#line 874 "yacc_sql.y"
                                    {
      if((yyvsp[0].complex_expr)->get_type() == ExprSqlNode::Type::VALUE_EXPR){
        ValueSqlNode* tmp = (ValueSqlNode*)(yyvsp[0].complex_expr);
        tmp->val.make_negative();
        (yyval.complex_expr) = (ExprSqlNode*)tmp;
      }else (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::NEGATIVE, (yyvsp[0].complex_expr), nullptr, sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = (yyvsp[0].complex_expr)->need_extract;
    }
#line 2845 "yacc_sql.cpp"
    break;

  case 113: /* complex_expr: value_in_expr  */
#line 883 "yacc_sql.y"
    {
      (yyval.complex_expr) = new ValueSqlNode(*(yyvsp[0].value));
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = false;
      delete (yyvsp[0].value);
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 114: /* possible_argument: %empty  */
#line 893 "yacc_sql.y"
    {
      (yyval.complex_expr) = nullptr;
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 115: /* possible_argument: COMMA complex_expr  */
#line 897 "yacc_sql.y"
    {
      (yyval.complex_expr) = (yyvsp[0].complex_expr);
    }
#line 2872 "yacc_sql.cpp"
    break;

  case 116: /* complex_expr_list: %empty  */
#line 903 "yacc_sql.y"
    {
      (yyval.complex_expr_list) = nullptr;
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 117: /* complex_expr_list: COMMA complex_expr alias_attr complex_expr_list  */
#line 906 "yacc_sql.y"
                                                      {
      if ((yyvsp[0].complex_expr_list) != nullptr) {
        (yyval.complex_expr_list) = (yyvsp[0].complex_expr_list);
      } else {
        (yyval.complex_expr_list) = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if((yyvsp[-1].string) != nullptr)
        (yyvsp[-2].complex_expr)->set_name(std::string((yyvsp[-1].string)));
      (yyval.complex_expr_list)->emplace_back(std::unique_ptr<ExprSqlNode>((yyvsp[-2].complex_expr)));
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 118: /* select_attr: complex_expr alias_attr complex_expr_list  */
#line 919 "yacc_sql.y"
                                              {
      if ((yyvsp[0].complex_expr_list) != nullptr) {
        (yyval.complex_expr_list) = (yyvsp[0].complex_expr_list);
      } else {
        (yyval.complex_expr_list) = new std::vector<std::unique_ptr<ExprSqlNode>>;
      }
      if((yyvsp[-1].string) != nullptr)
        (yyvsp[-2].complex_expr)->set_name(std::string((yyvsp[-1].string)));
      (yyval.complex_expr_list)->emplace_back(std::unique_ptr<ExprSqlNode>((yyvsp[-2].complex_expr)));
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 119: /* alias_attr: %empty  */
#line 933 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 120: /* alias_attr: AS ID  */
#line 936 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 121: /* alias_attr: ID  */
#line 939 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2934 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: %empty  */
#line 946 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 123: /* rel_list: COMMA ID alias_attr rel_list  */
#line 949 "yacc_sql.y"
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
#line 2960 "yacc_sql.cpp"
    break;

  case 124: /* where: %empty  */
#line 965 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 125: /* where: WHERE condition_list  */
#line 968 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list); 
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 126: /* condition_list: %empty  */
#line 974 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 127: /* condition_list: condition  */
#line 977 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: condition AND condition_list  */
#line 981 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->set_conj(false);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3003 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: condition OR condition_list  */
#line 986 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->set_conj(true);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3013 "yacc_sql.cpp"
    break;

  case 130: /* condition: complex_expr comp_op complex_expr  */
#line 994 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), (yyvsp[-1].comp));
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 131: /* condition: complex_expr comp_op LBRACE select_stmt RBRACE  */
#line 998 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-4].complex_expr), (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 132: /* condition: LBRACE select_stmt RBRACE comp_op complex_expr  */
#line 1002 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[0].complex_expr), (yyvsp[-3].sql_node), (yyvsp[-1].comp));
      (yyval.condition)->reverse_op();
    }
#line 3038 "yacc_sql.cpp"
    break;

  case 133: /* condition: complex_expr comp_op LBRACE value non_null_value_list RBRACE  */
#line 1007 "yacc_sql.y"
    {
      (yyvsp[-1].value_list)->emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      (yyval.condition) = new ConditionSqlNode((yyvsp[-5].complex_expr), (yyvsp[-1].value_list), (yyvsp[-4].comp));
    }
#line 3048 "yacc_sql.cpp"
    break;

  case 134: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1013 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-5].sql_node), (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3056 "yacc_sql.cpp"
    break;

  case 135: /* condition: exist_op LBRACE select_stmt RBRACE  */
#line 1017 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((ExprSqlNode*)nullptr, (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 3064 "yacc_sql.cpp"
    break;

  case 136: /* exist_op: EXIST_OP  */
#line 1023 "yacc_sql.y"
             { (yyval.comp) = EXIST;  }
#line 3070 "yacc_sql.cpp"
    break;

  case 137: /* exist_op: NOT EXIST_OP  */
#line 1024 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXIST;  }
#line 3076 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: EQ  */
#line 1028 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3082 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: LT  */
#line 1029 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3088 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: GT  */
#line 1030 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3094 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: LE  */
#line 1031 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3100 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: GE  */
#line 1032 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3106 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NE  */
#line 1033 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3112 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: IS_OP  */
#line 1034 "yacc_sql.y"
            { (yyval.comp) = IS; }
#line 3118 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: IS_OP NOT  */
#line 1035 "yacc_sql.y"
                { (yyval.comp) = IS_NOT; }
#line 3124 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: LK  */
#line 1036 "yacc_sql.y"
         { (yyval.comp) = LIKE;  }
#line 3130 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT LK  */
#line 1037 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;  }
#line 3136 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: IN_OP  */
#line 1038 "yacc_sql.y"
            { (yyval.comp) = IN; }
#line 3142 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: NOT IN_OP  */
#line 1039 "yacc_sql.y"
                { (yyval.comp) = NOT_IN; }
#line 3148 "yacc_sql.cpp"
    break;

  case 150: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1044 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 151: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1057 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3171 "yacc_sql.cpp"
    break;

  case 152: /* set_variable_stmt: SET ID EQ value set_variable_list  */
#line 1065 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3186 "yacc_sql.cpp"
    break;

  case 153: /* set_variable_stmt: SET ID EQ LBRACE select_stmt RBRACE set_variable_list  */
#line 1076 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-5].string)));
      (yyval.sql_node)->set_variable.value.push_back(Value());
      (yyval.sql_node)->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>((yyvsp[-2].sql_node)));
      free((yyvsp[-5].string));
    }
#line 3201 "yacc_sql.cpp"
    break;

  case 154: /* set_variable_list: %empty  */
#line 1090 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 3209 "yacc_sql.cpp"
    break;

  case 155: /* set_variable_list: COMMA ID EQ value set_variable_list  */
#line 1094 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3224 "yacc_sql.cpp"
    break;

  case 156: /* set_variable_list: COMMA ID EQ LBRACE select_stmt RBRACE set_variable_list  */
#line 1105 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-5].string)));
      (yyval.sql_node)->set_variable.value.push_back(Value());
      (yyval.sql_node)->set_variable.sub_select.push_back(std::unique_ptr<ParsedSqlNode>((yyvsp[-2].sql_node)));
      free((yyvsp[-5].string));
    }
#line 3239 "yacc_sql.cpp"
    break;


#line 3243 "yacc_sql.cpp"

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

#line 1120 "yacc_sql.y"

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
