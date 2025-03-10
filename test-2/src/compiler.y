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
	#include "compiler.h"

	int yylex();
	void yyerror(char* s);
    int i;
	extern FILE* yyin;
	extern DeclScope *global_decls;
	extern Symbol *symbol_table[TABLE_SIZE];
	bool is_true = true;
	Statement *stmts = NULL;
%}

%union {
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
}

%token <id> BEG END
%token <id> T_INT T_BOOL T_FLOAT
%token <id> READ WRITE
%token <id> DECL ENDDECL
%token <fval> FLOAT
%token <var> VAR 
%token <val> NUM
%token <id> IF THEN ELSE ENDIF
%token <op> LOGICAL_AND LOGICAL_NOT LOGICAL_OR
%token <op> EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%token <id> WHILE DO ENDWHILE FOR 
%token <id> STRING BREAK
%token T F 
%token <type> MAIN RETURN

%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT

%type <node> Prog Gdecl_sec func arg_list arg_list1
%type <var_data> Glist Gid var_list
%type <stmts> MainBlock stmt_list statement read_stmt write_stmt assign_stmt cond_stmt func_stmt break_stmt
%type <node> func_call param_list param_list1 para expr var_expr
%type <decl_scope> Gdecl_list Gdecl
%type <type> ret_type arg_type type func_ret_type main
%type <var> func_name
%%

Prog:
	  Gdecl_sec Fdef_sec MainBlock
	;

Gdecl_sec:
	  DECL { initialize_global(); init_symbol_table(); } Gdecl_list ENDDECL { print_decls(); free_decls(); }
	;

Gdecl_list:
	    /* empty */
	|   Gdecl Gdecl_list
	;

Gdecl:
	    ret_type Glist ';' {add_symbols($1, $2);}
	;

ret_type:
	    T_INT { $$ = SYMBOL_INT;}
	|   T_BOOL { $$ = SYMBOL_BOOL;}
	|   T_FLOAT  { $$ = SYMBOL_FLOAT; }
	;

Glist:
	    Gid {$$ = $1;}
	|   Gid ',' Glist { $1->next = $3; $$ = $1;}
	;

Gid:
	   VAR '[' NUM ']' { $$ = add_arr($1, $3); }
	|  VAR '[' NUM ']''[' NUM ']'{ $$ = add_2d_arr($1, $3, $6); }
	|    VAR { $$ = add_var($1);}
	;

func:
	    VAR '(' arg_list ')'
	;
			
arg_list:
	    /* empty */
	|   arg_list1
	;
		
arg_list1:
	    arg_list1 ';' arg
	|   arg
	;
		
arg:
	    arg_type var_list
	;
		
arg_type:
	    T_INT
	;

var_list:
	    VAR
	|   VAR ',' var_list
	;
		
Fdef_sec:
	    /* empty */
	|   Fdef_sec Fdef
	;
		
Fdef:
	    func_ret_type func_name '(' FargList ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}'	
	;
		
func_ret_type:
	    T_INT
	;
			
func_name:
	    VAR
	;
		
FargList:
	    arg_list
	;

ret_stmt:
	    RETURN expr ';'
	;
			
MainBlock:
	    func_ret_type main '(' ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}'		
	|   BEG stmt_list END { stmts = $2; }
	;
		
main:
	    MAIN
	;
		
Ldecl_sec:
	    DECL Ldecl_list ENDDECL
	;

Ldecl_list:
	    /* empty */
	|   Ldecl Ldecl_list
	;

Ldecl:
	    type Lid_list ';'
	;

type:
	    T_INT
	;

Lid_list:
	    Lid
	|   Lid ',' Lid_list
	;
		
Lid:
	    VAR
	;

stmt_list:
	    /* empty */ { $$ = NULL; }
	|   statement stmt_list { $$ = $1; $1->next = $2; }
	|   error ';'
	;

statement:
		assign_stmt ';'          { $$ = $1; }
	| read_stmt ';'            {}
	| write_stmt ';'           { $$ = $1; }
	| cond_stmt                { $$ = $1; }
	| func_stmt ';'            {}
	| break_stmt ';'           { $$ = $1; }
	;
  
break_stmt:
    BREAK                    { $$ = create_break_stmt(); }
  ;

read_stmt:
	    READ '(' var_expr ')'
	;

write_stmt:
	    WRITE '(' expr ')' { $$ = create_write_stmt($3); }
	|	WRITE '(' STRING ')' { $$ = create_write_stmt_string($3); }
	;
	
assign_stmt:
	    var_expr '=' expr { $$ = create_assign_stmt($1, $3); }
	;

cond_stmt:
	    IF expr THEN stmt_list ENDIF {$$ = create_if_stmt($2, $4, NULL); }
	|   IF expr THEN stmt_list ELSE stmt_list ENDIF {$$ = create_if_stmt($2, $4, $6); }
	|   FOR '(' assign_stmt ';' expr ';' assign_stmt ')' '{' stmt_list '}' {$$ = create_for_stmt($3, $5, $7, $10);}
	|   DO '{' stmt_list '}' WHILE '(' expr')'';' {$$ = create_do_while_stmt($3, $7);}
	;
	
func_stmt:
	    func_call
	;
		
func_call:
	    VAR '(' param_list ')'
	;
		
param_list:
	    /* empty */
	|   param_list1
	;
		
param_list1:
	    para
	|   para ',' param_list1
	;

para:
	    expr
	;

expr:			{$$ = NULL;}
	|   FLOAT {$$ = create_float_node($1); }
	| 	'-' FLOAT { $$ = create_float_node($2);}
	|    NUM { $$ = create_num_node($1); }
	|   '-' NUM { $$ = create_num_node(-1 * $2); }
	|   var_expr { $$ = $1; }
	|   T { $$ = create_bool_node(true); }
	|   F { $$ = create_bool_node(false); }
	|   '(' expr ')' { $$ = $2; }
	|   expr '+' expr { $$ = create_expr_node(TOKEN_ADD, $1, $3); }
	|   expr '-' expr { $$ = create_expr_node(TOKEN_SUB, $1, $3); }
	|   expr '*' expr { $$ = create_expr_node(TOKEN_MUL, $1, $3); }
	|   expr '/' expr { $$ = create_expr_node(TOKEN_DIV, $1, $3); }
	|   expr '%' expr { $$ = create_expr_node(TOKEN_MOD, $1, $3); }
	|   expr '<' expr { $$ = create_expr_node(TOKEN_LT, $1, $3); }
	|   expr '>' expr { $$ = create_expr_node(TOKEN_GT, $1, $3); }
	|   expr GREATERTHANOREQUAL expr { $$ = create_expr_node(TOKEN_GE, $1, $3); }
	|   expr LESSTHANOREQUAL expr { $$ = create_expr_node(TOKEN_LE, $1, $3); }
	|   expr NOTEQUAL expr { $$ = create_expr_node(TOKEN_NE, $1, $3); }
	|   expr EQUALEQUAL expr { $$ = create_expr_node(TOKEN_EQ, $1, $3); }
	|   LOGICAL_NOT expr { $$ = create_expr_node(TOKEN_NOT, NULL, $2); }
	|   expr LOGICAL_AND expr { $$ = create_expr_node(TOKEN_AND, $1, $3); }
	|   expr LOGICAL_OR expr { $$ = create_expr_node(TOKEN_OR, $1, $3); }
	|   func_call
	;
	
var_expr:
		VAR '[' expr ']' { $$ = create_array_node($1, $3); }
	|   VAR '[' expr ']' '[' expr ']' {$$ = create_2d_array_node($1, $3, $6);}
    |   VAR { $$ = create_var_node($1); }   
	;

%%

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
