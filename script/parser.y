%{
#include "ASTree.hpp"

int yylex();
int yyerror(const char* p) { return 0;}

extern int yylineno;

using namespace nde::ast;
%}
%locations



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
%token ASSIGN LSHIFTASSIGN RSHIFTASSIGN BORASSIGN BANDASSIGN BXORASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN

/* Comparisons */
%token EQUAL NEQUAL LTE GTE LT GT

/* OTHER */
%token LSHIFT RSHIFT INC DEC

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

%union {
	char* stringval;
	int	 intval;
	bool	boolval;
	float floatval;
	float* vectorval;
	
	eReturnType  vartype;
	eDeclType    decltype;
	eBinaryOp    binop;
	eUnaryOp     uop;
	eLiteralType littype;
	
	VarType*    vartype_class;
	ExprNode*   exprnode;
	StmtNode*   stmtnode;
	
	BinaryExpr* binexpr;
	TernaryExpr* ternexpr;
	UnaryExpr*   uexpr;
	
	PrimaryExpr* primexpr;
	IdentNode*   identnode;
	LiteralExpr* literalexpr;
	AttributeNode* attrnode;
	SubscriptNode* subscriptnode;
	FunctionCall*  funccall;
	CodeBlock*     codeblock;
	
	Decl*          decl;
	VarDecl*       vardecl;
	FunctionDecl*  funcdecl;
	ClassDecl*     classdecl;
	
	IfStmt*        ifstmt;
	WhileStmt*     whilestmt;
	ForStmt*       forstmt;
	ExprStmt*      exprstmt;
	ReturnStmt*    returnstmt;
	BreakStmt*     breakstmt;
	ContinueStmt*  continuestmt;
	
	Program*       program;
	
	
	expr_list_t*    exprlist;
	stmt_list_t*    stmtlist;
	declarations_t* decllist;
	vardecls_t*     vardecllist;
	
}
//char*
%type <stringval> optional_inherits

//int
%type <intval> 

//bool
%type <boolval> 

//float
%type <floatval> 

//float*
%type <vectorval> 

//eReturnType
%type <vartype> 

//eDeclType
%type <decltype> 

//eBinaryOp
%type <binop> 

//eUnaryOp
%type <uop> 

//eLiteralType
%type <littype> 

//VarType*
%type <vartype_class> 

//ExprNode*
%type <exprnode> 

//StmtNode*
%type <stmtnode> statement

//BinaryExpr*
%type <binexpr> 

//TernaryExpr*
%type <ternexpr> 

//UnaryExpr*
%type <uexpr> 

//PrimaryExpr*
%type <primexpr>
 
//IdentNode*
%type <identnode> 

//LiteralExpr*
%type <literalexpr> 

//AttributeNode*
%type <attrnode> 

//SubscriptNode*
%type <subscriptnode> 

//FunctionCall*
%type <funccall> 

//CodeBlock*
%type <codeblock> code_block optional_else

//Decl*
%type <decl> declaration

//VarDecl*
%type <vardecl> 

//FunctionDecl*
%type <funcdecl> function_decl

//ClassDecl*
%type <classdecl> class_decl
 
//IfStmt*
%type <ifstmt> if_stmt optional_else_if_list else_if_list else_if

//WhileStmt*
%type <whilestmt> 

//ForStmt*
%type <forstmt> 

//ExprStmt*
%type <exprstmt> 

//ReturnStmt*
%type <returnstmt> 

//BreakStmt*
%type <breakstmt> 

//ContinueStmt*
%type <continuestmt> 

//Program*
%type <program> program

//expr_list_t*
%type <exprlist> 

//stmt_list_t*
%type <stmtlist> optional_statements statements

//declarations_t*
%type <decllist> declarations

//vardecls_t*
%type <vardecllist> optional_argument_list argument_list


%%

program
	: declarations {
		$$ = new Program();
		$$->declarations = $1;
	} 
	| // empty { $$ = NULL; }
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
		f->is_event = false;
		f->arguments = $4;
		f->block = $6;
		$$ = f;
	}
	| EVENT var_type IDENT '(' optional_argument_list ')' code_block {
		FunctionDecl* f = new FunctionDecl();
		f->is_event = true;
		f->arguments = $4;
		f->block = $6;
		$$ = f;
	}
	;

optional_argument_list
	: argument_list
	|
	;

argument_list
	: argument_list ',' var_decl
	| var_decl
	;

code_block
	: '{' optional_statements '}'
	;

optional_statements
	: statements
	|
	;

statements
	: statements statement
	| statement
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
		if ($4 == NULL) {
			$$->false_block = $5;
		}
		else {
			$4->passDown($5);
			$$->false_block = $4;
		}
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
	: WHILE expr code_block
	;

for_stmt
	: FOR expr ';' expr ';' expr code_block
	;

return_stmt
	: RETURN optional_expr_stmt 
	;

optional_expr_stmt
	: expr_stmt
	| ';'
	;

expr_stmt
	: expr ';'
	;

var_decl_stmt
	: var_decl ';'
	;

var_decl
	: var_type IDENT optional_is_array optional_var_assign
	;

optional_is_array
	: '[' ']'
	|
	;

trigger_call
	: TRIGGER function_call ';' // can't be used as a lhs
	;

loop_control_stmt
	: BREAK ';'
	| CONTINUE ';'
	;

var_type
	: IDENT
	| INT
	| UINT
	| FLOAT
	| STRING
	| VECTOR
	| BOOL
	| VOID
	;

optional_var_assign
	: ASSIGN expr
	|
	;

expr
	: expr ASSIGN  expr
	| expr BORASSIGN expr
	| expr  BANDASSIGN expr
	| expr BXORASSIGN expr
	| expr  LSHIFTASSIGN expr
	| expr RSHIFTASSIGN expr
	| expr ADDASSIGN expr
	| expr SUBASSIGN expr
	| expr MULASSIGN expr
	| expr DIVASSIGN expr
	| expr MODASSIGN expr
	| expr '?' expr ':' expr 
	| expr OR expr
	| expr AND expr
	| expr '|' expr
	| expr '^' expr
	| expr '&' expr
	| expr EQUAL expr
	| expr NEQUAL expr
	| expr GT expr
	| expr LT expr
	| expr GTE expr
	| expr LTE expr
	| expr LSHIFT expr
	| expr RSHIFT expr
	| expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| expr '%' expr
	| unary_expr
	;

unary_expr
	: '~' unary_expr %prec UNARY
	| '!' unary_expr %prec UNARY
	| INC unary_expr %prec UNARY
	| DEC unary_expr %prec UNARY
	| primary_expr
	;



primary_expr
	: atom
	| attribute
	| subscript
	| function_call
	;



atom
	: IDENT
	| literal
	| '(' expr ')'
	;



attribute
	: primary_expr '.' IDENT
	;



subscript
	: primary_expr '[' expr ']'
	;



function_call
	: primary_expr '(' optional_expr_list ')'
	;


literal
	: STRINGVAL
	| INTVAL
	| BOOLVAL
	| FLOATVAL
	| VECTORVAL
	;



optional_expr_list
	: expr_list
	| // empty
	;



expr_list
	: expr_list ',' expr
	| expr
	;



%%

int main() {
	while (yyparse()) {}

	return 0;
}
