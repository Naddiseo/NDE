#pragma once
#include <exception>
#include <sstream>
#include "script/Token.hpp"
#include "script/ASTree.hpp"

namespace nde {

class ParseError : public std::exception {
	std::stringstream msg;
public:
	ParseError(std::string msg, Token t) {
		this->msg << "Parse Error[" << t.lineno << ":" << t.charno << "] " << msg;
	}

	ParseError(const nde::ParseError& other) { msg = other.msg; };

	virtual ~ParseError() throw();

	const char* what() const throw() {
		return msg.str().c_str();
	}
};

class Parser {
	tokens_t tokens;
	tokens_t::iterator iter;
	Token current;
	Token peek;
public:
	Parser(tokens_t& _tokens);
	virtual ~Parser();

	bool parse();
private:

	void next();
	void expectType(Token t, TokenType tt);
	void expectType(TokenType tt);

	/*
	 * Grammar
	 *
	 *
	 * program
	 * 	: declarations
	 * 	| // empty
	 * 	;
	 */
	ast::Program program();

	 /*
	 * declarations
	 * 	: declarations declaration
	 * 	| declaration
	 * 	;
	 */
	std::vector<ast::Decl> declarations();
	 /* declaration
	 * 	: function_decl
	 * 	| var_decl
	 * 	| class_decl
	 * 	;
	 */
	ast::Decl declaration();

	 /* var_decl
	 * 	: var_type ident_t optional_var_assign ';'
	 * 	;
	 */
	ast::VarDecl var_decl();

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
	ast::eReturnType var_type();

	/* optional_var_assign
	 * 	: '=' expr
	 * 	| // empty
	 * 	;
	 */
	void optional_var_assign();

};

} // namespace nde


