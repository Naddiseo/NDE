%skeleton "lalr1.cc"
%require "2.3"
%defines
%define "parser_class_name" "Parser"
%name-prefix="nde::script"

/*%define "namespace" "nde::script"*/

%code requires {
#include "ASTree.hpp"
}

%{
#include "ASTree.hpp"
class Driver;
%}

%parse-param { class Driver& driver }
%lex-param { class Driver& driver }

%locations
%initial-action {
	@$.begin.filename = @$.end.filename = &driver.streamname;
};

%debug
%error-verbose

%union {
	char* stringval;
	int	 intval;
	bool	boolval;
	float floatval;
	float* vectorval;
	
	ast::ASTNode* node;
}


%{
#include "ASTree.hpp"
#include "Driver.hpp"
%}

%token END 0 "end of file"

%token <stringval> IDENT STRINGVAL;
%token <intval> INTVAL;
%token <boolval> BOOLVAL;
%token <floatval> FLOATVAL;
%token <vectorval> VECTORVAL;


/* type names */
%token INT UINT FLOAT STRING VECTOR BOOL VOID

/* keywords */
%token IF ELIF ELSE WHILE FOR BREAK CONTINUE CLASS RETURN EVENT TRIGGER OR AND

/* assign */
%token ASSIGN LSHIFTASSIGN RSHIFTASSIGN BORASSIGN BANDASSIGN 
%token BXORASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN

/* Comparisons */
%token EQUAL NEQUAL LTE GTE LT GT

/* OTHER */
%token LSHIFT RSHIFT INC DEC

%type <stringval> optional_inherits
%type <boolval> optional_is_array

%type <node> var_type 

%type <node> optional_var_assign expr unary_expr primary_expr atom attribute subscript function_call literal

//StmtNode*
%type <node> statement loop_control_stmt declaration function_decl var_decl_stmt 
%type <node> var_decl class_decl if_stmt optional_else_if_list else_if_list else_if 
%type <node> while_stmt for_stmt  optional_expr_stmt expr_stmt return_stmt trigger_call code_block optional_else

//expr_list_t*
%type <node> optional_expr_list expr_list

//stmt_list_t*
%type <node> optional_statements statements

//declarations_t*
%type <node> declarations

//vardecls_t*
%type <node> optional_argument_list argument_list

%destructor { free($$); } <stringval> IDENT STRINGVAL;

%left ','
%right ASSIGN BORASSIGN BANDASSIGN BXORASSIGN LSHIFTASSIGN RSHIFTASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN
%right '?' ':'
%left OR
%left AND
%left '|'
%left '^'
%left '&'
%left NEQUAL EQUAL
%left LT GT LTE GTE
%left LSHIFT RSHIFT
%left '+' '-'
%left '*' '/' '%'
%right '~' '!' UNARY
%left '.'
%left '[' ']'
%left '(' ')'


%start program
%%

program
	: declarations {
		driver.declarations = $1;
	} 
	| /* empty*/ { YYACCEPT; }
	;

declarations
	: declarations declaration {
		$1->push_back($2);
		$$ = $1;
	}
	| declaration {
		declarations_t* d = new declarations_t();
		d->push_back($1);
		$$ = d;
	}
	;

declaration
	: function_decl
	| var_decl_stmt
	| class_decl 
	;

class_decl
	: CLASS IDENT optional_inherits '{' declarations '}' {
		ClassDecl* c = new ClassDecl();
		c->name = $2;
		c->parent = $3;
		c->declarations = $5;
		$$ = c;
	}
	;

optional_inherits
	: ':' IDENT { $$ = $2; }
	| { $$ = const_cast<char*>(""); }
	;

function_decl
	: var_type IDENT '(' optional_argument_list ')' code_block {
		FunctionDecl* f = new FunctionDecl();
		f->name = $2;
		f->is_event = false;
		f->arguments = $4;
		f->block = $6;
		$$ = f;
	}
	| EVENT var_type IDENT '(' optional_argument_list ')' code_block {
		FunctionDecl* f = new FunctionDecl();
		f->name = $3;
		f->is_event = true;
		f->arguments = $5;
		f->block = $7;
		$$ = f;
	}
	;

optional_argument_list
	: argument_list
	| { $$ = NULL; }
	;

argument_list
	: argument_list ',' var_decl {
		$1->push_back($3);
		$$ = $1;
	}
	| var_decl {
		$$ = new vardecls_t();
		$$->push_back($1);
	}
	;

code_block
	: '{' optional_statements '}' { $$ = $2; }
	;

optional_statements
	: statements
	| { $$ = NULL; }
	;

statements
	: statements statement {
		$1->push_back($2);
		$$ = $1;
	}
	| statement {
		$$ = new stmt_list_t();
		$$->push_back($1);
	}
	;

statement
	: var_decl_stmt
	| if_stmt
	| while_stmt
	| for_stmt
	| return_stmt
	| expr_stmt
	| trigger_call
	| loop_control_stmt
	;

if_stmt
	: IF expr code_block optional_else_if_list {
		$$ = new IfStmt();
		$$->condition = $2;
		$$->true_block = $3;
		$$->false_block = $4;
	}
	;

optional_else_if_list
	: else_if_list { $$ = $1; }
	| optional_else { $$ = $1; }
	;

else_if_list
	: else_if_list else_if {
		$$ = $1;
		$$->passDown($2);
	}
	| else_if {
		$$ = $1;
	}
	;

else_if
	: ELIF expr code_block optional_else {
		$$ = new IfStmt();
		$$->condition = $2;
		$$->true_block = $3;
		$$->false_block = $4;
	}
	;

optional_else
	: ELSE code_block { $$ = $2; }
	| { $$ = NULL; }
	;

while_stmt
	: WHILE expr code_block {
		$$ = new WhileStmt();
		$$->condition = $2;
		$$->block = $3;
	}
	;

for_stmt
	: FOR expr ';' expr ';' expr code_block {
		$$ = new ForStmt();
		$$->begin = $2;
		$$->condition = $4;
		$$->counter = $6;
		$$->block = $7;
	}
	;

return_stmt
	: RETURN optional_expr_stmt  {
		$$ = new ReturnStmt();
		$$->return_val = $2;
	}
	;

optional_expr_stmt
	: expr_stmt
	| ';' { $$ = new ExprStmt(); }
	;

expr_stmt
	: expr ';' { 
		$$ = new ExprStmt();
		$$->block = $1;
	}
	;

var_decl_stmt
	: var_decl ';' { $$ = $1; }
	;

var_decl
	: var_type IDENT optional_is_array optional_var_assign {
		$$ = new VarDecl();
		$1->is_array = $3;
		$$->type = $1;
		$$->name = $2;
		$$->default_value = $4;
	}
	;

optional_is_array
	: '[' ']' { $$ = true; }
	| { $$ = false; }
	;

trigger_call
	: TRIGGER function_call ';' { // can't be used as a lhs
		$$ = $2;
		$$->is_trigger = true;
	}
	;

loop_control_stmt
	: BREAK ';' { $$ = new BreakStmt(); }
	| CONTINUE ';' { $$ = new ContinueStmt(); }
	;

var_type
	: IDENT { 
		$$ = new VarType(eReturnType::OBJECT);
		$$->class_name = $1; 
	}
	| INT { $$ = new VarType(eReturnType::INT); }
	| UINT { $$ = new VarType(eReturnType::UINT); } 
	| FLOAT { $$ = new VarType(eReturnType::FLOAT); }
	| STRING { $$ = new VarType(eReturnType::STRING); }
	| VECTOR { $$ = new VarType(eReturnType::VECTOR); }
	| BOOL { $$ = new VarType(eReturnType::BOOl); }
	| VOID { $$ = new VarTYpe(eReturnType::VOID); }
	;

optional_var_assign
	: ASSIGN expr { $$ = $2; }
	| { $$ = NULL; }
	;

expr
	: expr ASSIGN  expr { $$ = new BinaryExpr($1, eBinaryOp::ASSIGN, $3); }
	| expr BORASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::BORASSIGN, $3); }
	| expr  BANDASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::BANDASSIGN, $3); }
	| expr BXORASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::BXORASSIGN, $3); }
	| expr  LSHIFTASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::LSHIFTASSIGN, $3); }
	| expr RSHIFTASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::RSHIFTASSIGN, $3); }
	| expr ADDASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::ADDASSIGN, $3); }
	| expr SUBASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::SUBASSIGN, $3); }
	| expr MULASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::MULASSIGN, $3); }
	| expr DIVASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::DIVASSIGN, $3); }
	| expr MODASSIGN expr { $$ = new BinaryExpr($1, eBinaryOp::MODASSIGN, $3); }
	| expr '?' expr ':' expr { $$ = new TernaryExpr($1, $3, $5); }
	| expr OR expr { $$ = new BinaryExpr($1, eBinaryOp::OR, $3); }
	| expr AND expr { $$ = new BinaryExpr($1, eBinaryOp::AND, $3); }
	| expr '|' expr { $$ = new BinaryExpr($1, eBinaryOp::BOR, $3); }
	| expr '^' expr { $$ = new BinaryExpr($1, eBinaryOp::BXOR, $3); }
	| expr '&' expr { $$ = new BinaryExpr($1, eBinaryOp::BAND, $3); }
	| expr EQUAL expr { $$ = new BinaryExpr($1, eBinaryOp::EQUAL, $3); }
	| expr NEQUAL expr { $$ = new BinaryExpr($1, eBinaryOp::NEQUAL, $3); }
	| expr GT expr { $$ = new BinaryExpr($1, eBinaryOp::GT, $3); }
	| expr LT expr { $$ = new BinaryExpr($1, eBinaryOp::LT, $3); }
	| expr GTE expr { $$ = new BinaryExpr($1, eBinaryOp::GTE, $3); }
	| expr LTE expr { $$ = new BinaryExpr($1, eBinaryOp::LTE, $3); }
	| expr LSHIFT expr { $$ = new BinaryExpr($1, eBinaryOp::LSHIFT, $3); }
	| expr RSHIFT expr { $$ = new BinaryExpr($1, eBinaryOp::RSHIFT, $3); }
	| expr '+' expr { $$ = new BinaryExpr($1, eBinaryOp::ADD, $3); }
	| expr '-' expr { $$ = new BinaryExpr($1, eBinaryOp::SUB, $3); }
	| expr '*' expr { $$ = new BinaryExpr($1, eBinaryOp::MUL, $3); }
	| expr '/' expr { $$ = new BinaryExpr($1, eBinaryOp::DIV, $3); }
	| expr '%' expr { $$ = new BinaryExpr($1, eBinaryOp::MOD, $3); }
	| unary_expr
	;

unary_expr
	: '~' unary_expr %prec UNARY { $$ = new UnaryExpr(eUnaryType::BNOT, $2); }
	| '!' unary_expr %prec UNARY { $$ = new UnaryExpr(eUnaryType::NOT, $2); }
	| INC unary_expr %prec UNARY { $$ = new UnaryExpr(eUnaryType::INC, $2); }
	| DEC unary_expr %prec UNARY { $$ = new UnaryExpr(eUnaryType::DEC, $2); }
	| primary_expr
	;



primary_expr
	: atom
	| attribute
	| subscript
	| function_call
	;



atom
	: IDENT { $$ = new IdentNode($1); }
	| literal
	| '(' expr ')' { $$ = $2; }
	;



attribute
	: primary_expr '.' IDENT { $$ = new AttributeNode($1, $3); }
	;



subscript
	: primary_expr '[' expr ']'
	;



function_call
	: primary_expr '(' optional_expr_list ')'
	;


literal
	: STRINGVAL { $$ = new LiteralExpr($1); }
	| INTVAL { $$ = new LiteralExpr($1); }
	| BOOLVAL { $$ = new LiteralExpr($1); }
	| FLOATVAL { $$ = new LiteralExpr($1); }
	| VECTORVAL { $$ = new LiteralExpr($1); }
	;



optional_expr_list
	: expr_list
	| /* empty */ { $$ = NULL; }
	;



expr_list
	: expr_list ',' expr { 
		$1->push_back($3);
		$$ = $1;
	}
	| expr {
		$$ = new expr_list_t();
		$$->push_back($1);
	}
	;



%%

