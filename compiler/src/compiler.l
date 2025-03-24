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
    #include "y.tab.h"
    extern YYSTYPE yylval;
    int  Lineno = 1;
    int  wflag;
%}

%option noyywrap

digit	[0-9]
letter	[a-zA-Z]
string  \"[^\"]*\"

%%

main         { return MAIN; }
return       { return RETURN; }
read         { return READ; }
write        { return WRITE; }
integer      { return T_INT; }
boolean      { return T_BOOL; }
begindecl    { return DECL; }
decl         { return DECL; }
begin        { return BEG; }
enddecl      { return ENDDECL; }
end          { return END; }
if           { return IF; }
then         { return THEN; }
else         { return ELSE; }
endif        { return ENDIF; }
do           { return DO; }
while        { return WHILE; }
endwhile     { return ENDWHILE; }
for          { return FOR; }
break        { return BREAK; }

"=="         { return EQUALEQUAL; }
"<="         { return LESSTHANOREQUAL; }
">="         { return GREATERTHANOREQUAL; }
"!="         { return NOTEQUAL; }

AND          { return LOGICAL_AND; }
OR           { return LOGICAL_OR; }
NOT          { return LOGICAL_NOT; }
true         { return T; }
false        { return F; }
{digit}+     { yylval.val = atoi(yytext); return NUM; }
{letter}({letter}|{digit})*   { yylval.var = strdup(yytext); return VAR; }

{string}     { 
                yylval.var = strdup(yytext + 1);
                yylval.var[strlen(yylval.var) - 1] = '\0';
                return STRING; 
             }

[-+*/=()><;,\{\}\[\]\%] { return yytext[0]; }

[ \t]        { /* Ignore spaces and tabs */ }
\n           { Lineno++; }

.            { return yytext[0]; }

%%
