%{
#include <sstream>
#include <cstring>
#include "ASTree.hpp"
#include "parser.tab.h"
static std::stringstream ss;
class LexerError;

%}

%option noyywrap
%option yylineno

%%

[\r\n\t ]  { /* ignore whitespace */ }

int      { return INT; }
uint     { return UINT; }
float    { return FLOAT; }
string   { return STRING; }
vector   { return VECTOR; }
bool     { return BOOL; }
void     { return VOID; }

if       { return IF; }
while    { return WHILE; }
for      { return FOR; }
break    { return BREAK; }
continue { return CONTINUE; }
else     { return ELSE; }
class    { return CLASS; }
return   { return RETURN; }
event    { return EVENT; }
trigger  { return TRIGGER; }

or       { return OR; }
and      { return AND; }

true|false   { 
	yylval.boolval = (yytext[0] == 't');
	return BOOLVAL; 
}

[a-zA-Z_][a-zA-Z0-9_] { 
	yylval.stringval = strdup(yytext);
	return IDENT;
}

-?[0-9]+\.[0-9]+ {
	ss << yytext;
	ss >> yylval.floatval;
	return FLOATVAL; 
}

-?[0-9]+ {
	ss << yytext;
	ss >> yylval.intval;
	return INTVAL;
}

==  { return EQUAL; }
=   { return ASSIGN; }
!=  { return NEQUAL; }
\<\<= { return LSHIFTASSIGN; }
\>\>= { return RSHIFTASSIGN; }
\<=  { return LTE; }
\>=  { return GTE; }
\<\<  { return LSHIFT; }
\>\>  { return RSHIFT; }
\<   { return LT; }
\>   { return GT; }

\|= { return BORASSIGN; }
&=  { return BANDASSIGN; }
\^=  { return BXORASSIGN; }
\+= { return ADDASSIGN; }
\-= { return SUBASSIGN; }
\*= { return MULASSIGN; }
\/= { return DIVASSIGN; }
\%= { return MODASSIGN; }

\+\+ { return INC; }
\-\- { return DEC; }

\|\| { return OR; }
&&   { return AND; }



[;\(\)\{\}\[\],\.\:\?\|&~^!\+\-\*\/%] { return yytext[0]; }

. {
	//throw LexerError();
	
}

%%