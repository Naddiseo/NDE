#pragma once
#include <vector>
#include <string>

namespace nde {
namespace ast {

enum class eReturnType {
	VOID,
	INT,
	UINT,
	FLOAT,
	VECTOR,
	STRING,
	BOOL,
	OBJECT
};

enum class eDeclType {
	ERROR,
	VAR,
	FUNCTION,
	CLASS
};

enum class eBinaryOp {
	ERROR,
	ASSIGN,
	BOR,
	BAND,
	BXOR,
	LSHIFT,
	RSHIFT,
	ADD,
	SUB,
	MUL,
	DIV

	GT,
	LT,
	GTE,
	LTE

	LEFT,
	RIGHT

	ADD,
	SUB

	MUL,
	DIV,
	MOD
};

enum class eUnaryType {
	BNOT,
	NOT,
	INC,
	DEC
};

enum class eLiteralType {
	STRINGVAL,
	INTVAL,
	UINTVAL,
	BOOLVAL,
	TRUE,
	FALSE,
	FLOATVAL,
	VECTORVAL,
};

struct VarType {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType() {}
	VarType(eReturnType _t) : type(_t) {}
};

struct ExprNode {
	virtual ~ExprNode() {}
};
struct StmtNode {
	virtual ~StmtNode() {}
};
typedef std::vector<ExprNode> expr_list_t;
typedef std::vector<StmtNode> stmt_list_t;

struct EmptyExpression : public ExprNode {};

struct BinaryExpr : public ExprNode {
	eBinaryOp op;
	ExprNode* lhs;
	ExprNode* rhs;
	
	BinaryExpr() : op(eBinaryOp::ERROR) {}
	BinaryExpr(eBinaryOp _o) : op(_o) {}
};

struct TernaryExpr : public ExprNode {
	ExprNode* condition;
	ExprNode* true_cond;
	ExprNode* false_cond;
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	ExprNode* expr;
};

struct PrimaryExpr : public ExprNode {
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;
};

struct LiteralExpr : public PrimaryExpr {
	eLiteralType type;
	std::string str_val;
	union {
		float flt_val;
		int int_val;
	};
	bool bool_val;
	// Vector vector_val;
};

struct AttributeNode : public PrimaryExpr {
	PrimaryExpr* lhs;
	IdentNode* ident;
};

struct SubscriptNode : public PrimaryExpr {
	PrimaryExpr* base;
	ExprNode* subscript;
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	PrimaryExpr* name;
	expr_list_t* arguments;
};

struct CodeBlock : public StmtNode {
	stmt_list_t* children;
};

struct Decl : StmtNode {
	VarType* type;
	eDeclType decl_type;
	eReturnType value_type;
	std::string* name;

	Decl() : decl_type(eDeclType::ERROR) {}
	Decl(eDeclType _t) : decl_type(_t) {}
	virtual ~Decl();
};

typedef std::vector<Decl*> declarations_t;

struct VarDecl : public Decl {
	ExprNode* default_value;
	VarDecl() : Decl(eDeclType::VAR) {}
};

typedef std::vector<VarDecl*> vardecls_t;

struct FunctionDecl : public Decl {
	bool is_event;
	vardecls_t* arguments;
	CodeBlock* block;

	FunctionDecl() : Decl(eDeclType::FUNCTION) {}
};

struct ClassDecl : public Decl {
	std::string parent;
	declarations_t* declarations;

	ClassDecl() : Decl(eDeclType::CLASS) {}
};

struct IfStmt :  public StmtNode {
	ExprNode* condition;
	CodeBlock* true_block;
	IfStmt* false_block;
	
	IfStmt() : condition(NULL), true_block(NULL), false_block(NULL) {}
	
	void passDown(StmtNode* block) {
		if (false_block == NULL) {
			false_block = block;
		}
		else {
			false_block->passDown(block);
		}
	}
};

struct WhileStmt :  public StmtNode {
	ExprNode* condition;
	CodeBlock* block;
};

struct ForStmt :  public StmtNode {
	ExprNode* begin;
	ExprNode* condition;
	ExprNode* counter;
	CodeBlock* block;
};

struct ExprStmt :  public StmtNode {
	ExprNode* expr;
};

struct ReturnStmt :  public StmtNode {
	ExprStmt* return_val;
};

struct BreakStmt : public StmtNode {}
struct ContinueStmt : public StmtNode {}

struct Program {
	declarations_t* declarations;
};

} //namespace ast
} // namespace nde


