#pragma once
#include <vector>
#include <string>

namespace nde {
namespace script {
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
	BORASSIGN,
	BANDASSIGN,
	BXORASSIGN,
	LSHIFTASSIGN,
	RSHIFTASSIGN,
	ADDASSIGN,
	SUBASSIGN,
	MULASSIGN,
	DIVASSIGN,

	GT,
	LT,
	GTE,
	LTE,

	LSHIFT,
	RSHIFT,

	ADD,
	SUB,

	MUL,
	DIV,
	MOD,
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

struct ASTNode {
	virtual ~ASTNode() {}

};

struct VarType : public ASTNode {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType() {}
	VarType(eReturnType _t) : type(_t) {}
	virtual ~VarType() {}
};

struct ExprNode : public ASTNode  {
	virtual ~ExprNode() {}
};
struct StmtNode : public ASTNode  {
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
	BinaryExpr(ExprNode* _lhs, eBinaryOp _op, ExprNode* _rhs)
		: op(_op), lhs(_lhs), rhs(_rhs) {}
};

struct TernaryExpr : public ExprNode {
	ExprNode* condition;
	ExprNode* true_cond;
	ExprNode* false_cond;

	TernaryExpr(ExprNode* _c, ExprNode* _t, ExprNode* _f)
		: condition(_c), true_cond(_t), false_cond(_f) {}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	ExprNode* expr;

	UnaryExpr(eUnaryType _o, ExprNode* _e)
		: op(_o), expr(_e) {}
};

struct PrimaryExpr : public ExprNode {
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;

	IdentNode(std::string _i) : ident(_i) {}
};

struct LiteralExpr : public PrimaryExpr {
	eLiteralType type;
	std::string str_val;
	union {
		float flt_val;
		size_t int_val;
	};
	bool bool_val;
	// Vector vector_val;

	LiteralExpr(std::string _s)
		: type(eLiteralType::STRINGVAL), str_val(_s) {}
	LiteralExpr(float _f)
			: type(eLiteralType::FLOATVAL), flt_val(_f) {}
	LiteralExpr(size_t _i)
			: type(eLiteralType::INTVAL), int_val(_i) {}
	LiteralExpr(bool _b)
			: type(eLiteralType::BOOLVAL), bool_val(_b) {}
	//LiteralExpr(Vector _v)
	//		: type(eLiteralType::STRINGVAL), vector_val(_v) {}
};

struct AttributeNode : public PrimaryExpr {
	PrimaryExpr* lhs;
	IdentNode* ident;

	AttributeNode(PrimaryExpr* _l, IdentNode* _i)
		: lhs(_l), ident(_i) {}
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

	void passDown(IfStmt* block) {
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

struct BreakStmt : public StmtNode {};
struct ContinueStmt : public StmtNode {};

struct Program {
	declarations_t* declarations;
};

} //namespace ast
} // namespace script
} // namespace nde


