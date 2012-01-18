#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "Script.hpp"
#include "ASTree.hpp"
#include "ASTVisitor.hpp"
#include "location.hh"

NDESCRIPT_NS_BEGIN
namespace sem {

class SymbolRedefinedError : public std::runtime_error {
public:
	SymbolRedefinedError(std::string msg) : runtime_error(msg) {

	}

	static void Throw(location& loc, std::string sym) {
		std::stringstream ss;
		ss << loc << ", Symbol '" + sym + "' redefined";
		throw SymbolRedefinedError(ss.str());
	}
};

class CompileError : public std::runtime_error {
public:
	CompileError(std::string msg) : std::runtime_error("Compile Error: " + msg) {}
};

#define SEM_LIST(X) \
	X(ClassDecl) \
	X(VarDecl) \
	X(FunctionDecl)

#define FORWARD(X) struct X;
SEM_LIST(FORWARD)
#undef FORWARD

#define SMART_PTR(X) typedef std::shared_ptr<X> p##X;
SEM_LIST(SMART_PTR)
#undef SMART_PTR

typedef std::vector<pVarDecl> var_decls;
typedef std::vector<pFunctionDecl> function_decls;

struct SymbolEntry;
typedef std::shared_ptr<SymbolEntry> pSymbolEntry;

struct SymbolEntry {
	enum {
		CLASS,
		VARIABLE,
		FUNCTION
	} symtype;

	pClassDecl klass;
	pVarDecl   var;
	pFunctionDecl func;

	pSymbolEntry prev;
	pSymbolEntry next;

	size_t level;

	SymbolEntry();
	SymbolEntry(pClassDecl k);
	SymbolEntry(pVarDecl v);
	SymbolEntry(pFunctionDecl f);
	SymbolEntry(pClassDecl k, size_t _level);
	SymbolEntry(pVarDecl v, size_t _level);
	SymbolEntry(pFunctionDecl f, size_t _level);

	location& get_location();
	virtual ~SymbolEntry();
};

class SymbolTable {
	std::map<std::string, pSymbolEntry> sym_map;
	size_t level;
public:

	SymbolTable() : level(0) {}
	virtual ~SymbolTable();

	void pushScope();
	void popScope();

	void pushSymbol(std::string sym, pSymbolEntry& e);
	void pushSymbol(std::string sym, pClassDecl& k);
	void pushSymbol(std::string sym, pVarDecl& v);
	void pushSymbol(std::string sym, pFunctionDecl& f);
};

struct LocationNodeMixin {
	location loc;
};

struct Decl : public LocationNodeMixin {
	std::string name;
	virtual ~Decl() {}
};

struct ClassDecl : public Decl {
	ast::ClassDecl* ast;

	virtual ~ClassDecl();

	pClassDecl parent;
	var_decls vars;
	function_decls funcs;
};

struct VarDecl : public Decl {
	location loc;
	ast::VarDecl* ast;

	std::string name;
	bool is_array;
	ast::eReturnType return_type;

	virtual ~VarDecl() {}
};

struct FunctionDecl : public Decl {
	ast::FunctionDecl* ast;


	var_decls arguments;

	std::string name;

	pClassDecl klass;
	bool is_event;

	ast::eReturnType return_type;

	virtual ~FunctionDecl() {}
};

class Program {
	ast::Program* ast;

	std::vector<pClassDecl> classes;
	var_decls global_vars;
	function_decls global_functions;

	SymbolTable symtab;

public:
	Program() : ast(NULL), classes(), global_vars(), global_functions() {}
	virtual ~Program();

	//void walk(ast::Node* _node);
	void walk(ast::Program* prog);
	void walk(ast::VarType* _node);
	void walk(ast::ExprNode* _node);
	void walk(ast::StmtNode* _node);
	void walk(ast::expr_list_t* _node);
	void walk(ast::stmt_list_t* _node);
	void walk(ast::EmptyExpression* _node);
	void walk(ast::BinaryExpr* _node);
	void walk(ast::TernaryExpr* _node);
	void walk(ast::UnaryExpr* _node);
	void walk(ast::PrimaryExpr* _node);
	void walk(ast::IdentNode* _node);
	void walk(ast::LiteralExpr* _node);
	void walk(ast::AttributeNode* _node);
	void walk(ast::SubscriptNode* _node);
	void walk(ast::FunctionCall* _node);
	void walk(ast::CodeBlock* _node);
	void walk(ast::Decl* _node);
	void walk(ast::VarDecl* _node, pVarDecl var);
	void walk(ast::declarations_t* _node);
	void walk(ast::vardecls_t* _node, var_decls& decls);
	void walk(ast::FunctionDecl* _node, pFunctionDecl func);
	void walk(ast::ClassDecl* _node, pClassDecl klass);
	void walk(ast::IfStmt* _node);
	void walk(ast::WhileStmt* _node);
	void walk(ast::ForStmt* _node);
	void walk(ast::ExprStmt* _node);
	void walk(ast::ReturnStmt* _node);
	void walk(ast::ContinueStmt* _node);
	void walk(ast::BreakStmt* _node);

	void sem_error(std::string msg);
};


} //namespace sem
NDESCRIPT_NS_END
