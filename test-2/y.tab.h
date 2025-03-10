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

#line 152 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
