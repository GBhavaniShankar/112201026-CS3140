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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 18 "src/compiler.y"
	
	#include "compiler.h"

	int yylex();
	void yyerror(char* s);
    int i;
	extern FILE* yyin;
	extern DeclScope *global_decls;
	extern Symbol *symbol_table[TABLE_SIZE];
	bool is_true = true;
	Statement *stmts = NULL;

#line 84 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    BEG = 258,                     /* BEG  */
    END = 259,                     /* END  */
    T_INT = 260,                   /* T_INT  */
    T_BOOL = 261,                  /* T_BOOL  */
    T_FLOAT = 262,                 /* T_FLOAT  */
    READ = 263,                    /* READ  */
    WRITE = 264,                   /* WRITE  */
    DECL = 265,                    /* DECL  */
    ENDDECL = 266,                 /* ENDDECL  */
    FLOAT = 267,                   /* FLOAT  */
    VAR = 268,                     /* VAR  */
    NUM = 269,                     /* NUM  */
    IF = 270,                      /* IF  */
    THEN = 271,                    /* THEN  */
    ELSE = 272,                    /* ELSE  */
    ENDIF = 273,                   /* ENDIF  */
    LOGICAL_AND = 274,             /* LOGICAL_AND  */
    LOGICAL_NOT = 275,             /* LOGICAL_NOT  */
    LOGICAL_OR = 276,              /* LOGICAL_OR  */
    EQUALEQUAL = 277,              /* EQUALEQUAL  */
    LESSTHANOREQUAL = 278,         /* LESSTHANOREQUAL  */
    GREATERTHANOREQUAL = 279,      /* GREATERTHANOREQUAL  */
    NOTEQUAL = 280,                /* NOTEQUAL  */
    WHILE = 281,                   /* WHILE  */
    DO = 282,                      /* DO  */
    ENDWHILE = 283,                /* ENDWHILE  */
    FOR = 284,                     /* FOR  */
    STRING = 285,                  /* STRING  */
    BREAK = 286,                   /* BREAK  */
    T = 287,                       /* T  */
    F = 288,                       /* F  */
    MAIN = 289,                    /* MAIN  */
    RETURN = 290                   /* RETURN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define BEG 258
#define END 259
#define T_INT 260
#define T_BOOL 261
#define T_FLOAT 262
#define READ 263
#define WRITE 264
#define DECL 265
#define ENDDECL 266
#define FLOAT 267
#define VAR 268
#define NUM 269
#define IF 270
#define THEN 271
#define ELSE 272
#define ENDIF 273
#define LOGICAL_AND 274
#define LOGICAL_NOT 275
#define LOGICAL_OR 276
#define EQUALEQUAL 277
#define LESSTHANOREQUAL 278
#define GREATERTHANOREQUAL 279
#define NOTEQUAL 280
#define WHILE 281
#define DO 282
#define ENDWHILE 283
#define FOR 284
#define STRING 285
#define BREAK 286
#define T 287
#define F 288
#define MAIN 289
#define RETURN 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "src/compiler.y"

	int val;
	float fval;
	char* var;
	char* id;
	char* op;
	bool boolen;
	Node* node;
	Statement* stmts;
	DeclScope* decl_scope;
    DeclNode* decl;
	VariableData* var_data;
	SymbolType type;

#line 222 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BEG = 3,                        /* BEG  */
  YYSYMBOL_END = 4,                        /* END  */
  YYSYMBOL_T_INT = 5,                      /* T_INT  */
  YYSYMBOL_T_BOOL = 6,                     /* T_BOOL  */
  YYSYMBOL_T_FLOAT = 7,                    /* T_FLOAT  */
  YYSYMBOL_READ = 8,                       /* READ  */
  YYSYMBOL_WRITE = 9,                      /* WRITE  */
  YYSYMBOL_DECL = 10,                      /* DECL  */
  YYSYMBOL_ENDDECL = 11,                   /* ENDDECL  */
  YYSYMBOL_FLOAT = 12,                     /* FLOAT  */
  YYSYMBOL_VAR = 13,                       /* VAR  */
  YYSYMBOL_NUM = 14,                       /* NUM  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_THEN = 16,                      /* THEN  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_ENDIF = 18,                     /* ENDIF  */
  YYSYMBOL_LOGICAL_AND = 19,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_NOT = 20,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_OR = 21,                /* LOGICAL_OR  */
  YYSYMBOL_EQUALEQUAL = 22,                /* EQUALEQUAL  */
  YYSYMBOL_LESSTHANOREQUAL = 23,           /* LESSTHANOREQUAL  */
  YYSYMBOL_GREATERTHANOREQUAL = 24,        /* GREATERTHANOREQUAL  */
  YYSYMBOL_NOTEQUAL = 25,                  /* NOTEQUAL  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_DO = 27,                        /* DO  */
  YYSYMBOL_ENDWHILE = 28,                  /* ENDWHILE  */
  YYSYMBOL_FOR = 29,                       /* FOR  */
  YYSYMBOL_STRING = 30,                    /* STRING  */
  YYSYMBOL_BREAK = 31,                     /* BREAK  */
  YYSYMBOL_T = 32,                         /* T  */
  YYSYMBOL_F = 33,                         /* F  */
  YYSYMBOL_MAIN = 34,                      /* MAIN  */
  YYSYMBOL_RETURN = 35,                    /* RETURN  */
  YYSYMBOL_36_ = 36,                       /* '<'  */
  YYSYMBOL_37_ = 37,                       /* '>'  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* '%'  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_45_ = 45,                       /* '['  */
  YYSYMBOL_46_ = 46,                       /* ']'  */
  YYSYMBOL_47_ = 47,                       /* '('  */
  YYSYMBOL_48_ = 48,                       /* ')'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '}'  */
  YYSYMBOL_51_ = 51,                       /* '='  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_Prog = 53,                      /* Prog  */
  YYSYMBOL_Gdecl_sec = 54,                 /* Gdecl_sec  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_Gdecl_list = 56,                /* Gdecl_list  */
  YYSYMBOL_Gdecl = 57,                     /* Gdecl  */
  YYSYMBOL_ret_type = 58,                  /* ret_type  */
  YYSYMBOL_Glist = 59,                     /* Glist  */
  YYSYMBOL_Gid = 60,                       /* Gid  */
  YYSYMBOL_arg_list = 61,                  /* arg_list  */
  YYSYMBOL_arg_list1 = 62,                 /* arg_list1  */
  YYSYMBOL_arg = 63,                       /* arg  */
  YYSYMBOL_arg_type = 64,                  /* arg_type  */
  YYSYMBOL_var_list = 65,                  /* var_list  */
  YYSYMBOL_Fdef_sec = 66,                  /* Fdef_sec  */
  YYSYMBOL_Fdef = 67,                      /* Fdef  */
  YYSYMBOL_func_ret_type = 68,             /* func_ret_type  */
  YYSYMBOL_func_name = 69,                 /* func_name  */
  YYSYMBOL_FargList = 70,                  /* FargList  */
  YYSYMBOL_ret_stmt = 71,                  /* ret_stmt  */
  YYSYMBOL_MainBlock = 72,                 /* MainBlock  */
  YYSYMBOL_main = 73,                      /* main  */
  YYSYMBOL_Ldecl_sec = 74,                 /* Ldecl_sec  */
  YYSYMBOL_Ldecl_list = 75,                /* Ldecl_list  */
  YYSYMBOL_Ldecl = 76,                     /* Ldecl  */
  YYSYMBOL_type = 77,                      /* type  */
  YYSYMBOL_Lid_list = 78,                  /* Lid_list  */
  YYSYMBOL_Lid = 79,                       /* Lid  */
  YYSYMBOL_stmt_list = 80,                 /* stmt_list  */
  YYSYMBOL_statement = 81,                 /* statement  */
  YYSYMBOL_break_stmt = 82,                /* break_stmt  */
  YYSYMBOL_read_stmt = 83,                 /* read_stmt  */
  YYSYMBOL_write_stmt = 84,                /* write_stmt  */
  YYSYMBOL_assign_stmt = 85,               /* assign_stmt  */
  YYSYMBOL_cond_stmt = 86,                 /* cond_stmt  */
  YYSYMBOL_func_stmt = 87,                 /* func_stmt  */
  YYSYMBOL_func_call = 88,                 /* func_call  */
  YYSYMBOL_param_list = 89,                /* param_list  */
  YYSYMBOL_param_list1 = 90,               /* param_list1  */
  YYSYMBOL_para = 91,                      /* para  */
  YYSYMBOL_expr = 92,                      /* expr  */
  YYSYMBOL_var_expr = 93                   /* var_expr  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   459

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
       2,     2,     2,     2,     2,     2,     2,    42,     2,     2,
      47,    48,    40,    38,    44,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      36,    51,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    83,    83,    86,    88,    92,    96,    97,
      98,   102,   103,   107,   108,   109,   116,   118,   122,   123,
     127,   131,   135,   136,   139,   141,   145,   149,   153,   157,
     161,   165,   166,   170,   174,   177,   179,   183,   187,   191,
     192,   196,   200,   201,   202,   206,   207,   208,   209,   210,
     211,   215,   219,   223,   224,   228,   232,   233,   234,   235,
     239,   243,   246,   248,   252,   253,   257,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   287,   288,   289
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BEG", "END", "T_INT",
  "T_BOOL", "T_FLOAT", "READ", "WRITE", "DECL", "ENDDECL", "FLOAT", "VAR",
  "NUM", "IF", "THEN", "ELSE", "ENDIF", "LOGICAL_AND", "LOGICAL_NOT",
  "LOGICAL_OR", "EQUALEQUAL", "LESSTHANOREQUAL", "GREATERTHANOREQUAL",
  "NOTEQUAL", "WHILE", "DO", "ENDWHILE", "FOR", "STRING", "BREAK", "T",
  "F", "MAIN", "RETURN", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "';'", "','", "'['", "']'", "'('", "')'", "'{'", "'}'", "'='", "$accept",
  "Prog", "Gdecl_sec", "$@1", "Gdecl_list", "Gdecl", "ret_type", "Glist",
  "Gid", "arg_list", "arg_list1", "arg", "arg_type", "var_list",
  "Fdef_sec", "Fdef", "func_ret_type", "func_name", "FargList", "ret_stmt",
  "MainBlock", "main", "Ldecl_sec", "Ldecl_list", "Ldecl", "type",
  "Lid_list", "Lid", "stmt_list", "statement", "break_stmt", "read_stmt",
  "write_stmt", "assign_stmt", "cond_stmt", "func_stmt", "func_call",
  "param_list", "param_list1", "para", "expr", "var_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   -52,     1,   -52,     3,   -52,     9,   -52,   -52,   -52,
       0,     3,    17,   232,   -52,   -52,    -9,   -52,   -52,   -52,
     -12,    -6,    -2,    -5,     6,    10,   -27,   166,     7,    26,
     -52,    43,    31,    32,    35,    37,    48,   -52,    50,   -52,
      38,   -52,   -52,    67,    68,   102,   -52,    17,   -52,   105,
     157,   166,   118,   -52,   -52,   166,   -52,   -52,    12,   166,
     -52,   353,   -52,    14,   105,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   166,   114,    72,    75,   -52,    77,    76,    78,
      46,   299,    79,   -52,    81,   393,   -52,   -52,   -52,   243,
     208,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,    73,    85,   393,   -52,   -52,    86,
     -52,   121,    88,    90,    95,   -52,   -52,   -52,    97,   -52,
     166,   -52,    -1,   -52,   -52,    71,    71,    71,    71,   417,
     417,   235,   235,   -14,   -14,    53,   119,   166,   114,   100,
     -52,    98,   139,   138,   166,   -52,   242,   -52,   107,   360,
     -52,   121,   139,   151,   160,   122,   325,   142,   166,   105,
     -52,   161,   -52,   156,   151,   159,   193,   -52,   -52,   -52,
     271,   125,   193,   -52,   -52,   -52,   132,   137,   147,   140,
     135,   147,   -52,   159,   166,   181,   -52,    14,   187,   -52,
     385,   143,   145,   150,   -52,   -52,   -52,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,    24,     5,     1,     0,     8,     9,    10,
       0,     5,     0,     0,    27,    25,     0,     2,     4,     6,
      15,     0,    11,     0,     0,     0,    93,    67,     0,     0,
      51,     0,     0,     0,     0,     0,     0,    48,     0,    60,
       0,    28,    33,     0,     0,     0,     7,     0,    44,     0,
      67,    67,    67,    68,    70,    67,    73,    74,     0,    67,
      90,     0,    72,     0,     0,    32,    43,    50,    46,    47,
      45,    49,    67,    16,     0,     0,    12,    93,     0,     0,
       0,     0,     0,    63,    64,    66,    87,    69,    71,     0,
       0,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,     0,     0,    55,    21,    29,    17,
      19,     0,     0,     0,    13,    52,    54,    53,    91,    61,
      67,    75,     0,    88,    89,    86,    84,    83,    85,    81,
      82,    76,    77,    78,    79,    80,     0,    67,     0,    22,
      20,     0,     0,     0,    67,    65,     0,    56,     0,     0,
      18,     0,     0,    35,     0,     0,     0,     0,    67,     0,
      23,     0,    38,     0,    35,     0,     0,    14,    92,    57,
       0,     0,     0,    34,    36,    41,     0,    39,     0,     0,
       0,     0,    37,     0,    67,     0,    59,     0,     0,    40,
       0,     0,     0,     0,    30,    31,    58,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -52,   -52,   -52,   -52,   186,   -52,   -52,   163,   -52,   -52,
     -52,    54,   -52,    52,   -52,   -52,   -52,   -52,   -52,    30,
     -52,   -52,    55,    51,   -52,   -52,    29,   -52,   -29,   -52,
     -52,   -52,   -52,   -51,   -52,   -52,   -11,   -52,    94,   -52,
       4,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    10,    11,    12,    21,    22,   108,
     109,   110,   111,   140,     6,    15,    16,    43,   112,   185,
      17,    44,   154,   163,   164,   165,   176,   177,    31,    32,
      33,    34,    35,    36,    37,    38,    60,    82,    83,    84,
      85,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,     5,    39,    66,    41,    91,     1,    92,     7,     8,
       9,    18,    13,   105,    14,    23,   146,   147,    51,    40,
      52,    39,    24,    25,    87,    42,    88,    26,   103,    27,
      20,    61,    23,    45,   104,   -42,    78,    46,    48,    24,
      25,    28,    47,    29,    26,    30,    27,    65,   -42,   -42,
      40,    40,    39,    49,    80,    81,    63,    50,    28,    86,
      29,   122,    30,    89,   -42,    91,   -42,    92,    93,    94,
      95,    96,    91,    64,    92,    67,   106,    40,    68,    39,
      69,   -42,    97,    98,    99,   100,   101,   102,   103,    72,
      91,    70,    92,    71,   117,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   171,    99,
     100,   101,   102,   103,    73,    74,    75,   157,    77,   107,
     113,   114,    51,   136,   115,   120,   116,   119,   137,   138,
      53,    26,    54,    40,   139,    39,   141,   178,    55,   142,
     143,   149,   144,   181,   151,   148,    40,   152,   156,   153,
      56,    57,   155,    40,   158,    39,   162,    58,   192,    40,
     169,    39,   170,   166,   172,    59,   -62,   173,   167,    53,
      26,    54,   175,   180,    40,   182,    39,    55,    53,    26,
      54,   183,   184,   186,   187,   191,    55,    79,   190,    56,
      57,   193,   150,   195,    23,   196,    58,    19,    56,    57,
     197,    24,    25,   160,    59,    58,    26,   161,    27,    23,
      76,   188,   189,    59,   145,   174,    24,    25,     0,     0,
      28,    26,    29,    27,    30,   -42,   -42,     0,   -42,     0,
       0,     0,     0,    23,     0,    28,   -42,    29,     0,    30,
      24,    25,     0,    23,     0,    26,     0,    27,     0,     0,
      24,    25,     0,     0,    91,    26,    92,    27,     0,    28,
     -42,    29,    91,    30,    92,    93,    94,    95,    96,    28,
       0,    29,     0,    30,     0,   101,   102,   103,     0,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
      91,   121,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,    91,   179,
      92,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101,
     102,   103,     0,     0,    91,   118,    92,    93,    94,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,    98,    99,   100,   101,   102,   103,     0,    90,
       0,   168,    91,     0,    92,    93,    94,    95,    96,    91,
       0,    92,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,    97,    98,    99,   100,
     101,   102,   103,   159,    91,     0,    92,    93,    94,    95,
      96,     0,    91,     0,    92,    93,    94,    95,    96,     0,
       0,    97,    98,    99,   100,   101,   102,   103,   194,    97,
      98,    99,   100,   101,   102,   103,    91,     0,    92,    93,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   100,   101,   102,   103
};

static const yytype_int16 yycheck[] =
{
      13,     0,    13,    32,    13,    19,    10,    21,     5,     6,
       7,    11,     3,    64,     5,     1,    17,    18,    45,    32,
      47,    32,     8,     9,    12,    34,    14,    13,    42,    15,
      13,    27,     1,    45,    63,     4,    49,    43,    43,     8,
       9,    27,    44,    29,    13,    31,    15,     4,    17,    18,
      63,    64,    63,    47,    50,    51,    49,    47,    27,    55,
      29,    90,    31,    59,    50,    19,    35,    21,    22,    23,
      24,    25,    19,    47,    21,    43,    72,    90,    43,    90,
      43,    50,    36,    37,    38,    39,    40,    41,    42,    51,
      19,    43,    21,    43,    48,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   159,    38,
      39,    40,    41,    42,    47,    47,    14,   146,    13,     5,
      48,    46,    45,    50,    48,    44,    48,    48,    43,    43,
      12,    13,    14,   146,    13,   146,    48,   166,    20,    49,
      45,   137,    45,   172,    44,    26,   159,    49,   144,    10,
      32,    33,    14,   166,    47,   166,     5,    39,   187,   172,
      18,   172,   158,     3,     3,    47,    48,    11,    46,    12,
      13,    14,    13,    48,   187,    43,   187,    20,    12,    13,
      14,    44,    35,    43,    49,     4,    20,    30,   184,    32,
      33,     4,   138,    50,     1,    50,    39,    11,    32,    33,
      50,     8,     9,   151,    47,    39,    13,   152,    15,     1,
      47,   181,   183,    47,   120,   164,     8,     9,    -1,    -1,
      27,    13,    29,    15,    31,    17,    18,    -1,    35,    -1,
      -1,    -1,    -1,     1,    -1,    27,     4,    29,    -1,    31,
       8,     9,    -1,     1,    -1,    13,    -1,    15,    -1,    -1,
       8,     9,    -1,    -1,    19,    13,    21,    15,    -1,    27,
      18,    29,    19,    31,    21,    22,    23,    24,    25,    27,
      -1,    29,    -1,    31,    -1,    40,    41,    42,    -1,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      19,    48,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    19,    48,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    19,    46,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    -1,    16,
      -1,    46,    19,    -1,    21,    22,    23,    24,    25,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    36,    37,    38,    39,
      40,    41,    42,    43,    19,    -1,    21,    22,    23,    24,
      25,    -1,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    36,
      37,    38,    39,    40,    41,    42,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    53,    54,    55,     0,    66,     5,     6,     7,
      56,    57,    58,     3,     5,    67,    68,    72,    11,    56,
      13,    59,    60,     1,     8,     9,    13,    15,    27,    29,
      31,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      93,    13,    34,    69,    73,    45,    43,    44,    43,    47,
      47,    45,    47,    12,    14,    20,    32,    33,    39,    47,
      88,    92,    93,    49,    47,     4,    80,    43,    43,    43,
      43,    43,    51,    47,    47,    14,    59,    13,    93,    30,
      92,    92,    89,    90,    91,    92,    92,    12,    14,    92,
      16,    19,    21,    22,    23,    24,    25,    36,    37,    38,
      39,    40,    41,    42,    80,    85,    92,     5,    61,    62,
      63,    64,    70,    48,    46,    48,    48,    48,    46,    48,
      44,    48,    80,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    50,    43,    43,    13,
      65,    48,    49,    45,    45,    90,    17,    18,    26,    92,
      63,    44,    49,    10,    74,    14,    92,    80,    47,    43,
      65,    74,     5,    75,    76,    77,     3,    46,    46,    18,
      92,    85,     3,    11,    75,    13,    78,    79,    80,    48,
      48,    80,    43,    44,    35,    71,    43,    49,    71,    78,
      92,     4,    80,     4,    43,    50,    50,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    55,    54,    56,    56,    57,    58,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      63,    64,    65,    65,    66,    66,    67,    68,    69,    70,
      71,    72,    72,    73,    74,    75,    75,    76,    77,    78,
      78,    79,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    82,    83,    84,    84,    85,    86,    86,    86,    86,
      87,    88,    89,    89,    90,    90,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     4,     0,     2,     3,     1,     1,
       1,     1,     3,     4,     7,     1,     0,     1,     3,     1,
       2,     1,     1,     3,     0,     2,    12,     1,     1,     1,
       3,    11,     3,     1,     3,     0,     2,     3,     1,     1,
       3,     1,     0,     2,     2,     2,     2,     2,     1,     2,
       2,     1,     4,     4,     4,     3,     5,     7,    11,     9,
       1,     4,     0,     1,     1,     3,     1,     0,     1,     2,
       1,     2,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       1,     4,     7,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* $@1: %empty  */
#line 83 "src/compiler.y"
               { initialize_global(); init_symbol_table(); }
#line 1478 "y.tab.c"
    break;

  case 4: /* Gdecl_sec: DECL $@1 Gdecl_list ENDDECL  */
#line 83 "src/compiler.y"
                                                                                { print_decls(); free_decls(); }
#line 1484 "y.tab.c"
    break;

  case 7: /* Gdecl: ret_type Glist ';'  */
#line 92 "src/compiler.y"
                               {add_symbols((yyvsp[-2].type), (yyvsp[-1].var_data));}
#line 1490 "y.tab.c"
    break;

  case 8: /* ret_type: T_INT  */
#line 96 "src/compiler.y"
                  { (yyval.type) = SYMBOL_INT;}
#line 1496 "y.tab.c"
    break;

  case 9: /* ret_type: T_BOOL  */
#line 97 "src/compiler.y"
                   { (yyval.type) = SYMBOL_BOOL;}
#line 1502 "y.tab.c"
    break;

  case 10: /* ret_type: T_FLOAT  */
#line 98 "src/compiler.y"
                     { (yyval.type) = SYMBOL_FLOAT; }
#line 1508 "y.tab.c"
    break;

  case 11: /* Glist: Gid  */
#line 102 "src/compiler.y"
                {(yyval.var_data) = (yyvsp[0].var_data);}
#line 1514 "y.tab.c"
    break;

  case 12: /* Glist: Gid ',' Glist  */
#line 103 "src/compiler.y"
                          { (yyvsp[-2].var_data)->next = (yyvsp[0].var_data); (yyval.var_data) = (yyvsp[-2].var_data);}
#line 1520 "y.tab.c"
    break;

  case 13: /* Gid: VAR '[' NUM ']'  */
#line 107 "src/compiler.y"
                           { (yyval.var_data) = add_arr((yyvsp[-3].var), (yyvsp[-1].val)); }
#line 1526 "y.tab.c"
    break;

  case 14: /* Gid: VAR '[' NUM ']' '[' NUM ']'  */
#line 108 "src/compiler.y"
                                     { (yyval.var_data) = add_2d_arr((yyvsp[-6].var), (yyvsp[-4].val), (yyvsp[-1].val)); }
#line 1532 "y.tab.c"
    break;

  case 15: /* Gid: VAR  */
#line 109 "src/compiler.y"
                 { (yyval.var_data) = add_var((yyvsp[0].var));}
#line 1538 "y.tab.c"
    break;

  case 32: /* MainBlock: BEG stmt_list END  */
#line 166 "src/compiler.y"
                              { stmts = (yyvsp[-1].stmts); }
#line 1544 "y.tab.c"
    break;

  case 42: /* stmt_list: %empty  */
#line 200 "src/compiler.y"
                        { (yyval.stmts) = NULL; }
#line 1550 "y.tab.c"
    break;

  case 43: /* stmt_list: statement stmt_list  */
#line 201 "src/compiler.y"
                                { (yyval.stmts) = (yyvsp[-1].stmts); (yyvsp[-1].stmts)->next = (yyvsp[0].stmts); }
#line 1556 "y.tab.c"
    break;

  case 45: /* statement: assign_stmt ';'  */
#line 206 "src/compiler.y"
                                         { (yyval.stmts) = (yyvsp[-1].stmts); }
#line 1562 "y.tab.c"
    break;

  case 46: /* statement: read_stmt ';'  */
#line 207 "src/compiler.y"
                                   {}
#line 1568 "y.tab.c"
    break;

  case 47: /* statement: write_stmt ';'  */
#line 208 "src/compiler.y"
                                   { (yyval.stmts) = (yyvsp[-1].stmts); }
#line 1574 "y.tab.c"
    break;

  case 48: /* statement: cond_stmt  */
#line 209 "src/compiler.y"
                                   { (yyval.stmts) = (yyvsp[0].stmts); }
#line 1580 "y.tab.c"
    break;

  case 49: /* statement: func_stmt ';'  */
#line 210 "src/compiler.y"
                                   {}
#line 1586 "y.tab.c"
    break;

  case 50: /* statement: break_stmt ';'  */
#line 211 "src/compiler.y"
                                   { (yyval.stmts) = (yyvsp[-1].stmts); }
#line 1592 "y.tab.c"
    break;

  case 51: /* break_stmt: BREAK  */
#line 215 "src/compiler.y"
                             { (yyval.stmts) = create_break_stmt(); }
#line 1598 "y.tab.c"
    break;

  case 53: /* write_stmt: WRITE '(' expr ')'  */
#line 223 "src/compiler.y"
                               { (yyval.stmts) = create_write_stmt((yyvsp[-1].node)); }
#line 1604 "y.tab.c"
    break;

  case 54: /* write_stmt: WRITE '(' STRING ')'  */
#line 224 "src/compiler.y"
                                     { (yyval.stmts) = create_write_stmt_string((yyvsp[-1].id)); }
#line 1610 "y.tab.c"
    break;

  case 55: /* assign_stmt: var_expr '=' expr  */
#line 228 "src/compiler.y"
                              { (yyval.stmts) = create_assign_stmt((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1616 "y.tab.c"
    break;

  case 56: /* cond_stmt: IF expr THEN stmt_list ENDIF  */
#line 232 "src/compiler.y"
                                         {(yyval.stmts) = create_if_stmt((yyvsp[-3].node), (yyvsp[-1].stmts), NULL); }
#line 1622 "y.tab.c"
    break;

  case 57: /* cond_stmt: IF expr THEN stmt_list ELSE stmt_list ENDIF  */
#line 233 "src/compiler.y"
                                                        {(yyval.stmts) = create_if_stmt((yyvsp[-5].node), (yyvsp[-3].stmts), (yyvsp[-1].stmts)); }
#line 1628 "y.tab.c"
    break;

  case 58: /* cond_stmt: FOR '(' assign_stmt ';' expr ';' assign_stmt ')' '{' stmt_list '}'  */
#line 234 "src/compiler.y"
                                                                               {(yyval.stmts) = create_for_stmt((yyvsp[-8].stmts), (yyvsp[-6].node), (yyvsp[-4].stmts), (yyvsp[-1].stmts));}
#line 1634 "y.tab.c"
    break;

  case 59: /* cond_stmt: DO '{' stmt_list '}' WHILE '(' expr ')' ';'  */
#line 235 "src/compiler.y"
                                                      {(yyval.stmts) = create_do_while_stmt((yyvsp[-6].stmts), (yyvsp[-2].node));}
#line 1640 "y.tab.c"
    break;

  case 67: /* expr: %empty  */
#line 260 "src/compiler.y"
                        {(yyval.node) = NULL;}
#line 1646 "y.tab.c"
    break;

  case 68: /* expr: FLOAT  */
#line 261 "src/compiler.y"
                  {(yyval.node) = create_float_node((yyvsp[0].fval)); }
#line 1652 "y.tab.c"
    break;

  case 69: /* expr: '-' FLOAT  */
#line 262 "src/compiler.y"
                          { (yyval.node) = create_float_node((yyvsp[0].fval));}
#line 1658 "y.tab.c"
    break;

  case 70: /* expr: NUM  */
#line 263 "src/compiler.y"
                 { (yyval.node) = create_num_node((yyvsp[0].val)); }
#line 1664 "y.tab.c"
    break;

  case 71: /* expr: '-' NUM  */
#line 264 "src/compiler.y"
                    { (yyval.node) = create_num_node(-1 * (yyvsp[0].val)); }
#line 1670 "y.tab.c"
    break;

  case 72: /* expr: var_expr  */
#line 265 "src/compiler.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1676 "y.tab.c"
    break;

  case 73: /* expr: T  */
#line 266 "src/compiler.y"
              { (yyval.node) = create_bool_node(true); }
#line 1682 "y.tab.c"
    break;

  case 74: /* expr: F  */
#line 267 "src/compiler.y"
              { (yyval.node) = create_bool_node(false); }
#line 1688 "y.tab.c"
    break;

  case 75: /* expr: '(' expr ')'  */
#line 268 "src/compiler.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1694 "y.tab.c"
    break;

  case 76: /* expr: expr '+' expr  */
#line 269 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1700 "y.tab.c"
    break;

  case 77: /* expr: expr '-' expr  */
#line 270 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1706 "y.tab.c"
    break;

  case 78: /* expr: expr '*' expr  */
#line 271 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1712 "y.tab.c"
    break;

  case 79: /* expr: expr '/' expr  */
#line 272 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1718 "y.tab.c"
    break;

  case 80: /* expr: expr '%' expr  */
#line 273 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1724 "y.tab.c"
    break;

  case 81: /* expr: expr '<' expr  */
#line 274 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1730 "y.tab.c"
    break;

  case 82: /* expr: expr '>' expr  */
#line 275 "src/compiler.y"
                          { (yyval.node) = create_expr_node(TOKEN_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1736 "y.tab.c"
    break;

  case 83: /* expr: expr GREATERTHANOREQUAL expr  */
#line 276 "src/compiler.y"
                                         { (yyval.node) = create_expr_node(TOKEN_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1742 "y.tab.c"
    break;

  case 84: /* expr: expr LESSTHANOREQUAL expr  */
#line 277 "src/compiler.y"
                                      { (yyval.node) = create_expr_node(TOKEN_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1748 "y.tab.c"
    break;

  case 85: /* expr: expr NOTEQUAL expr  */
#line 278 "src/compiler.y"
                               { (yyval.node) = create_expr_node(TOKEN_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1754 "y.tab.c"
    break;

  case 86: /* expr: expr EQUALEQUAL expr  */
#line 279 "src/compiler.y"
                                 { (yyval.node) = create_expr_node(TOKEN_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1760 "y.tab.c"
    break;

  case 87: /* expr: LOGICAL_NOT expr  */
#line 280 "src/compiler.y"
                             { (yyval.node) = create_expr_node(TOKEN_NOT, NULL, (yyvsp[0].node)); }
#line 1766 "y.tab.c"
    break;

  case 88: /* expr: expr LOGICAL_AND expr  */
#line 281 "src/compiler.y"
                                  { (yyval.node) = create_expr_node(TOKEN_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1772 "y.tab.c"
    break;

  case 89: /* expr: expr LOGICAL_OR expr  */
#line 282 "src/compiler.y"
                                 { (yyval.node) = create_expr_node(TOKEN_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1778 "y.tab.c"
    break;

  case 91: /* var_expr: VAR '[' expr ']'  */
#line 287 "src/compiler.y"
                                 { (yyval.node) = create_array_node((yyvsp[-3].var), (yyvsp[-1].node)); }
#line 1784 "y.tab.c"
    break;

  case 92: /* var_expr: VAR '[' expr ']' '[' expr ']'  */
#line 288 "src/compiler.y"
                                          {(yyval.node) = create_2d_array_node((yyvsp[-6].var), (yyvsp[-4].node), (yyvsp[-1].node));}
#line 1790 "y.tab.c"
    break;

  case 93: /* var_expr: VAR  */
#line 289 "src/compiler.y"
            { (yyval.node) = create_var_node((yyvsp[0].var)); }
#line 1796 "y.tab.c"
    break;


#line 1800 "y.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 292 "src/compiler.y"


void yyerror(char *s) 
{
   fprintf(stderr, "%s\n", s);
}

int main(int argc, char* argv[]){

	yyparse();

	eval_stmts(stmts);
	print_all_statements_tree(stmts);
	free_statements(stmts);

	print_symbol_table();
	free_symbol_table();

	return 0;
}
