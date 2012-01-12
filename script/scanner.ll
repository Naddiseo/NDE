%{
#include <cstring>
#include <sstream>
#include "Script.hpp"
#include "Driver.hpp"
#include "Parser.hpp"

typedef NDESCRIPT_NS Parser::token token;
typedef NDESCRIPT_NS Parser::token_type token_type;

#define yyterminate() return token::END

#define YY_NO_UNISTD_H

%}
%option c++ 
%option nounput debug yylineno stack batch
%option prefix="NDE"
/*%option yyclass="Scanner"*/

%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
static std::stringstream ss;
%}

%%

%{
	yylloc->step();
%}

[\r\t ]+  { /* ignore whitespace */ yylloc->step(); }
[\n] { yylloc->lines(yyleng); yylloc->step(); }

int      { return token::INT; }
uint     { return token::UINT; }
float    { return token::FLOAT; }
string   { return token::STRING; }
vector   { return token::VECTOR; }
bool     { return token::BOOL; }
void     { return token::VOID; }

if       { return token::IF; }
while    { return token::WHILE; }
for      { return token::FOR; }
break    { return token::BREAK; }
continue { return token::CONTINUE; }
else     { return token::ELSE; }
class    { return token::CLASS; }
return   { return token::RETURN; }
event    { return token::EVENT; }
trigger  { return token::TRIGGER; }

or       { return token::OR; }
and      { return token::AND; }

(true)|(false)   { 
	yylval->boolval = (yytext[0] == 't');
	return token::BOOLVAL; 
}

\"[^\"]*\" {
	//yytext[yyleng] = 0;
	//yytext++;
	yylval->stringval = strdup(yytext);
	return token::STRINGVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* { 
	yylval->stringval = strdup(yytext);
	return token::IDENT;
}

-?[0-9]+\.[0-9]+ {
	ss << yytext << " ";
	ss >> yylval->floatval;
	return token::FLOATVAL; 
}

-?[0-9]+ {
	ss << yytext << " ";
	ss >> yylval->intval;
	return token::INTVAL;
}

==  { return token::EQUAL; }
=   { return token::ASSIGN; }
!=  { return token::NEQUAL; }
\<\<= { return token::LSHIFTASSIGN; }
\>\>= { return token::RSHIFTASSIGN; }
\<=  { return token::LTE; }
\>=  { return token::GTE; }
\<\<  { return token::LSHIFT; }
\>\>  { return token::RSHIFT; }
\<   { return token::LT; }
\>   { return token::GT; }

\|= { return token::BORASSIGN; }
&=  { return token::BANDASSIGN; }
\^=  { return token::BXORASSIGN; }
\+= { return token::ADDASSIGN; }
\-= { return token::SUBASSIGN; }
\*= { return token::MULASSIGN; }
\/= { return token::DIVASSIGN; }
\%= { return token::MODASSIGN; }

\+\+ { return token::INC; }
\-\- { return token::DEC; }

\|\| { return token::OR; }
&&   { return token::AND; }



[;\(\)\{\}\[\],\.\:\?\|&~^!\+\-\*\/%] { return static_cast<token_type>(yytext[0]); }

. {
	driver.error(std::string("Unexpected character '") + yytext[0] + "'");
	
}

%%

NDESCRIPT_NS_BEGIN

Scanner::Scanner(FLEX_STD istream* in, FLEX_STD ostream* out)
	: NDEFlexLexer(in, out) {}


Scanner::~Scanner() {}

void Scanner::set_debug(bool b) { yy_flex_debug = b; }

#ifdef yylex
#	undef yylex
#endif

NDESCRIPT_NS_END

int 
yyFlexLexer::yylex() {
	// shouldn't get here
	std::cerr << "in yyFlexLexer::yylex()!" << std::endl;
	return 0;
}

int 
NDEFlexLexer::yywrap() {
	return 1;
}