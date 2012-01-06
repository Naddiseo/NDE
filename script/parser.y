%{

int yylex();
int yyerror(const char* p) { return 0;}

extern int yylineno;
%}
%locations

%union {
	char* stringval;
	int	 intval;
	bool	boolval;
	float floatval;
	float* vectorval;
}

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

%%

program
	: declarations
	| // empty
	;

declarations
	: declarations declaration
	| declaration
	;

declaration
	: function_decl
	| var_decl_stmt
	| class_decl 
	;

class_decl
	: CLASS IDENT optional_inherits '{' declarations '}'
	;

optional_inherits
	: ':' IDENT
	|
	;

function_decl
	: var_type IDENT '(' optional_argument_list ')' code_block
	| EVENT var_type IDENT '(' optional_argument_list ')' code_block
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
	: IF expr code_block optional_else_if_list optional_else
	;

optional_else_if_list
	: else_if_list
	|
	;

else_if_list
	: else_if_list else_if
	| else_if
	;

else_if
	: ELIF expr code_block
	;

optional_else
	: ELSE code_block
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
