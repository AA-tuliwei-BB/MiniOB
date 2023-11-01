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
  YYSYMBOL_NOT = 51,                       /* NOT  */
  YYSYMBOL_SET = 52,                       /* SET  */
  YYSYMBOL_ON = 53,                        /* ON  */
  YYSYMBOL_LOAD = 54,                      /* LOAD  */
  YYSYMBOL_DATA = 55,                      /* DATA  */
  YYSYMBOL_INFILE = 56,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 57,                   /* EXPLAIN  */
  YYSYMBOL_LK = 58,                        /* LK  */
  YYSYMBOL_EQ = 59,                        /* EQ  */
  YYSYMBOL_LT = 60,                        /* LT  */
  YYSYMBOL_GT = 61,                        /* GT  */
  YYSYMBOL_LE = 62,                        /* LE  */
  YYSYMBOL_GE = 63,                        /* GE  */
  YYSYMBOL_NE = 64,                        /* NE  */
  YYSYMBOL_IS_OP = 65,                     /* IS_OP  */
  YYSYMBOL_IN_OP = 66,                     /* IN_OP  */
  YYSYMBOL_EXIST_OP = 67,                  /* EXIST_OP  */
  YYSYMBOL_NUMBER = 68,                    /* NUMBER  */
  YYSYMBOL_DATE = 69,                      /* DATE  */
  YYSYMBOL_FLOAT = 70,                     /* FLOAT  */
  YYSYMBOL_ID = 71,                        /* ID  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 88,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 89,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_id_list = 91,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_null_def = 96,                  /* null_def  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_value_in_expr = 102,            /* value_in_expr  */
  YYSYMBOL_delete_stmt = 103,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 104,              /* update_stmt  */
  YYSYMBOL_select_stmt = 105,              /* select_stmt  */
  YYSYMBOL_from = 106,                     /* from  */
  YYSYMBOL_join_attr = 107,                /* join_attr  */
  YYSYMBOL_on_attr = 108,                  /* on_attr  */
  YYSYMBOL_order_by_stmt = 109,            /* order_by_stmt  */
  YYSYMBOL_order_type = 110,               /* order_type  */
  YYSYMBOL_order_by_list = 111,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 112,                /* calc_stmt  */
  YYSYMBOL_expression_list = 113,          /* expression_list  */
  YYSYMBOL_expression = 114,               /* expression  */
  YYSYMBOL_complex_expr = 115,             /* complex_expr  */
  YYSYMBOL_possible_argument = 116,        /* possible_argument  */
  YYSYMBOL_complex_expr_list = 117,        /* complex_expr_list  */
  YYSYMBOL_select_attr = 118,              /* select_attr  */
  YYSYMBOL_alias_attr = 119,               /* alias_attr  */
  YYSYMBOL_rel_list = 120,                 /* rel_list  */
  YYSYMBOL_where = 121,                    /* where  */
  YYSYMBOL_condition_list = 122,           /* condition_list  */
  YYSYMBOL_condition = 123,                /* condition  */
  YYSYMBOL_comp_op = 124,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 125,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 126,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 127,        /* set_variable_stmt  */
  YYSYMBOL_set_variable_list = 128,        /* set_variable_list  */
  YYSYMBOL_opt_semicolon = 129             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  281

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   224,   224,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   255,   261,   266,   272,   278,   284,   290,
     297,   303,   311,   327,   347,   350,   361,   371,   390,   393,
     406,   415,   427,   430,   434,   439,   442,   443,   444,   445,
     446,   449,   465,   468,   479,   483,   487,   491,   496,   500,
     507,   511,   515,   520,   524,   530,   542,   556,   590,   593,
     610,   613,   640,   643,   650,   653,   666,   669,   673,   681,
     684,   694,   704,   709,   720,   723,   726,   729,   732,   736,
     739,   748,   751,   754,   757,   760,   764,   767,   770,   773,
     781,   790,   797,   801,   805,   809,   813,   818,   826,   837,
     840,   847,   850,   863,   877,   880,   883,   890,   893,   909,
     912,   918,   921,   925,   931,   935,   942,   943,   944,   945,
     946,   947,   948,   949,   950,   951,   952,   953,   954,   955,
     959,   972,   980,   995,   998,  1011,  1012
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
  "JOIN", "FROM", "WHERE", "ORDER_BY", "ASC", "AS", "AND", "NOT", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "LK", "EQ", "LT", "GT", "LE",
  "GE", "NE", "IS_OP", "IN_OP", "EXIST_OP", "NUMBER", "DATE", "FLOAT",
  "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "id_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "null_def", "number",
  "type", "insert_stmt", "value_list", "value", "value_in_expr",
  "delete_stmt", "update_stmt", "select_stmt", "from", "join_attr",
  "on_attr", "order_by_stmt", "order_type", "order_by_list", "calc_stmt",
  "expression_list", "expression", "complex_expr", "possible_argument",
  "complex_expr_list", "select_attr", "alias_attr", "rel_list", "where",
  "condition_list", "condition", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "set_variable_list",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-227)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     174,   102,    31,   201,   101,   -62,     4,  -227,   -17,   -16,
     -40,  -227,  -227,  -227,  -227,  -227,   -38,   -20,   174,    59,
      60,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,    18,    58,    36,    54,    55,   201,  -227,  -227,  -227,
    -227,  -227,   201,  -227,  -227,   187,   110,   111,   113,   115,
     127,   139,   140,   141,   101,   119,   101,  -227,  -227,    71,
     132,  -227,  -227,   109,   112,   129,   123,   134,  -227,  -227,
    -227,  -227,   185,   130,   163,  -227,   164,   -24,  -227,   201,
     201,   201,   201,   201,   101,   101,   101,   101,   101,   101,
     101,   101,    48,   153,  -227,   154,  -227,   101,   101,   101,
     101,   190,   158,   191,   188,   189,   189,   -27,   161,   166,
     186,   169,   170,  -227,  -227,    -7,    -7,  -227,  -227,    82,
     133,   147,   175,   183,   192,   204,   204,  -227,  -227,  -227,
      12,    12,  -227,  -227,   101,  -227,   -44,   198,   189,   217,
     101,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   176,   218,
     206,   116,   224,   182,   219,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,   101,   227,   228,    71,   244,   205,   245,   -27,
     223,  -227,   241,  -227,   222,  -227,   288,  -227,  -227,  -227,
    -227,  -227,    -3,   166,   268,   274,   230,    88,  -227,  -227,
     190,   231,  -227,   -44,   101,  -227,   275,    -2,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,   253,  -227,  -227,   117,   101,
     246,   235,   239,  -227,   271,  -227,   224,  -227,   238,   282,
    -227,   -44,   244,     5,   -27,   284,  -227,  -227,  -227,  -227,
       2,    88,  -227,   -27,  -227,  -227,   285,  -227,  -227,   282,
     242,   287,   244,   262,  -227,  -227,   289,   275,  -227,   291,
     218,   -29,   292,   282,  -227,  -227,   101,   191,   101,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,     5,   289,
    -227
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     145,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    64,    60,    63,
      61,    62,     0,    90,    81,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,     0,   101,   108,   114,
      68,    31,    30,     0,     0,     0,     0,     0,   141,     1,
     146,     2,     0,     0,     0,    29,     0,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,     0,   116,     0,     0,     0,
       0,   111,     0,    70,     0,   119,   119,     0,     0,     0,
       0,     0,     0,    88,    83,    84,    85,    86,    87,     0,
       0,     0,     0,     0,     0,   109,   109,   106,   100,   115,
     102,   103,   104,   105,     0,   113,   114,     0,   119,     0,
     121,    65,    66,    59,    54,    58,    56,    57,     0,   143,
       0,     0,    38,     0,     0,    36,    91,    92,    93,    94,
      95,    96,     0,     0,     0,   114,   117,     0,    74,     0,
       0,   120,   122,    55,     0,   142,     0,    46,    47,    48,
      49,    50,    42,     0,     0,     0,     0,   110,    97,    98,
     111,     0,    69,   114,     0,    67,    52,     0,   134,   126,
     127,   128,   129,   130,   131,   132,   136,   138,     0,   121,
       0,     0,     0,    44,     0,    41,    38,    37,     0,    34,
     112,   114,   117,    76,     0,     0,   135,   137,   139,   133,
       0,   124,   123,     0,   140,    45,     0,    43,    39,    34,
       0,     0,   117,    72,    78,    77,    79,    52,    51,     0,
     143,    42,     0,    34,    32,   118,   121,    70,     0,    75,
      53,   125,   144,    40,    33,    35,    73,    71,    76,    79,
      80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,   298,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -217,  -227,  -227,    94,   128,    61,  -227,
    -227,  -227,    66,  -177,     9,  -227,  -227,    84,  -227,    62,
    -227,  -227,    47,    49,  -227,   237,    -8,    -4,   194,   131,
    -227,  -145,  -226,  -112,  -212,  -227,  -227,  -227,  -227,   252,
      72,  -227
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   251,    31,    32,   194,   162,   225,   246,
     192,    33,   235,   159,    68,    34,    35,    36,   113,   148,
     267,   205,   256,   269,    37,    54,    55,   180,   173,   145,
      70,   111,   202,   151,   181,   182,   218,    38,    39,    40,
     185,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,   176,   206,   123,   152,   105,   253,   242,   223,    71,
     153,    72,    53,    56,    57,    58,    59,    60,    61,    62,
      63,     4,   224,   222,    73,   254,   265,   106,    64,    74,
     200,    75,   262,    76,   223,    77,   178,    44,    87,    47,
      45,   154,   155,   156,    88,   157,   275,   158,   224,    90,
      91,    92,    93,   255,   276,    53,   236,   257,   232,    79,
     102,    53,   104,    80,   237,   238,   260,    83,    92,    93,
      48,    49,    50,    65,    51,   137,    66,    67,   107,   108,
     109,   110,   125,   126,   127,   128,   252,   109,   110,    82,
     129,   130,   131,   132,   133,   134,   135,   136,    53,    53,
      53,    53,    53,   140,   141,   142,   143,    84,    41,   166,
      42,    43,    56,    57,    58,    59,    60,    61,    62,    63,
     105,   107,   108,   109,   110,    85,    86,    64,    56,    57,
      58,    59,    60,    61,    62,    63,    94,    95,    47,    96,
     175,    97,   106,   240,   107,   108,   109,   110,   187,   188,
     189,   190,   191,    98,    47,   107,   108,   109,   110,   103,
     167,   107,   108,   109,   110,    99,   100,   101,   197,    48,
      49,    50,    65,    51,   168,    66,    67,   112,     1,     2,
     114,    16,   117,   115,     3,    48,    49,    50,    65,    51,
     118,    66,    67,     4,     5,     6,     7,     8,     9,    10,
     233,   120,   169,    11,    12,    13,   107,   108,   109,   110,
     170,   119,    14,    15,   241,    89,   121,   122,   144,   171,
     107,   108,   109,   110,   138,   139,    16,    46,    17,   146,
     149,    18,   172,   160,   147,   150,   102,   161,    47,   163,
     164,   165,   177,   179,   183,   196,   184,   186,   107,   108,
     109,   110,   193,   195,   198,   199,   107,   108,   109,   110,
      90,    91,    92,    93,   278,   107,   108,   109,   110,    48,
      49,    50,   201,    51,   207,    52,   203,   107,   108,   109,
     110,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   219,   204,   220,   221,   227,   107,   108,   109,   110,
     228,   229,   231,   234,   239,   243,   244,   245,   247,   249,
     250,   258,   261,   263,   264,   266,    78,   268,   271,   274,
     248,   226,   273,   270,   259,   279,   124,   116,   280,   277,
     174,   230,   272
};

static const yytype_int16 yycheck[] =
{
       4,   146,   179,    27,   116,    49,   232,   219,    37,    71,
      37,     7,     3,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    51,    26,    41,    20,   252,    71,    26,    45,
     175,    71,   249,    71,    37,    55,   148,     6,    46,    37,
       9,    68,    69,    70,    52,    72,   263,    74,    51,    73,
      74,    75,    76,    48,   266,    46,    58,   234,   203,     0,
      64,    52,    66,     3,    66,    67,   243,     9,    75,    76,
      68,    69,    70,    71,    72,    27,    74,    75,    73,    74,
      75,    76,    90,    91,    92,    93,   231,    75,    76,    71,
      94,    95,    96,    97,    98,    99,   100,   101,    89,    90,
      91,    92,    93,   107,   108,   109,   110,    71,     6,    27,
       8,     9,    11,    12,    13,    14,    15,    16,    17,    18,
      49,    73,    74,    75,    76,    71,    71,    26,    11,    12,
      13,    14,    15,    16,    17,    18,    26,    26,    37,    26,
     144,    26,    71,    26,    73,    74,    75,    76,    32,    33,
      34,    35,    36,    26,    37,    73,    74,    75,    76,    40,
      27,    73,    74,    75,    76,    26,    26,    26,   172,    68,
      69,    70,    71,    72,    27,    74,    75,    45,     4,     5,
      71,    52,    59,    71,    10,    68,    69,    70,    71,    72,
      56,    74,    75,    19,    20,    21,    22,    23,    24,    25,
     204,    71,    27,    29,    30,    31,    73,    74,    75,    76,
      27,    26,    38,    39,   218,    28,    53,    53,    28,    27,
      73,    74,    75,    76,    71,    71,    52,    26,    54,    71,
      42,    57,    28,    72,    43,    46,   240,    71,    37,    53,
      71,    71,    44,    26,    68,    26,    28,    41,    73,    74,
      75,    76,    28,    71,    27,    27,    73,    74,    75,    76,
      73,    74,    75,    76,   268,    73,    74,    75,    76,    68,
      69,    70,    28,    72,    51,    74,    71,    73,    74,    75,
      76,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    50,    47,    71,     6,    27,    73,    74,    75,    76,
      26,    71,    71,    28,    51,    59,    71,    68,    37,    71,
      28,    27,    27,    71,    27,    53,    18,    28,    27,    27,
     226,   193,   261,   257,   240,   278,    89,    75,   279,   267,
     136,   200,   260
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    19,    20,    21,    22,    23,    24,
      25,    29,    30,    31,    38,    39,    52,    54,    57,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    99,   103,   104,   105,   112,   125,   126,
     127,     6,     8,     9,     6,     9,    26,    37,    68,    69,
      70,    72,    74,   102,   113,   114,    11,    12,    13,    14,
      15,    16,    17,    18,    26,    71,    74,    75,   102,   115,
     118,    71,     7,    41,    45,    71,    71,    55,    80,     0,
       3,   129,    71,     9,    71,    71,    71,   114,   114,    28,
      73,    74,    75,    76,    26,    26,    26,    26,    26,    26,
      26,    26,   115,    40,   115,    49,    71,    73,    74,    75,
      76,   119,    45,   106,    71,    71,   127,    59,    56,    26,
      71,    53,    53,    27,   113,   114,   114,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,    27,    71,    71,
     115,   115,   115,   115,    28,   117,    71,    43,   107,    42,
      46,   121,   121,    37,    68,    69,    70,    72,    74,   101,
      72,    71,    95,    53,    71,    71,    27,    27,    27,    27,
      27,    27,    28,   116,   116,   115,   119,    44,   121,    26,
     115,   122,   123,    68,    28,   128,    41,    32,    33,    34,
      35,    36,    98,    28,    94,    71,    26,   115,    27,    27,
     119,    28,   120,    71,    47,   109,   101,    51,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   124,    50,
      71,     6,    26,    37,    51,    96,    95,    27,    26,    71,
     117,    71,   119,   115,    28,   100,    58,    66,    67,    51,
      26,   115,   122,    59,    71,    68,    97,    37,    94,    71,
      28,    91,   119,   120,    20,    48,   110,   101,    27,   105,
     101,    27,    91,    71,    27,   120,    53,   108,    28,   111,
     100,    27,   128,    96,    27,    91,   122,   107,   115,   110,
     111
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    90,    91,    91,    92,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    98,
      98,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     102,   102,   102,   102,   102,   103,   104,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     116,   117,   117,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   127,   128,   128,   129,   129
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     8,     0,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     6,     0,     4,
       0,     7,     0,     2,     0,     4,     0,     1,     1,     0,
       4,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     4,     4,     4,     4,     4,     4,     5,     5,     1,
       3,     1,     3,     3,     3,     3,     3,     2,     1,     0,
       2,     0,     4,     3,     0,     2,     1,     0,     4,     0,
       2,     0,     1,     3,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     1,     2,
       7,     2,     5,     0,     5,     0,     1
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
#line 225 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1862 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 255 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1871 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 261 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1879 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 266 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1887 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 272 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1895 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 278 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1903 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 284 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1911 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 290 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 297 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1929 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 303 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1939 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 312 "yacc_sql.y"
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
#line 1959 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 328 "yacc_sql.y"
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
#line 1979 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 347 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr; 
    }
#line 1987 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 351 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else (yyval.relation_list) = new std::vector<std::string>;
      (yyval.relation_list)->emplace_back(std::string((yyvsp[-1].string)));
      free((yyvsp[-1].string));
    }
#line 1999 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 362 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 372 "yacc_sql.y"
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
#line 2031 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 390 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 394 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2053 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 407 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 2066 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type null_def  */
#line 416 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (bool)(yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2079 "yacc_sql.cpp"
    break;

  case 42: /* null_def: %empty  */
#line 427 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 43: /* null_def: NOT NULL_VAL  */
#line 431 "yacc_sql.y"
    {
      (yyval.number) = 0;
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 44: /* null_def: NULL_VAL  */
#line 435 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 439 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2109 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 442 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2115 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 443 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2121 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 444 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2127 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 445 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2133 "yacc_sql.cpp"
    break;

  case 50: /* type: TEXT_T  */
#line 446 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2139 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 450 "yacc_sql.y"
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
#line 2155 "yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 465 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 468 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2177 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 479 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2186 "yacc_sql.cpp"
    break;

  case 55: /* value: '-' NUMBER  */
#line 483 "yacc_sql.y"
               {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 487 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2204 "yacc_sql.cpp"
    break;

  case 57: /* value: SSS  */
#line 491 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2214 "yacc_sql.cpp"
    break;

  case 58: /* value: DATE  */
#line 496 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 59: /* value: NULL_VAL  */
#line 500 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2232 "yacc_sql.cpp"
    break;

  case 60: /* value_in_expr: NUMBER  */
#line 507 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 61: /* value_in_expr: FLOAT  */
#line 511 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2250 "yacc_sql.cpp"
    break;

  case 62: /* value_in_expr: SSS  */
#line 515 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2260 "yacc_sql.cpp"
    break;

  case 63: /* value_in_expr: DATE  */
#line 520 "yacc_sql.y"
          {
      (yyval.value) = new Value((date_t)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2269 "yacc_sql.cpp"
    break;

  case 64: /* value_in_expr: NULL_VAL  */
#line 524 "yacc_sql.y"
              {
      (yyval.value) = new Value((null_t)0);
      (yyloc) = (yylsp[0]);
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 65: /* delete_stmt: DELETE FROM ID where  */
#line 531 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 66: /* update_stmt: UPDATE ID set_variable_stmt where  */
#line 543 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->update.name.swap((yyvsp[-1].sql_node)->set_variable.name);
      (yyval.sql_node)->update.value.swap((yyvsp[-1].sql_node)->set_variable.value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      delete (yyvsp[-1].sql_node);
    }
#line 2308 "yacc_sql.cpp"
    break;

  case 67: /* select_stmt: SELECT select_attr from join_attr where order_by_stmt  */
#line 557 "yacc_sql.y"
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
#line 2342 "yacc_sql.cpp"
    break;

  case 68: /* from: %empty  */
#line 590 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 69: /* from: FROM ID alias_attr rel_list  */
#line 594 "yacc_sql.y"
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
#line 2367 "yacc_sql.cpp"
    break;

  case 70: /* join_attr: %empty  */
#line 610 "yacc_sql.y"
    {
      (yyval.join_attr) = nullptr;
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 71: /* join_attr: INNER JOIN ID alias_attr rel_list on_attr join_attr  */
#line 614 "yacc_sql.y"
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
#line 2402 "yacc_sql.cpp"
    break;

  case 72: /* on_attr: %empty  */
#line 640 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 73: /* on_attr: ON condition_list  */
#line 644 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2418 "yacc_sql.cpp"
    break;

  case 74: /* order_by_stmt: %empty  */
#line 650 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2426 "yacc_sql.cpp"
    break;

  case 75: /* order_by_stmt: ORDER_BY complex_expr order_type order_by_list  */
#line 654 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 76: /* order_type: %empty  */
#line 666 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2447 "yacc_sql.cpp"
    break;

  case 77: /* order_type: ASC  */
#line 670 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 78: /* order_type: DESC  */
#line 674 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 79: /* order_by_list: %empty  */
#line 681 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 80: /* order_by_list: COMMA complex_expr order_type order_by_list  */
#line 685 "yacc_sql.y"
    {
    if ((yyvsp[0].order_by_list) != nullptr) {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    } else (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>;

      (yyval.order_by_list)->push_back(std::unique_ptr<OrderBySqlNode>(new OrderBySqlNode((yyvsp[-2].complex_expr), (yyvsp[-1].bools))));
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 81: /* calc_stmt: CALC expression_list  */
#line 695 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 705 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression COMMA expression_list  */
#line 710 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2516 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression  */
#line 720 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '-' expression  */
#line 723 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2532 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '*' expression  */
#line 726 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2540 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression  */
#line 729 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2548 "yacc_sql.cpp"
    break;

  case 88: /* expression: LBRACE expression RBRACE  */
#line 732 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2557 "yacc_sql.cpp"
    break;

  case 89: /* expression: '-' expression  */
#line 736 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2565 "yacc_sql.cpp"
    break;

  case 90: /* expression: value_in_expr  */
#line 739 "yacc_sql.y"
                    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2575 "yacc_sql.cpp"
    break;

  case 91: /* complex_expr: MAX_FUNC LBRACE complex_expr RBRACE  */
#line 748 "yacc_sql.y"
                                        {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MAX, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));     
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 92: /* complex_expr: MIN_FUNC LBRACE complex_expr RBRACE  */
#line 751 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_MIN, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 93: /* complex_expr: COUNT_FUNC LBRACE complex_expr RBRACE  */
#line 754 "yacc_sql.y"
                                            {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_COUNT, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 94: /* complex_expr: AVG_FUNC LBRACE complex_expr RBRACE  */
#line 757 "yacc_sql.y"
                                         {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_AVG, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 95: /* complex_expr: SUM_FUNC LBRACE complex_expr RBRACE  */
#line 760 "yacc_sql.y"
                                          {
      (yyval.complex_expr) = new AggrSqlNode(function_type::AGGR_SUM, (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 96: /* complex_expr: LENGTH_FUNC LBRACE complex_expr RBRACE  */
#line 764 "yacc_sql.y"
                                             {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_LENGTH, (yyvsp[-1].complex_expr), nullptr, token_name(sql_string, &(yyloc))); 
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 97: /* complex_expr: ROUND_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 767 "yacc_sql.y"
                                                              {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_ROUND, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 98: /* complex_expr: DATE_FORMAT_FUNC LBRACE complex_expr possible_argument RBRACE  */
#line 770 "yacc_sql.y"
                                                                    {
      (yyval.complex_expr) = new FuncSqlNode(function_type::FUNC_DATE_FORMAT, (yyvsp[-2].complex_expr), (yyvsp[-1].complex_expr), token_name(sql_string, &(yyloc)));
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 99: /* complex_expr: ID  */
#line 773 "yacc_sql.y"
         {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name = "";
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 100: /* complex_expr: ID DOT ID  */
#line 781 "yacc_sql.y"
                {
      RelAttrSqlNode* tmp = new RelAttrSqlNode;
      tmp->relation_name  = (yyvsp[-2].string);
      tmp->attribute_name = (yyvsp[0].string);
      tmp->need_extract = false;
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
      (yyval.complex_expr) = tmp;
    }
#line 2666 "yacc_sql.cpp"
    break;

  case 101: /* complex_expr: '*'  */
#line 790 "yacc_sql.y"
          {
      RelAttrSqlNode* attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      attr->need_extract = true;
      (yyval.complex_expr) = attr;
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 102: /* complex_expr: complex_expr '+' complex_expr  */
#line 797 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::ADD, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 103: /* complex_expr: complex_expr '-' complex_expr  */
#line 801 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::SUB, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 104: /* complex_expr: complex_expr '*' complex_expr  */
#line 805 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::MUL, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 105: /* complex_expr: complex_expr '/' complex_expr  */
#line 809 "yacc_sql.y"
                                    {
      (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::DIV, (yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = false;
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 106: /* complex_expr: LBRACE complex_expr RBRACE  */
#line 813 "yacc_sql.y"
                                 {
      (yyval.complex_expr) = (yyvsp[-1].complex_expr);
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = (yyvsp[-1].complex_expr)->need_extract;
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 107: /* complex_expr: '-' complex_expr  */
#line 818 "yacc_sql.y"
                                    {
      if((yyvsp[0].complex_expr)->get_type() == ExprSqlNode::Type::VALUE_EXPR){
        ValueSqlNode* tmp = (ValueSqlNode*)(yyvsp[0].complex_expr);
        tmp->val.make_negative();
        (yyval.complex_expr) = (ExprSqlNode*)tmp;
      }else (yyval.complex_expr) = create_complex_expression(ArithSqlNode::Type::NEGATIVE, (yyvsp[0].complex_expr), nullptr, sql_string, &(yyloc));
      (yyval.complex_expr)->need_extract = (yyvsp[0].complex_expr)->need_extract;
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 108: /* complex_expr: value_in_expr  */
#line 827 "yacc_sql.y"
    {
      (yyval.complex_expr) = new ValueSqlNode(*(yyvsp[0].value));
      (yyval.complex_expr)->set_name(token_name(sql_string, &(yyloc)));
      (yyval.complex_expr)->need_extract = false;
      delete (yyvsp[0].value);
    }
#line 2748 "yacc_sql.cpp"
    break;

  case 109: /* possible_argument: %empty  */
#line 837 "yacc_sql.y"
    {
      (yyval.complex_expr) = nullptr;
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 110: /* possible_argument: COMMA complex_expr  */
#line 841 "yacc_sql.y"
    {
      (yyval.complex_expr) = (yyvsp[0].complex_expr);
    }
#line 2764 "yacc_sql.cpp"
    break;

  case 111: /* complex_expr_list: %empty  */
#line 847 "yacc_sql.y"
    {
      (yyval.complex_expr_list) = nullptr;
    }
#line 2772 "yacc_sql.cpp"
    break;

  case 112: /* complex_expr_list: COMMA complex_expr alias_attr complex_expr_list  */
#line 850 "yacc_sql.y"
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
#line 2787 "yacc_sql.cpp"
    break;

  case 113: /* select_attr: complex_expr alias_attr complex_expr_list  */
#line 863 "yacc_sql.y"
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
#line 2802 "yacc_sql.cpp"
    break;

  case 114: /* alias_attr: %empty  */
#line 877 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 115: /* alias_attr: AS ID  */
#line 880 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 116: /* alias_attr: ID  */
#line 883 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 117: /* rel_list: %empty  */
#line 890 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 118: /* rel_list: COMMA ID alias_attr rel_list  */
#line 893 "yacc_sql.y"
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
#line 2852 "yacc_sql.cpp"
    break;

  case 119: /* where: %empty  */
#line 909 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 120: /* where: WHERE condition_list  */
#line 912 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list); 
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 121: /* condition_list: %empty  */
#line 918 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2876 "yacc_sql.cpp"
    break;

  case 122: /* condition_list: condition  */
#line 921 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 2885 "yacc_sql.cpp"
    break;

  case 123: /* condition_list: condition AND condition_list  */
#line 925 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 124: /* condition: complex_expr comp_op complex_expr  */
#line 932 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-2].complex_expr), (yyvsp[0].complex_expr), (yyvsp[-1].comp));
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 125: /* condition: complex_expr comp_op LBRACE select_stmt RBRACE  */
#line 936 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode((yyvsp[-4].complex_expr), (yyvsp[-1].sql_node), (yyvsp[-3].comp));
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: EQ  */
#line 942 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2916 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: LT  */
#line 943 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2922 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: GT  */
#line 944 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2928 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: LE  */
#line 945 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2934 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: GE  */
#line 946 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2940 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: NE  */
#line 947 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2946 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: IS_OP  */
#line 948 "yacc_sql.y"
            { (yyval.comp) = IS; }
#line 2952 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: IS_OP NOT  */
#line 949 "yacc_sql.y"
                { (yyval.comp) = IS_NOT; }
#line 2958 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LK  */
#line 950 "yacc_sql.y"
         { (yyval.comp) = LIKE;  }
#line 2964 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: NOT LK  */
#line 951 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;  }
#line 2970 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: IN_OP  */
#line 952 "yacc_sql.y"
            { (yyval.comp) = IN; }
#line 2976 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: NOT IN_OP  */
#line 953 "yacc_sql.y"
                { (yyval.comp) = NOT_IN; }
#line 2982 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: EXIST_OP  */
#line 954 "yacc_sql.y"
               { (yyval.comp) = EXIST; }
#line 2988 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: NOT EXIST_OP  */
#line 955 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXIST; }
#line 2994 "yacc_sql.cpp"
    break;

  case 140: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 960 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 141: /* explain_stmt: EXPLAIN command_wrapper  */
#line 973 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 142: /* set_variable_stmt: SET ID EQ value set_variable_list  */
#line 981 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 143: /* set_variable_list: %empty  */
#line 995 "yacc_sql.y"
    {
      (yyval.sql_node) = nullptr;
    }
#line 3040 "yacc_sql.cpp"
    break;

  case 144: /* set_variable_list: COMMA ID EQ value set_variable_list  */
#line 999 "yacc_sql.y"
    {
      if((yyvsp[0].sql_node) == nullptr)
        (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      else (yyval.sql_node) = (yyvsp[0].sql_node);

      (yyval.sql_node)->set_variable.name.push_back(std::string((yyvsp[-3].string)));
      (yyval.sql_node)->set_variable.value.push_back(*(yyvsp[-1].value));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].value);
    }
#line 3055 "yacc_sql.cpp"
    break;


#line 3059 "yacc_sql.cpp"

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

#line 1014 "yacc_sql.y"

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
