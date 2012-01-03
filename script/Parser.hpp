#pragma once
#include <exception>
#include <sstream>
#include <script/ScriptBase.hpp>
#include "script/Token.hpp"
#include "script/ASTree.hpp"

namespace nde {

class ParseError : public std::exception {
	std::stringstream msg;
public:
	ParseError(std::string msg, Token t) {
		this->msg << "Parse Error[" << t.lineno << ":" << t.charno << "] " << msg;
	}

	ParseError(const nde::ParseError& other) { msg << other.msg.str(); };

	virtual ~ParseError() throw(){}

	const char* what() const throw() {
		return msg.str().c_str();
	}
};

class Parser : public ScriptBase<ParseError> {
	tokens_t tokens;
	tokens_t::iterator iter;
	Token current;
	Token peek;

	ast::Program ast;
public:
	Parser(tokens_t& _tokens);
	virtual ~Parser();

	bool parse();

	ast::Program& getAST() { return ast; }
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
	ast::ExprNode optional_var_assign();

	/*
	 * expr
	 * 	: assignment
	 * 	;
	 */
	ast::ExprNode expression();

};

} // namespace nde


