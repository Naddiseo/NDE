%skeleton "lalr1.cc"
%require "2.3"
%defines
%define "parser_class_name" "Parser"
%name-prefix="nde::script"

%define "namespace" "nde::script"

%code requires {
#include "ASTree.hpp"
}

%{
#include "ASTree.hpp"
NDESCRIPT_NS_BEGIN
class Driver;
NDESCRIPT_NS_END
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
	
	ast::Node* node;
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

%type <node> optional_var_assign expr unary_expr primary_expr atom attribute subscript function_call literal ident_node

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
	: declarations {} 
	| /* empty*/ { YYACCEPT; }
	;

declarations
	: declarations declaration {
		driver.program.declarations.push_back($2);
	}
	| declaration {
		driver.program.declarations.push_back($1);
	}
	;

declaration
	: function_decl
	| var_decl_stmt
	| class_decl 
	;

class_decl
	: CLASS IDENT optional_inherits '{' declarations '}' {
		$$ = new ast::Node(new ast::ClassDecl(NULL, $2, $3, $5));
	}
	;

optional_inherits
	: ':' IDENT { $$ = $2; }
	| { $$ = const_cast<char*>(""); }
	;

function_decl
	: var_type IDENT '(' optional_argument_list ')' code_block {
		$$ = new ast::Node(new ast::FunctionDecl($1, std::string($2), false, $4, $6));
	}
	| EVENT var_type IDENT '(' optional_argument_list ')' code_block {
		$$ = new ast::Node(new ast::FunctionDecl($2, std::string($3), true, $5, $7));
	}
	;

optional_argument_list
	: argument_list
	| { $$ = NULL; }
	;

argument_list
	: argument_list ',' var_decl {
		((ast::vardecls_t*)$1)->push_back($3);
		$$ = $1;
	}
	| var_decl {
		auto tmp = new ast::vardecls_t();
		tmp->push_back($1);
		$$ = new ast::Node(tmp);
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
		((ast::stmt_list_t*)$1)->push_back($2);
		$$ = $1;
	}
	| statement {
		auto tmp = new ast::stmt_list_t();
		tmp->push_back($1);
		$$ = new ast::Node(tmp);
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
		$$ = new ast::Node(new ast::IfStmt($2, $3, $4));
	}
	;

optional_else_if_list
	: else_if_list 
	| optional_else
	;

else_if_list
	: else_if_list else_if {
		$$ = $1;
		((ast::IfStmt*)$$)->passDown($2);
	}
	| else_if {
		$$ = $1;
	}
	;

else_if
	: ELIF expr code_block optional_else {
		$$ = new ast::Node(new ast::IfStmt($2, $3, $4));
	}
	;

optional_else
	: ELSE code_block { $$ = $2; }
	| { $$ = NULL; }
	;

while_stmt
	: WHILE expr code_block {
		$$ = new ast::Node(new ast::WhileStmt($2, $3));
	}
	;

for_stmt
	: FOR expr ';' expr ';' expr code_block {
		$$ = new ast::Node(new ast::ForStmt($2, $4, $6, $7));
	}
	;

return_stmt
	: RETURN optional_expr_stmt  {
		$$ = new ast::Node(new ast::ReturnStmt($2));
	}
	;

optional_expr_stmt
	: expr_stmt
	| ';' { $$ = new ast::Node(new ast::ExprStmt(NULL)); }
	;

expr_stmt
	: expr ';' { 
		$$ = new ast::Node(new ast::ExprStmt($1));
	}
	;

var_decl_stmt
	: var_decl ';' { $$ = $1; }
	;

var_decl
	: var_type IDENT optional_is_array optional_var_assign {
		((ast::VarType*)$1)->is_array= $3;
		$$ = new ast::Node(new ast::VarDecl($1, $2, $4));
	}
	;

optional_is_array
	: '[' ']' { $$ = true; }
	| { $$ = false; }
	;

trigger_call
	: TRIGGER function_call ';' { // can't be used as a lhs
		$$ = $2;
		((ast::FunctionCall*)$$)->is_trigger = true;
	}
	;

loop_control_stmt
	: BREAK ';' { $$ = new ast::Node(new ast::BreakStmt()); }
	| CONTINUE ';' { $$ = new ast::Node(new ast::ContinueStmt()); }
	;

var_type
	: IDENT { $$ = new ast::Node(new ast::VarType(ast::eReturnType::OBJECT, $1)); }
	| INT { $$ = new ast::Node(new ast::VarType(ast::eReturnType::INT)); }
	| UINT { $$ = new ast::Node(new ast::VarType(ast::eReturnType::UINT)); } 
	| FLOAT { $$ = new ast::Node(new ast::VarType(ast::eReturnType::FLOAT)); }
	| STRING { $$ = new ast::Node(new ast::VarType(ast::eReturnType::STRING)); }
	| VECTOR { $$ = new ast::Node(new ast::VarType(ast::eReturnType::VECTOR)); }
	| BOOL { $$ = new ast::Node(new ast::VarType(ast::eReturnType::BOOL)); }
	| VOID { $$ = new ast::Node(new ast::VarType(ast::eReturnType::VOID)); }
	;

optional_var_assign
	: ASSIGN expr { $$ = $2; }
	| { $$ = NULL; }
	;

expr
	: expr ASSIGN  expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::ASSIGN, $3)); }
	| expr BORASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BORASSIGN, $3)); }
	| expr  BANDASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BANDASSIGN, $3)); }
	| expr BXORASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BXORASSIGN, $3)); }
	| expr  LSHIFTASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::LSHIFTASSIGN, $3)); }
	| expr RSHIFTASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::RSHIFTASSIGN, $3)); }
	| expr ADDASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::ADDASSIGN, $3)); }
	| expr SUBASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::SUBASSIGN, $3)); }
	| expr MULASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::MULASSIGN, $3)); }
	| expr DIVASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::DIVASSIGN, $3)); }
	| expr MODASSIGN expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::MODASSIGN, $3)); }
	| expr '?' expr ':' expr { $$ = new ast::Node(new ast::TernaryExpr($1, $3, $5)); }
	| expr OR expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::OR, $3)); }
	| expr AND expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::AND, $3)); }
	| expr '|' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BOR, $3)); }
	| expr '^' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BXOR, $3)); }
	| expr '&' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::BAND, $3)); }
	| expr EQUAL expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::EQUAL, $3)); }
	| expr NEQUAL expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::NEQUAL, $3)); }
	| expr GT expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::GT, $3)); }
	| expr LT expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::LT, $3)); }
	| expr GTE expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::GTE, $3)); }
	| expr LTE expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::LTE, $3)); }
	| expr LSHIFT expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::LSHIFT, $3)); }
	| expr RSHIFT expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::RSHIFT, $3)); }
	| expr '+' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::ADD, $3)); }
	| expr '-' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::SUB, $3)); }
	| expr '*' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::MUL, $3)); }
	| expr '/' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::DIV, $3)); }
	| expr '%' expr { $$ = new ast::Node(new ast::BinaryExpr($1, ast::eBinaryOp::MOD, $3)); }
	| unary_expr
	;

unary_expr
	: '~' unary_expr %prec UNARY { $$ = new ast::Node(new ast::UnaryExpr(ast::eUnaryType::BNOT, $2)); }
	| '!' unary_expr %prec UNARY { $$ = new ast::Node(new ast::UnaryExpr(ast::eUnaryType::NOT, $2)); }
	| INC unary_expr %prec UNARY { $$ = new ast::Node(new ast::UnaryExpr(ast::eUnaryType::INC, $2)); }
	| DEC unary_expr %prec UNARY { $$ = new ast::Node(new ast::UnaryExpr(ast::eUnaryType::DEC, $2)); }
	| primary_expr
	;

primary_expr
	: atom
	| attribute
	| subscript
	| function_call
	;

atom
	: ident_node {  }
	| literal
	| '(' expr ')' { $$ = $2; }
	;

attribute
	: primary_expr '.' ident_node { $$ = new ast::Node(new ast::AttributeNode($1, $3)); }
	;

ident_node
	: IDENT { $$ = new ast::Node(new ast::IdentNode($1)); }
	;

subscript
	: primary_expr '[' expr ']' { $$ = new ast::Node(new ast::SubscriptNode($1, $3)); }
	;

function_call
	: primary_expr '(' optional_expr_list ')' { $$ = new ast::Node(new ast::FunctionCall($1, $3)); }
	;

literal
	: STRINGVAL { $$ = new ast::Node(new ast::LiteralExpr($1)); }
	| INTVAL { $$ = new ast::Node(new ast::LiteralExpr($1)); }
	| BOOLVAL { $$ = new ast::Node(new ast::LiteralExpr($1)); }
	| FLOATVAL { $$ = new ast::Node(new ast::LiteralExpr($1)); }
	| VECTORVAL { $$ = new ast::Node(new ast::LiteralExpr($1)); }
	;

optional_expr_list
	: expr_list
	| /* empty */ { $$ = NULL; }
	;

expr_list
	: expr_list ',' expr { 
		((expr_list_t*)$1)->push_back($3);
		$$ = $1;
	}
	| expr {
		auto tmp = new expr_list_t();
		tmp->push_back($1);
		
		$$ = new ast::Node(tmp);
	}
	;

%%

