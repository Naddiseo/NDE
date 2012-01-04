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

	/*
		 * class_decl
		 *   : CLASS ident_t optional_inherits LBRACE declarations RBRACE
		 *   ;
		 */

		/*
		 * optional_inherits
		 *   : COLON ident_t
		 *   | // empty
		 *   ;
		 */

		/*
		 * function_decl
		 *   : return_type ident LPAREN optional_argument_list RPAREN code_block
		 *   | EVENT return_type ident LPAREN optional_argument_list RPAREN code_block
		 *   ;
		 */

		/*
		 * return_type
		 *   : var_type
		 *   | void
		 *   ;
		 */

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

		/*
		 * if_stmt
		 *  : IF expr code_block optional_else_if_list optional_else
		 *  ;
		 */

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

		/*
		 * for_stmt
		 *   : FOR expr SEMICOLON expr SEMICOLON expr SEMICOLON code_block
		 *   ;
		 */

		/*
		 * return_stmt
		 *   : RETURN optional_expr_stmt
		 *   ;
		 */

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
	 * 	| var_type LSQUARE RSQUARE
	 * 	;
	 */
	ast::eReturnType var_type();

	/* optional_var_assign
	 * 	: ASSIGN expr
	 * 	| // empty
	 * 	;
	 */
	ast::ExprNode optional_var_assign();

	/*
	 * expr
	 * 	: assignment_expr
	 * 	;
	 */
	ast::ExprNode expression();

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
		/*
		 * ternary_expr
		 *   : or_expr QUESTION expr COLON expr
		 *   | or_expr
		 *   ;
		 */

		/*
		 * or_expr
		 *   : or_expr OR and_expr
		 *   | and_expr
		 *   ;
		 */

		/*
		 * and_expr
		 *   : and_expr AND bor_expr
		 *   | bor_expr
		 *   ;
		 */

		/*
		 * bor_expr
		 *   : bor_expr BOR bxor_expr
		 *   | bxor_expr
		 *   ;
		 */

		/*
		 * bxor_expr
		 *   : bxor_expr BXOR band_Expr
		 *   | band_expr
		 *   ;
		 */

		/*
		 * band_expr
		 *   : xand_expr BAND eq_expr
		 *   | eq_expr
		 *   ;
		 */

		/*
		 * eq_expr
		 *   : eq_expr EQUALS comparison_expr
		 *   | eq_expr NEQUALS comparison_expr
		 *   | comparison_expr
		 *   ;
		 */

		/*
		 * comparison_expr
		 *   : comparison_expr GT shift_expr
		 *   | comparison_expr LT shift_expr
		 *   | comparison_expr GTE shift_expr
		 *   | comparison_expr LTE shift_expr
		 *   | shift_expr
		 *   ;
		 */

		/*
		 * shift_expr
		 *   : shift_expr LSHIFT add_expr
		 *   | shift_expr RSHIFT add_expr
		 *   | add_expr
		 *   ;
		 */

		/*
		 * add_expr
		 *   : add_expr ADD mul_expr
		 *   | add_expr SUB mul_expr
		 *   | mul_expr
		 *   ;
		 */

		/*
		 * mul_expr
		 *   : mul_expr MUL unary_expr
		 *   | mul_expr DIV unary_expr
		 *   | mul_expr MOD unary_expr
		 *   | unary_expr
		 *   ;
		 */

		/*
		 * unary_expr
		 *   : BNOT unary_expr
		 *   | NOT unary_expr
		 *   | INC unary_expr
		 *   | DEC unary_expr
		 *   | primary_expr
		 *   ;
		 */

		/*
		 * primary_expr
		 *   : atom
		 *   | attribute
		 *   | subscript
		 *   | function_call
		 *   ;
		 */

		/*
		 * atom
		 *   : IDENT
		 *   | literal
		 *   | LPAREN expr RPAREN
		 *   ;
		 */

		/*
		 * attribute
		 *   : primary_expr DOT IDENT
		 *   ;
		 */

		/*
		 * subscript
		 *   : primary LSQUARE expr RSQUARE
		 *   ;
		 */

		/*
		 * function_call
		 *   : primary LPAREN optional_expr_list RPAREN
		 *   | TRIGGER LPAREN optional_expr_list RPAREN
		 *   ;
		 */

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

};

} // namespace nde


