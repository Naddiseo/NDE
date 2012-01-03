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
std::vector<ast::Decl> Parser::declarations() {
	std::vector<ast::Decl> ret;

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
 * 	;
 */
ast::eReturnType Parser::var_type() {
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
		return expression();
	}

	return ast::EmptyExpression();
}

ast::ExprNode Parser::expression() {

	return ast::EmptyExpression();
}

} // namespace nde

