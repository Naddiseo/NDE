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

std::string to_string(const location& loc);

class SymbolRedefinedError : public std::runtime_error {
public:
	SymbolRedefinedError(std::string msg) : runtime_error(msg) {}
};

class CompileError : public std::runtime_error {
public:
	CompileError(std::string msg) : std::runtime_error("Compile Error: " + msg) {}
	CompileError(ast::Node* _node, std::string msg)
		: std::runtime_error(to_string(_node->loc)) {}
};


#define FORWARD(klass, var, enum_name) struct klass;
NODETYPE(FORWARD)
struct VarType;
#undef FORWARD

#define SMART_PTR(klass, var, enum_name) typedef std::shared_ptr<klass> p##klass;
NODETYPE(SMART_PTR)
typedef std::shared_ptr<VarType> pVarType;
#undef SMART_PTR

typedef std::vector<pVarDecl> var_decls;
typedef std::vector<pFunctionDecl> function_decls;
typedef std::vector<pStmtNode> stmt_list;
typedef std::vector<pExprNode> expr_list;

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

struct StmtNode : virtual public LocationNodeMixin {
	virtual ~StmtNode() {}
};

struct CodeBlock : public StmtNode {
	ast::CodeBlock* ast;

	stmt_list stmts;


	virtual ~CodeBlock() {}
};
/*
struct VarType : public LocationNodeMixin, public StmtNode {
	ast::VarType* ast;

	virtual ~VarType() {}
};*/

struct Decl : virtual public LocationNodeMixin {
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

struct VarDecl : public Decl, public StmtNode {
	ast::VarDecl* ast;

	std::string name;
	bool is_array;
	ast::eReturnType return_type;

	virtual ~VarDecl() {}
};

struct FunctionDecl : public Decl {
	ast::FunctionDecl* ast;

	var_decls arguments;
	pCodeBlock body;

	std::string name;

	pClassDecl klass;
	bool is_event;

	ast::eReturnType return_type;

	FunctionDecl()
		: ast(NULL), body(new CodeBlock()), is_event(false), return_type(ast::eReturnType::VOID) {}

	virtual ~FunctionDecl() {}
};

struct IfStmt : public StmtNode {
	ast::IfStmt* ast;

	pExprNode condition;
	pCodeBlock true_block;
	pStmtNode false_block;

	virtual ~IfStmt() {}
};

struct WhileStmt : public StmtNode {
	ast::WhileStmt* ast;

	pExprNode condition;
	pCodeBlock body;

	virtual ~WhileStmt() {}
};

struct ForStmt : public StmtNode {
	ast::ForStmt* ast;

	pExprStmt begin;
	pExprStmt condition;
	pExprStmt counter;
	pCodeBlock body;

	virtual ~ForStmt() {}
};

struct ExprStmt : public StmtNode {
	ast::ExprStmt* ast;

	pExprNode expr;

	virtual ~ExprStmt() {}
};

struct ReturnStmt : public StmtNode {
	ast::ReturnStmt* ast;

	pExprNode return_val;

	virtual ~ReturnStmt() {}
};

struct ContinueStmt : public StmtNode {
	ast::ContinueStmt* ast;

	virtual ~ContinueStmt() {}
};

struct BreakStmt : public StmtNode {
	ast::BreakStmt* ast;

	virtual ~BreakStmt() {}
};

struct ExprNode : public LocationNodeMixin {
	ast::ExprNode* ast;
	virtual ~ExprNode() {}
};

struct EmptyExpression : public ExprNode {
	ast::EmptyExpression* ast;
	virtual ~EmptyExpression() {}
};

struct BinaryExpr : public ExprNode {
	ast::BinaryExpr* ast;
	pExprNode lhs;
	ast::eBinaryOp op;
	pExprNode rhs;

	virtual ~BinaryExpr() {}
};

struct TernaryExpr : public ExprNode {
	ast::TernaryExpr* ast;

	virtual ~TernaryExpr() {}
};

struct UnaryExpr : public ExprNode {
	ast::UnaryExpr* ast;

	virtual ~UnaryExpr() {}
};

struct PrimaryExpr : public ExprNode {
	ast::PrimaryExpr* ast;

	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	ast::IdentNode* ast;

	virtual ~IdentNode() {}
};

struct LiteralExpr : public PrimaryExpr {
	ast::LiteralExpr* ast;

	virtual ~LiteralExpr() {}
};

struct AttributeNode : public PrimaryExpr {
	ast::AttributeNode* ast;

	virtual ~AttributeNode() {}
};

struct SubscriptNode : public PrimaryExpr {
	ast::SubscriptNode* ast;

	virtual ~SubscriptNode() {}
};

struct FunctionCall : public PrimaryExpr {
	ast::FunctionCall* ast;

	pIdentNode name;
	expr_list arguments;

	virtual ~FunctionCall() {}
};


class Program {
	ast::Program* ast;

	std::vector<pClassDecl> classes;
	var_decls global_vars;
	function_decls global_functions;

	SymbolTable symtab;

	int in_breakable;
	pFunctionDecl current_fn;
public:
	Program()
		: ast(NULL), classes(),
		  global_vars(), global_functions(),
		  in_breakable(0) {}
	virtual ~Program();


	//void walk(ast::Node* _node);

	void walk(ast::Node* _node, pExprNode expr);
	void walk(ast::Node* _node, pStmtNode expr);

	void walk(ast::Program* prog);
	void walk(ast::VarType* _node, pStmtNode stmt);
	void walk(ast::ExprNode* _node, pExprNode expr);
	void walk(ast::StmtNode* _node, pStmtNode stmt);
	void walk(ast::expr_list_t* _node, expr_list& elist);
	void walk(ast::stmt_list_t* _node, stmt_list& slist);
	void walk(ast::EmptyExpression* _node, pExprNode expr);
	void walk(ast::BinaryExpr* _node, pBinaryExpr expr);
	void walk(ast::TernaryExpr* _node, pExprNode expr);
	void walk(ast::UnaryExpr* _node, pExprNode expr);
	void walk(ast::PrimaryExpr* _node, pExprNode expr);
	void walk(ast::IdentNode* _node, pExprNode expr);
	void walk(ast::LiteralExpr* _node, pExprNode expr);
	void walk(ast::AttributeNode* _node, pExprNode expr);
	void walk(ast::SubscriptNode* _node, pExprNode expr);
	void walk(ast::FunctionCall* _node, pExprNode expr);
	void walk(ast::CodeBlock* _node, pCodeBlock block);
	void walk(ast::Decl* _node);
	void walk(ast::VarDecl* _node, pVarDecl var);
	void walk(ast::declarations_t* _node);
	void walk(ast::vardecls_t* _node, var_decls& decls);
	void walk(ast::FunctionDecl* _node, pFunctionDecl func);
	void walk(ast::ClassDecl* _node, pClassDecl klass);
	void walk(ast::IfStmt* _node, pIfStmt stmt);
	void walk(ast::WhileStmt* _node, pWhileStmt stmt);
	void walk(ast::ForStmt* _node, pForStmt stmt);
	void walk(ast::ExprStmt* _node, pExprStmt stmt);
	void walk(ast::ReturnStmt* _node, pReturnStmt stmt);
	void walk(ast::ContinueStmt* _node, pContinueStmt stmt);
	void walk(ast::BreakStmt* _node, pBreakStmt stmt);

	void sem_error(std::string msg);
	ast::eReturnType get_expr_type(ast::Node* _node);
};


} //namespace sem
NDESCRIPT_NS_END
