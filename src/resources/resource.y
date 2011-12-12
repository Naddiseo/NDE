%{
#include <iostream>
#include <cstdarg>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "resources/ResourceReader.hpp"
#include "resources/Face.hpp"

using namespace nde;
void yyerror(const char* s, ...) {
	std::cerr << s << std::endl;
}
extern "C" int yylex(void);

static faces_t faces = faces_t();

nde::Face* currentFace;

faces_t& get_faces() { return faces; }
%}



%error-verbose
%locations

%union {
	long ival;
	float fval;
	char* ident;
	
	nde::Face* face;
	Vector3f* vec;
	Vector2f* point;
}


%token <ival> INT
%token <ident> IDENT STRING
%token <fval> FLOAT

%token T_FACE T_VERTEX T_TEX T_TEXNAME NL

%type <vec> vertex
%type <point> tex
%type <face> dfn_stmt stmt_list stmt
%type <ident> texname

%destructor { free($$); } IDENT

%%

program
	: dfn_list 
	|
	;

dfn_list
	: dfn_list dfn_stmt
	| dfn_stmt nl_list
	;

dfn_stmt
	: T_FACE 
		{ currentFace = new Face(); } 
		'{' opt_nl stmt_list opt_nl '}'  {
		currentFace->setEnum();
		faces.push_back(currentFace);
	} 
	;


stmt_list
	: stmt stmt_list
	| stmt
	;

stmt
	: vertex { currentFace->vertexes.push_back($1); }
	| tex { currentFace->tex_points.push_back($1); }
	| texname {
		size_t len = strlen($1);
		char* str = $1;
		str[len-1] = 0;
		str++;
		std::cout << "loading texture file '" << str << "'" << std::endl;
		//TODO
	}
	;

vertex
	: T_VERTEX FLOAT FLOAT FLOAT NL {
		$$ = new Vector3f($2, $3, $4);
	}
	; 

tex
	: T_TEX FLOAT FLOAT NL {
		$$ = new Vector2f($2, $3);
	}
	;

texname
	: T_TEXNAME STRING NL {
		$$ = $2;
	}

nl_list
	: nl_list NL
	| NL
	;

opt_nl
	: NL
	|
	;