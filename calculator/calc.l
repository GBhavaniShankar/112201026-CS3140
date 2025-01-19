%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern int yylval;
%}

%%

[A-Z]      { yylval = yytext[0]; return ALPHA; }
[0-9]+     { yylval = atoi(yytext); return DIGIT; }
[+\-*/=]   { return yytext[0]; }
[ \t\r]+   { /* ignore spaces, who cares? */ }
\n         { return '\n'; }
.          { printf("Uh-oh! What is this: %s?\n", yytext); }

%%

int yywrap() { return 1; }