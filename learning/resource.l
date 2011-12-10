%{
#include <iostream>
#include <cstring>
#include <cstdio>
#include "ResourceReader.hpp"
#include "resource.tab.h"

/* handle locations */
int yycolumn = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

extern "C" int yylex(void);

#if defined(WINDOWS) || !defined(strdup)
char* strdup(char* str) {
	char* newstr = new char[strlen(str)];
	strcpy(newstr, str);
	return newstr;
}
#endif

 void yyerror(const char* s, ...);

%}

%option noyywrap
%option yylineno

%%

#.*\n { /* ignore comments*/ return NL; }
vertex { return T_VERTEX; }
face { return T_FACE; }
tex { return T_TEX; }
texname { return T_TEXNAME; }

-?[0-9]+(\.[0-9]+)? { yylval.fval = atof(yytext); return FLOAT; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.ident = strdup(yytext); return IDENT; }

\"[^\"]+\" { yylval.ident = strdup(yytext); return STRING; }

[ \t]+ { /* ignore */}
[\n]+ { yycolumn = 1; return NL; }

[\{\}] { return yytext[0]; }

. { std::cerr << "Unknown char '" << yytext << "'" << std::endl; }

<<EOF>> { return 0; }
%%

