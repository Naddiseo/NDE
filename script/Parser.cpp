#include <iostream>
#include "script/Parser.hpp"

namespace nde {

Parser::Parser(tokens_t& _tokens) : tokens(_tokens) {
	iter = tokens.begin();
	current = *iter++;
	peek = *iter;
}

Parser::~Parser() {}

bool
Parser::parse() {
	bool ret = true;

	try {
		ast = program();
	}
	catch (ParseError& e) {
		ret = false;
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

void
Parser::next() {
	current = peek;
	peek = *iter++;
}


void
Parser::expectType(Token t, TokenType tt) {
	if (t.type != tt) {
		throw ParseError("Expecting " + Token::typeToString(tt) + " got " + t.getName(), t);
	}
	next();
}
void
Parser::expectType(TokenType tt) {
	if (current.type != tt) {
		throw ParseError("Expecting " + Token::typeToString(tt) + " got " + current.getName(), current);
	}
	next();
}

/*
 * Grammar
 *
 *
 * program
 * 	: declarations
 * 	| // empty
 * 	;
 */
ast::Program Parser::program() {
	ast::Program ret;

	ret.declarations = declarations();

	return ret;
}

 /*
 * declarations
 * 	: declarations declaration
 * 	| declaration
 * 	;
 */
ast::declarations_t Parser::declarations() {
	ast::declarations_t ret;

	while (iter != tokens.end() && !current.isError()) {
		ret.push_back(declaration());
	}

	return ret;
}
 /* declaration
 * 	: function_decl
 * 	| var_decl
 * 	| class_decl
 * 	;
 */
ast::Decl Parser::declaration() {
	ast::Decl ret;
	switch (current.type) {
	case TokenType::INT:
	case TokenType::UINT:
	case TokenType::FLOAT:
	case TokenType::STRING:
	case TokenType::VECTOR:
	case TokenType::BOOL:
		// var or function decl
	case TokenType::VOID: {
		// method decl
		Token rettype = current;
		Token name;

		next();
		expectType(TokenType::IDENT);

		switch (current.type) {
		case TokenType::LPAREN:
			// function decl
			break;
		case TokenType::ASSIGN:
		case TokenType::SEMICOLON:
			var_decl();
			break;
		default:
			throw ParseError("Bad token for declaration", current);
			break;
		}
	};
		break;
	default:
		// error
		throw ParseError("Bad token for declaration", current);
		break;
	}

	return ret;
}

/*
 * class_decl
 *   : CLASS ident_t optional_inherits LBRACE declarations RBRACE
 *   ;
 */
ast::ClassDecl Parser::class_decl() {}

/*
 * optional_inherits
 *   : COLON ident_t
 *   | // empty
 *   ;
 */
std::string Parser::optional_inherits() {}

/*
 * function_decl
 *   : return_type ident LPAREN optional_argument_list RPAREN code_block
 *   | EVENT return_type ident LPAREN optional_argument_list RPAREN code_block
 *   ;
 */
ast::FunctionDecl Parser::function_decl() {}

/*
 * return_type
 *   : var_type
 *   | void
 *   ;
 */
ast::VarType Parser::return_type() {}

/*
 * optional_argument_list
 *   : argument_list
 *   | // empty
 *   ;
 */

/*
 * argument_list
 *   : argument_list COMMA argument
 *   | argument
 *   ;
 */

/*
 * argument
 *  : var_type ident_t optional_var_assign
 *  ;
 */

/*
 * code_block
 *   : LBRACE optional_statements RBRACE
 *   ;
 */
ast::CodeBlock Parser::code_block() {}

/*
 * optional_statements
 *   : statements
 *   | // empty
 *   ;
 */

/*
 * statements
 *   : statements statement
 *   | statement
 *   ;
 */

/*
 * statement
 *   : var_decl
 *   | if_stmt
 *   | while_stmt
 *   | for_stmt
 *   | return_stmt
 *   | expr_stmt
 *   ;
 */
ast::StmtNode Parser::statement() {}

/*
 * if_stmt
 *  : IF expr code_block optional_else_if_list optional_else
 *  ;
 */
ast::IfStmt Parser::if_stmt() {}

/*
 * optional_else_if_list
 *   : else_if_list
 *   | // empty
 *   ;
 */

/*
 * else_if_list
 *   : else_if_list else_if
 *   | else_if
 *   ;
 */

/*
 * else_if
 *   : ELSE IF expr code_block
 *   ;
 */

/*
 * optional_else
 *   : ELSE code_block
 *   | // empty
 *   ;
 */

/*
 * while_stmt
 *   : WHILE expr code_block
 *   ;
 */
ast::WhileStmt Parser::while_stmt() {}

/*
 * for_stmt
 *   : FOR expr_stmt expr_stmt expr_stmt code_block
 *   ;
 */
ast::ForStmt Parser::for_stmt() {}

/*
 * return_stmt
 *   : RETURN optional_expr_stmt
 *   ;
 */
ast::ReturnStmt Parser::return_stmt() {}

/*
 * optional_expr_stmt
 *   : expr_stmt
 *   | // none
 *   ;
 */

/*
 * expr_stmt
 *   : expr ';'
 *   ;
 */
ast::ExprStmt Parser::expr_stmt() {}

 /* var_decl
 * 	: var_type ident_t optional_var_assign ';'
 * 	;
 */
ast::VarDecl Parser::var_decl() {
	ast::VarDecl ret;
	return ret;
}

/* var_type
 * 	: ident_t
 * 	| int
 * 	| uint
 * 	| float
 * 	| string
 * 	| vector
 * 	| bool
 * 	| var_type LSQUARE RSQUARE
 * 	;
 */
ast::VarType Parser::var_type() {
	return ast::eReturnType::OBJECT;
}

/* optional_var_assign
 * 	: '=' expr
 * 	| // empty
 * 	;
 */
ast::ExprNode Parser::optional_var_assign() {
	if (current.type == TokenType::ASSIGN) {
		expectType(TokenType::ASSIGN);
		return Parser::expression() {}
	}

	return ast::EmptyExpression() {}
}

/*
 * expr
 * 	: assignment_expr
 * 	;
 */
ast::ExprNode Parser::expression() {

	return ast::EmptyExpression() {}
}

/*
 * assignment_expr
 *   : assignment_expr ASSIGN ternary_expr
 *   | assignment_expr BORASSIGN ternary_expr
 *   | assignment_expr BANDASSIGN ternary_expr
 *   | assignment_expr BXORASSIGN ternary_expr
 *   | assignment_expr LSHIFTASSIGN ternary_expr
 *   | assignment_expr RSHIFTASSIGN ternary_expr
 *   | assignment_expr ADDASSIGN ternary_expr
 *   | assignment_expr SUBASSIGN ternary_expr
 *   | assignment_expr MULASSIGN ternary_expr
 *   | assignment_expr DIVASSIGN ternary_expr
 *   | ternary_expr
 *   ;
 */
ast::ExprNode Parser::assignment_expr() {}

/*
 * ternary_expr
 *   : or_expr QUESTION expr COLON expr
 *   | or_expr
 *   ;
 */
ast::ExprNode Parser::ternary_expr() {}


/*
 * or_expr
 *   : or_expr OR and_expr
 *   | and_expr
 *   ;
 */
ast::ExprNode Parser::or_expr() {}

/*
 * and_expr
 *   : and_expr AND bor_expr
 *   | bor_expr
 *   ;
 */
ast::ExprNode Parser::and_expr() {}

/*
 * bor_expr
 *   : bor_expr BOR bxor_expr
 *   | bxor_expr
 *   ;
 */
ast::ExprNode Parser::bor_expr() {}

/*
 * bxor_expr
 *   : bxor_expr BXOR band_Expr
 *   | band_expr
 *   ;
 */
ast::ExprNode Parser::bxor_expr() {}

/*
 * band_expr
 *   : xand_expr BAND eq_expr
 *   | eq_expr
 *   ;
 */
ast::ExprNode Parser::band_expr() {}

/*
 * eq_expr
 *   : eq_expr EQUALS comparison_expr
 *   | eq_expr NEQUALS comparison_expr
 *   | comparison_expr
 *   ;
 */
ast::ExprNode Parser::eq_expr() {}

/*
 * comparison_expr
 *   : comparison_expr GT shift_expr
 *   | comparison_expr LT shift_expr
 *   | comparison_expr GTE shift_expr
 *   | comparison_expr LTE shift_expr
 *   | shift_expr
 *   ;
 */
ast::ExprNode Parser::comparison_expr() {}

/*
 * shift_expr
 *   : shift_expr LSHIFT add_expr
 *   | shift_expr RSHIFT add_expr
 *   | add_expr
 *   ;
 */
ast::ExprNode Parser::shift_expr() {}

/*
 * add_expr
 *   : add_expr ADD mul_expr
 *   | add_expr SUB mul_expr
 *   | mul_expr
 *   ;
 */
ast::ExprNode Parser::add_expr() {}

/*
 * mul_expr
 *   : mul_expr MUL unary_expr
 *   | mul_expr DIV unary_expr
 *   | mul_expr MOD unary_expr
 *   | unary_expr
 *   ;
 */
ast::ExprNode Parser::mul_expr() {}

/*
 * unary_expr
 *   : BNOT unary_expr
 *   | NOT unary_expr
 *   | INC unary_expr
 *   | DEC unary_expr
 *   | primary_expr
 *   ;
 */
ast::ExprNode Parser::unary_expr() {}

/*
 * primary_expr
 *   : atom
 *   | attribute
 *   | subscript
 *   | function_call
 *   ;
 */
ast::PrimaryExpr Parser::primary_expr() {}

/*
 * atom
 *   : IDENT
 *   | literal
 *   | LPAREN expr RPAREN
 *   ;
 */
ast::ExprNode Parser::atom() {}

/*
 * attribute
 *   : primary_expr DOT IDENT
 *   ;
 */
ast::AttributeNode Parser::attribute() {}

/*
 * subscript
 *   : primary_expr LSQUARE expr RSQUARE
 *   ;
 */
ast::SubscriptNode Parser::subscript() {}

/*
 * function_call
 *   : primary_expr LPAREN optional_expr_list RPAREN
 *   | TRIGGER primary_expr LPAREN optional_expr_list RPAREN
 *   ;
 */
ast::FunctionCall Parser::function_call() {}

/*
 * literal
 *   : STRINGVAL
 *   | INTVAL
 *   | UINTVAL
 *   | BOOLVAL
 *   | TRUE
 *   | FALSE
 *   | FLOATVAL
 *   | VECTORVAL
 *   ;
 */
ast::LiteralExpr Parser::literal() {}

/*
 * optional_expr_list
 *   : expr_list
 *   | // empty
 *   ;
 */

/*
 * expr_list
 *   : expr_list ',' expr
 *   | expr
 *   ;
 */
ast::expr_list_t Parser::expr_list() {}


} // namespace nde

