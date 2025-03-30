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
    extern int Lineno;
    extern Statement *global_stmts;
    extern Symbol *symbol_table[TABLE_SIZE];

    #define MAX_LINE 1024

    void process_line(char *line, FILE *output) {
        char *start = strstr(line, "write(");
        if (!start) {
            fprintf(output, "%s", line);
            return;
        }
        char before[MAX_LINE];
        char args[MAX_LINE];
        char *end = strchr(start, ')');
        if (!end) {
            fprintf(output, "%s", line);
            return;
        }
        *end = '\0';
        strncpy(before, line, start - line);
        before[start - line] = '\0';
        strcpy(args, start + 6);
        char *token = strtok(args, ",");
        while (token) {
            fprintf(output, "%swrite(%s);\n", before, token);
            token = strtok(NULL, ",");
        }
    }

    FILE *process_file_temp(const char *filename) {
        FILE *input = fopen(filename, "r");
        if (!input) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        FILE *temp = fopen("temp.txt", "w");
        if (!temp) {
            perror("Error creating temp file");
            fclose(input);
            exit(EXIT_FAILURE);
        }
        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, input)) {
            process_line(line, temp);
        }
        fclose(input);
        fclose(temp);
        temp = fopen("temp.txt", "r");
        if (!temp) {
            perror("Error opening temp file for reading");
            exit(EXIT_FAILURE);
        }
        return temp;
    }
%}

%union {
    int val;
    char *var;
    char *id;
    Node *node;
    Statement *stmts;
    SymbolType type;
}

%type <node> func arg_list arg_list1 Gid var_list func_call param_list param_list1 para expr var_expr
%type <stmts> Prog Gdecl_sec MainBlock Glist stmt_list statement read_stmt write_stmt assign_stmt cond_stmt func_stmt break_stmt Gdecl_list Gdecl
%type <type> ret_type arg_type type func_ret_type main
%type <var> func_name

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
%token <id> STRING BREAK
%token T F 
%token <id> MAIN RETURN

%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT

%%

Prog:
      Gdecl_sec Fdef_sec MainBlock {
          global_stmts = merge_ast_segments($1, NULL, $3);
      }
;

Gdecl_sec:
      DECL Gdecl_list ENDDECL { $$ = $2; }
;

Gdecl_list:
      { $$ = NULL; }
    | Gdecl Gdecl_list {
          $1->next = $2;
          $$ = $1;
      }
;

Gdecl:
      ret_type Glist ';' {
          $$ = create_decl_stmt($1, $2);
      }
;

ret_type:
      T_INT       { $$ = SYMBOL_INT; }
      | T_BOOL {}
;

Glist:
      Gid { $$ = $1; }
    | Gid ',' Glist {
          $1->data.decl.next = $3;
          $$ = $1;
      }
;

Gid:
      VAR '[' NUM ']' {
          $$ = create_arr_decl_node($1, $3);
      }
    | VAR {
          $$ = create_var_decl_node($1);
      }
;

func:
      VAR '(' arg_list ')' {}
;

arg_list:
      /* empty */ {}
    | arg_list1 {}
;

arg_list1:
      arg_list1 ';' arg { }
    | arg { }
;

arg:
      arg_type var_list {}
;

arg_type:
      T_INT { }
;

var_list:
      VAR { }
    | VAR ',' var_list { }
;

Fdef_sec:
      /* empty */
    | Fdef_sec Fdef { }
;

Fdef:
      func_ret_type func_name '(' FargList ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}' {}
;

func_ret_type:
      T_INT {}
;

func_name:
      VAR {}
;

FargList:
      arg_list { }
;

ret_stmt:
      RETURN expr ';' {
          /* Handle return as needed; ignore for now */
      }
;

MainBlock:
      func_ret_type main '(' ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}' {
          $$ = $8;
      }
    | BEG stmt_list END {
          $$ = $2;
      }
;

main:
      MAIN { }
;

Ldecl_sec:
      DECL Ldecl_list ENDDECL { }
;

Ldecl_list:
      /* empty */
    | Ldecl Ldecl_list { }
;

Ldecl:
      type Lid_list ';'
;

type:
      T_INT {}
;

Lid_list:
      Lid { }
    | Lid ',' Lid_list { }
;

Lid:
      VAR { }
;

stmt_list:
      /* empty */ { $$ = NULL; }
    | statement stmt_list {
          $1->next = $2;
          $$ = $1;
      }
    | error ';' { $$ = NULL; }
;

statement:
      assign_stmt ';' { $$ = $1; }
    | read_stmt ';' { }
    | write_stmt ';' { $$ = $1; }
    | cond_stmt { $$ = $1; }
    | func_stmt ';' { }
    | break_stmt ';' { $$ = $1; }
;

break_stmt:
      BREAK { $$ = create_break_stmt(); }
;

read_stmt:
      READ '(' var_expr ')' { $$ = NULL; }
;

write_stmt:
      WRITE '(' expr ')' { $$ = create_write_stmt(false, $3, ""); }
    | WRITE '(' STRING ')' { $$ = create_write_stmt(true, NULL, $3); }
;

assign_stmt:
       var_expr '=' expr {$$ = create_assign_stmt($1, $3);}
      | {$$ = NULL; }
;

cond_stmt:
      IF expr THEN stmt_list ENDIF { $$ = create_if_stmt($2, $4, NULL); }
    | IF expr THEN stmt_list ELSE stmt_list ENDIF { $$ = create_if_stmt($2, $4, $6); }
    | FOR '(' assign_stmt ';' expr ';' assign_stmt ')' '{' stmt_list '}' {
          $$ = create_for_stmt($3, $5, $7, $10);
      }
;

func_stmt:
      func_call { }
;

func_call:
      VAR '(' param_list ')' { }
;

param_list:
      /* empty */ {}
    | param_list1 {}
;

param_list1:
      para { }
    | para ',' param_list1 { }
;

para:
      expr { }
;

expr:
      /* empty */ { $$ = NULL; }
    | NUM { $$ = create_num_node($1); }
    | '-' NUM { $$ = create_num_node(-1 * $2); }
    | var_expr { $$ = $1; }
    | T { $$ = create_bool_node(true); }
    | F { $$ = create_bool_node(false); }
    | '(' expr ')' { $$ = $2; }
    | expr '+' expr { $$ = create_expr_node(OP_ADD, $1, $3); }
    | expr '-' expr { $$ = create_expr_node(OP_SUB, $1, $3); }
    | expr '*' expr { $$ = create_expr_node(OP_MUL, $1, $3); }
    | expr '/' expr { $$ = create_expr_node(OP_DIV, $1, $3); }
    | expr '%' expr { $$ = create_expr_node(OP_MOD, $1, $3); }
    | expr '<' expr { $$ = create_expr_node(OP_LT, $1, $3); }
    | expr '>' expr { $$ = create_expr_node(OP_GT, $1, $3); }
    | expr GREATERTHANOREQUAL expr { $$ = create_expr_node(OP_GE, $1, $3); }
    | expr LESSTHANOREQUAL expr { $$ = create_expr_node(OP_LE, $1, $3); }
    | expr NOTEQUAL expr { $$ = create_expr_node(OP_NE, $1, $3); }
    | expr EQUALEQUAL expr { $$ = create_expr_node(OP_EQ, $1, $3); }
    | LOGICAL_NOT expr { $$ = create_expr_node(OP_NEG, NULL, $2); }
    | expr LOGICAL_AND expr { $$ = create_expr_node(OP_AND, $1, $3); }
    | expr LOGICAL_OR expr { $$ = create_expr_node(OP_OR, $1, $3); }
    | func_call { }
;

var_expr:
      VAR '[' expr ']' { $$ = create_array_node($1, $3); }
    | VAR { $$ = create_var_node($1); }
;

%%

void yyerror(char* s) {
    fprintf(stderr, "Error at line %d: %s\n", Lineno, s);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* fp = process_file_temp(argv[1]);
        yyin = fp;
    } else {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    yyparse();

    eval_stmts(global_stmts);

    print_ast();
    free_statements();

    print_symbol_table();
    free_symbol_table();
    
    fclose(yyin);
    remove("temp.txt");
    
    return 0;
}
