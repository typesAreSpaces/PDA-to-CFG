%{
#include <cstdio>
#include <iostream>
#include <string>
#include "parser.tab.h"
%}
%option noyywrap
%%
[ \t\n]   ;
[a-zA-Z0-9$_]+ { yylval.StringType = strdup(yytext); return ID; }
,         { return COMMA; }
->        { return ARROW; }
;         { return SEMICOLON; }
\|        { return BAR; }
.         ;
%%
