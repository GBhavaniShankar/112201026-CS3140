/*
 *   This file is part of SIL Compiler.
 *
 *  SIL Compiler is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SIL Compiler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SIL Compiler.  If not, see <http://www.gnu.org/licenses/>.
 */

%{	
	#include "hash.h"
	#include "node.h"
	#include <ctype.h>
	#define nxlin() printf("\n");

	int yylex();
	void yyerror(char* s);
    int i;
	extern FILE* yyin;
	extern HashNode *hash_table[TABLE_SIZE];

	char* to_uppercase(char *str) {
        char *ptr = str;
        while (*ptr) {
            *ptr = toupper((unsigned char)*ptr);
            ptr++;
        }
        return str;
    }
%}

%union{
	int val;
	char* var;
	char* id;
	Node* node;
}

%token <id> BEG END
%token <id> T_INT T_BOOL
%token <id> READ WRITE
%token <id> DECL ENDDECL
%token <var> VAR 
%token <val> NUM
%token <id> IF THEN ELSE ENDIF
%token <id> LOGICAL_AND LOGICAL_NOT LOGICAL_OR
%token <id> EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%token <id> WHILE DO ENDWHILE FOR 
%token T F 
%token <id> MAIN RETURN


%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT

%type <node> Prog Gdecl_sec Gdecl_list Gdecl ret_type Glist Gid func arg_list arg_list1 arg arg_type var_list
%type <node> Fdef_sec Fdef func_ret_type func_name FargList ret_stmt MainBlock main Ldecl_sec Ldecl_list 
%type <node> Ldecl type Lid_list Lid stmt_list statement read_stmt write_stmt assign_stmt cond_stmt func_stmt
%type <node> func_call param_list param_list1 para expr str_expr var_expr

%%

	Prog	:	Gdecl_sec Fdef_sec MainBlock 
		;
		
	Gdecl_sec:	DECL Gdecl_list ENDDECL		{print_tree($2); nxlin();}
		;
		
	Gdecl_list: {$$ = NULL;}
		| 	Gdecl Gdecl_list {$$ = create_node(tokenId, 0, 0, "DEC", $1, $2);}
		;
		
	Gdecl 	:	ret_type Glist ';'{$$ = $1; $$->right = $2;}
		;
		
	ret_type:	T_INT		{$$ = create_node(tokenId, 0, 0, "INT", NULL, NULL);}
		;
		
	Glist 	:	Gid { $$ = $1;}
		| 	func 
		|	Gid ',' Glist { $$ = $1; $$->right = $3;}
		|	func ',' Glist
		;
	
	Gid	:	VAR		{$$ = create_node(tokenVar, 0, 0, $1, NULL, NULL); insert($1, -1, 0);}
		|	Gid '[' NUM ']'	{                                                   }

		;
		
	func 	:	VAR '(' arg_list ')' 					{ 					}
		;
			
	arg_list:	
		|	arg_list1
		;
		
	arg_list1:	arg_list1 ';' arg
		|	arg
		;
		
	arg 	:	arg_type var_list	
		;
		
	arg_type:	T_INT		 {  }
		;

	var_list:	VAR 		 { }
		|	VAR ',' var_list { 	}
		;
		
	Fdef_sec:	
		|	Fdef_sec Fdef
		;
		
	Fdef	:	func_ret_type func_name '(' FargList ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}'	{	 				}
		;
		
	func_ret_type:	T_INT		{ }
		;
			
	func_name:	VAR		{ 					}
		;
		
	FargList:	arg_list	{ 					}
		;

	ret_stmt:	RETURN expr ';'	{ 					}
		;
			
	MainBlock: 	func_ret_type main '('')''{' Ldecl_sec BEG stmt_list ret_stmt END  '}'		{ 				  	  }
		|		stmt_list 
		;
		
	main	:	MAIN		{ 					}
		;
		
	Ldecl_sec:	DECL Ldecl_list ENDDECL	{}
		;

	Ldecl_list:		
		|	Ldecl Ldecl_list
		;

	Ldecl	:	type Lid_list ';'		
		;

	type	:	T_INT			{ }
		;

	Lid_list:	Lid
		|	Lid ',' Lid_list
		;
		
	Lid	:	VAR			{ 						}
		;

	stmt_list:	/* NULL */		{ }
		|	statement stmt_list	{}
		|	error ';' 		{}
		;

	statement:	assign_stmt  ';'		{print_tree($1); nxlin();}
		|	read_stmt ';'		{print_tree($1); nxlin();}
		|	write_stmt ';'		{print_tree($1); nxlin();}
		|	cond_stmt 		{ }
		|	func_stmt ';'		{ }
		;

	read_stmt:	READ '(' var_expr ')' {$$ = create_node(tokenId, 0, 0, "READ", NULL, $3);}
		;

	write_stmt:	WRITE '(' expr ')' 	{$$ = create_node(tokenId, 0, 0, "WRITE", NULL, $3); printf("%d\n", $3->val);}
		|		WRITE '(''"' str_expr '"'')'      {$$ = create_node(tokenId, 0, 0, "WRITE", NULL, $4);}

		;
	
	assign_stmt:	var_expr '=' expr 	{$$ = create_node(tokenId, 0, "=", "ASN", $1, $3); update($1->var, $3->val);}
		;

	cond_stmt:	IF expr THEN stmt_list ENDIF 	{ 						}
		|	IF expr THEN stmt_list ELSE stmt_list ENDIF 	{ 						}
	        |    FOR '(' assign_stmt  ';'  expr ';'  assign_stmt ')' '{' stmt_list '}'                                             {                                                 }
		;
	
	func_stmt:	func_call 		{ 						}
		;
		
	func_call:	VAR '(' param_list ')'	{ 						   }
		;
		
	param_list:				
		|	param_list1		
		;
		
	param_list1:	para			
		|	para ',' param_list1	
		;

	para	:	expr			{ 						}
		;

	expr	:	NUM 			{$$ = create_node(tokenVal, $1, 0, "", NULL, NULL);}
		|	'-' NUM			{$$ = create_node(tokenVal, -1 * $2, 0, "", NULL, NULL);}
		|	var_expr		{$$ = create_node(tokenVal, $1->val, 0, "", NULL, NULL);}
		|	T			{ 						  	}
		|	F			{ 	}
		|	'(' expr ')'		{$$ = create_node(tokenVal, $2->val, 0, "", NULL, NULL);}

		|	expr '+' expr 		{$$ = create_node(tokenOp, $1->val + $3->val, "+", "ADD", $1, $3);}
		|	expr '-' expr	 	{$$ = create_node(tokenOp, $1->val - $3->val, "-", "SUB", $1, $3);}
		|	expr '*' expr 		{$$ = create_node(tokenOp, $1->val * $3->val, "*", "MUL", $1, $3);}
		|	expr '/' expr 		{if ($3->val != 0){$$ = create_node(tokenOp, $1->val / $3->val, "/", "DIV", $1, $3);}else{fprintf(stderr, "Division With Zero.!\n");}}
		|	expr '%' expr 		{if ($3->val != 0){$$ = create_node(tokenOp, $1->val % $3->val, "%", "REM", $1, $3);}else{fprintf(stderr, "Cannot Calculate Remainder when divisor is '0'\n");}}
		|	expr '<' expr		{ 						}
		|	expr '>' expr		{ 						}
		|	expr GREATERTHANOREQUAL expr				{ 						}
		|	expr LESSTHANOREQUAL expr	{  						}
		|	expr NOTEQUAL expr			{ 						}
		|	expr EQUALEQUAL expr	{ 						}
		|	LOGICAL_NOT expr	{ 						}
		|	expr LOGICAL_AND expr	{ 						}
		|	expr LOGICAL_OR expr	{ 						}
		|	func_call		{  }

		;
	str_expr :  VAR        {}
        |	str_expr VAR   { }
        ;
	
	var_expr:	VAR {$$ = create_node(tokenVar, search($1)->value, 0, $1, NULL, NULL);}
		|	var_expr '[' expr ']'	{                                                 }
		;
%%

void yyerror ( char  *s) 
{
   fprintf (stderr, "%s\n", s);
}

int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1], "r");
	if(!fp){
		fprintf(stderr, "File Fetching Failed\n");
		exit(EXIT_FAILURE);
	}
	yyin = fp;

	yyparse();

	fclose(fp);

	printTable();
	freeTable();
	return 0;
}
