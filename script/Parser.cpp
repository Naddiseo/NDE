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
Parser::backup() {
	/*
	 *    +------+------+
	 *    |      |      |
	 * current  peek  *iter
	 */
	peek = current;
	iter -= 2;
	current = *iter++;
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
		next();
		expectType(TokenType::IDENT);

		switch (current.type) {
		case TokenType::LPAREN:
			// function decl
			ret = function_decl();
			break;
		case TokenType::ASSIGN:
		case TokenType::SEMICOLON:
			backup();
			backup();
			ret = var_decl();
			break;
		default:
			throw ParseError("Bad token for declaration", current);
			break;
		}
	};
		break;
	case TokenType::EVENT:
		ret = function_decl();
		break;
	case TokenType::CLASS: {
		ret = class_decl();
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
ast::ClassDecl Parser::class_decl() {
	ast::ClassDecl ret;

	expectType(TokenType::CLASS);
	ret.name = current.strtype;
	expectType(TokenType::IDENT);
	ret.parent = optional_inherits();

	expectType(TokenType::LBRACE);
	ret.declarations = declarations();
	expectType(TokenType::RBRACE);

	return ret;
}

/*
 * optional_inherits
 *   : COLON ident_t
 *   | // empty
 *   ;
 */
std::string Parser::optional_inherits() {
	std::string ret;

	if (current.type == TokenType::COLON) {
		next();
		ret = current.strtype;
		expectType(TokenType::IDENT);
	}
	else {
		next();
	}

	return ret;
}

/*
 * function_decl
 *   : return_type ident LPAREN optional_argument_list RPAREN code_block
 *   | EVENT return_type ident LPAREN optional_argument_list RPAREN code_block
 *   ;
 */
ast::FunctionDecl Parser::function_decl() {
	ast::FunctionDecl ret;

	if (current.type == TokenType::EVENT) {
		next();
		ret.is_event = true;
	}

	ret.type = return_type();
	ret.name = current.strtype;
	expectType(TokenType::IDENT);

	expectType(TokenType::LPAREN);
	ret.arguments = optional_argument_list();
	expectType(TokenType::RPAREN);

	ret.block = code_block();

	return ret;
}

/*
 * return_type
 *   : var_type
 *   | void
 *   ;
 */
ast::VarType Parser::return_type() {
	ast::VarType ret;

	if (current.type == TokenType::VOID) {
		ret.type = ast::eReturnType::VOID;
	}
	else {
		ret = var_type();
	}

	return ret;
}

/*
 * optional_argument_list
 *   : argument_list
 *   | // empty
 *   ;
 */
std::vector<ast::VarDecl>
Parser::optional_argument_list() {
	std::vector<ast::VarDecl> ret;

	while (current.type != TokenType::RPAREN) {
		ast::VarDecl arg;
		arg.type = var_type();
		arg.name = current.strtype;
		expectType(TokenType::IDENT);

		arg.default_value = optional_var_assign();

		if (current.type == TokenType::COMMA) {
			next();
		}
		ret.push_back(arg);
	}

	return ret;
}

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
ast::CodeBlock Parser::code_block() {
	ast::CodeBlock ret;
	expectType(TokenType::LBRACE);

	while (current.type != TokenType::RBRACE) {
		switch (current.type) {
		case TokenType::IF:
			ret.children.push_back(if_stmt());
			break;
		case TokenType::WHILE:
			ret.children.push_back(while_stmt());
			break;
		case TokenType::FOR:
			ret.children.push_back(for_stmt());
			break;
		case TokenType::RETURN:
			ret.children.push_back(return_stmt());
			break;
		case TokenType::INT:
		case TokenType::UINT:
		case TokenType::FLOAT:
		case TokenType::STRING:
		case TokenType::VECTOR:
		case TokenType::BOOL:
			ret.children.push_back(var_decl());
			break;
		default:
			ret.children.push_back(expr_stmt());
			break;
		}
	}

	expectType(TokenType::RBRACE);
	return ret;
}

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
ast::StmtNode Parser::statement() {
	ast::StmtNode ret;

	return ret;
}

/*
 * if_stmt
 *  : IF expr code_block optional_else_if_list optional_else
 *  ;
 */
ast::IfStmt Parser::if_stmt() {
	ast::IfStmt ret;

	return ret;
}

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
ast::WhileStmt Parser::while_stmt() {
	ast::WhileStmt ret;

	return ret;
}

/*
 * for_stmt
 *   : FOR expr_stmt expr_stmt expr_stmt code_block
 *   ;
 */
ast::ForStmt Parser::for_stmt() {
	ast::ForStmt ret;

	return ret;
}

/*
 * return_stmt
 *   : RETURN optional_expr_stmt
 *   ;
 */
ast::ReturnStmt Parser::return_stmt() {
	ast::ReturnStmt ret;

	return ret;
}

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
ast::ExprStmt Parser::expr_stmt() {
	ast::ExprStmt ret;

	return ret;
}

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
	ast::VarType ret;

	ret.is_array = (peek.type == TokenType::LSQUARE);

	switch (current.type) {
	case TokenType::IDENT:
		ret.type = ast::eReturnType::OBJECT;
		ret.class_name = current.strtype;
		break;
	case TokenType::INT:
		ret.type = ast::eReturnType::INT;
		break;
	case TokenType::UINT:
		ret.type = ast::eReturnType::UINT;
		break;
	case TokenType::FLOAT:
		ret.type = ast::eReturnType::FLOAT;
		break;
	case TokenType::STRING:
		ret.type = ast::eReturnType::STRING;
		break;
	case TokenType::VECTOR:
		ret.type = ast::eReturnType::VECTOR;
		break;
	case TokenType::BOOL:
		ret.type = ast::eReturnType::BOOL;
		break;
	default:
		THROW("Unexpected variable type", current);
		break;
	}
	next();

	if (ret.is_array) {
		expectType(TokenType::LSQUARE);
		expectType(TokenType::RSQUARE);
	}

	return ret;
}

/* optional_var_assign
 * 	: '=' expr
 * 	| // empty
 * 	;
 */
ast::ExprNode Parser::optional_var_assign() {
	if (current.type == TokenType::ASSIGN) {
		expectType(TokenType::ASSIGN);
		return Parser::expression();
	}

	return ast::EmptyExpression();
}

/*
 * expr
 * 	: assignment_expr
 * 	;
 */
ast::ExprNode Parser::expression() {

	return assignment_expr();
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
ast::ExprNode Parser::assignment_expr() {
	ast::ExprNode ret;

	return ret;
}

/*
 * ternary_expr
 *   : or_expr QUESTION expr COLON expr
 *   | or_expr
 *   ;
 */
ast::ExprNode Parser::ternary_expr() {
	ast::ExprNode ret;

	return ret;
}


/*
 * or_expr
 *   : or_expr OR and_expr
 *   | and_expr
 *   ;
 */
ast::ExprNode Parser::or_expr() {
	ast::ExprNode ret;

	return ret;
}

/*
 * and_expr
 *   : and_expr AND bor_expr
 *   | bor_expr
 *   ;
 */
ast::ExprNode Parser::and_expr() {
	ast::ExprNode ret;

	return ret;
}

/*
 * bor_expr
 *   : bor_expr BOR bxor_expr
 *   | bxor_expr
 *   ;
 */
ast::ExprNode Parser::bor_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * bxor_expr
 *   : bxor_expr BXOR band_Expr
 *   | band_expr
 *   ;
 */
ast::ExprNode Parser::bxor_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * band_expr
 *   : xand_expr BAND eq_expr
 *   | eq_expr
 *   ;
 */
ast::ExprNode Parser::band_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * eq_expr
 *   : eq_expr EQUALS comparison_expr
 *   | eq_expr NEQUALS comparison_expr
 *   | comparison_expr
 *   ;
 */
ast::ExprNode Parser::eq_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * comparison_expr
 *   : comparison_expr GT shift_expr
 *   | comparison_expr LT shift_expr
 *   | comparison_expr GTE shift_expr
 *   | comparison_expr LTE shift_expr
 *   | shift_expr
 *   ;
 */
ast::ExprNode Parser::comparison_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * shift_expr
 *   : shift_expr LSHIFT add_expr
 *   | shift_expr RSHIFT add_expr
 *   | add_expr
 *   ;
 */
ast::ExprNode Parser::shift_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * add_expr
 *   : add_expr ADD mul_expr
 *   | add_expr SUB mul_expr
 *   | mul_expr
 *   ;
 */
ast::ExprNode Parser::add_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * mul_expr
 *   : mul_expr MUL unary_expr
 *   | mul_expr DIV unary_expr
 *   | mul_expr MOD unary_expr
 *   | unary_expr
 *   ;
 */
ast::ExprNode Parser::mul_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * unary_expr
 *   : BNOT unary_expr
 *   | NOT unary_expr
 *   | INC unary_expr
 *   | DEC unary_expr
 *   | primary_expr
 *   ;
 */
ast::ExprNode Parser::unary_expr() {
	ast::ExprNode ret;

		return ret;
}

/*
 * primary_expr
 *   : atom
 *   | attribute
 *   | subscript
 *   | function_call
 *   ;
 */
ast::PrimaryExpr Parser::primary_expr() {
	ast::PrimaryExpr ret;

	return ret;
}

/*
 * atom
 *   : IDENT
 *   | literal
 *   | LPAREN expr RPAREN
 *   ;
 */
ast::ExprNode Parser::atom() {
	ast::ExprNode ret;

		return ret;
}

/*
 * attribute
 *   : primary_expr DOT IDENT
 *   ;
 */
ast::AttributeNode Parser::attribute() {
	ast::AttributeNode ret;

		return ret;
}

/*
 * subscript
 *   : primary_expr LSQUARE expr RSQUARE
 *   ;
 */
ast::SubscriptNode Parser::subscript() {
	ast::SubscriptNode ret;

		return ret;
}

/*
 * function_call
 *   : primary_expr LPAREN optional_expr_list RPAREN
 *   | TRIGGER primary_expr LPAREN optional_expr_list RPAREN
 *   ;
 */
ast::FunctionCall Parser::function_call() {
	ast::FunctionCall ret;

		return ret;
}

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
ast::LiteralExpr Parser::literal() {
	ast::LiteralExpr ret;

		return ret;
}

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
ast::expr_list_t Parser::expr_list() {
	ast::expr_list_t ret;

	return ret;
}


} // namespace nde

