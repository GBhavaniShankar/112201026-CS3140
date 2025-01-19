%{
#include <stdio.h>
#include <stdlib.h>

int storage[26];  // Array for variables (A-Z)

void yyerror(const char *msg);
int yylex();
%}

%token DIGIT ALPHA
%left '+' '-'
%left '*' '/'

%%

stuff:
    stuff thing '\n'
    | thing '\n'
    ;

thing:
    ALPHA '=' math { storage[$1 - 'A'] = $3; printf("%d\n", $3); }
    | math         { printf("%d\n", $1); }
    ;

math:
    DIGIT         { $$ = $1; }
    | ALPHA       { $$ = storage[$1 - 'A']; }
    | math '+' math { $$ = $1 + $3; }
    | math '-' math { $$ = $1 - $3; }
    | math '*' math { $$ = $1 * $3; }
    | math '/' math { 
        if ($3 == 0) {
            yyerror("Uh oh! Can't divide by zero!");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    ;

%%

int main() {
    printf("Alright, throw some math at me:\n");
    yyparse();
    return 0;
}

void yyerror(const char *msg) {
    printf("Error: %s\n", msg);
}
