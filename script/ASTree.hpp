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

enum class eAssignType {
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
};

enum class eComparisonType {
	GT,
	LT,
	GTE,
	LTE
};

enum class eShiftType {
	LEFT,
	RIGHT
};

enum class eAddType {
	ADD,
	SUB
};

enum class eMulType {
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

struct ExprNode {};
struct StmtNode {};
typedef std::vector<ExprNode> expr_list_t;
typedef std::vector<StmtNode> stmt_list_t;

struct EmptyExpression : public ExprNode {};

struct BinaryExpr : public ExprNode {
	ExprNode lhs;
	ExprNode rhs;
};


struct AssignmentExpr : public BinaryExpr {
	eAssignType op;
};

struct TernaryExpr : public ExprNode {
	ExprNode condition;
	ExprNode true_cond;
	ExprNode false_cond;
};

struct OrExpr : public BinaryExpr {};
struct XorExpr : public BinaryExpr {};
struct AndExpr : public BinaryExpr {};
struct EqualsExpr : public BinaryExpr {
	bool is_negated;
};

struct ComparisonExpr : public BinaryExpr {
	eComparisonType op;
};

struct ShiftExpr : public BinaryExpr {
	eShiftType op;
};

struct AddExpr : public BinaryExpr {
	eAddType op;
};

struct MulExpr : public BinaryExpr {
	eMulType op;
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	ExprNode expr;
};

struct PrimaryExpr : public ExprNode {};

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
	PrimaryExpr lhs;
	IdentNode ident;
};

struct SubscriptNode : public PrimaryExpr {
	PrimaryExpr base;
	ExprNode subscript;
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	PrimaryExpr name;
	expr_list_t arguments;
};

struct CodeBlock : public StmtNode {
	stmt_list_t children;
};

struct Decl : StmtNode {
	VarType type;
	eReturnType value_type;
	std::string name;

	Decl() : type(eDeclType::ERROR) {}
	Decl(eDeclType t) : type(t) {}
	virtual ~Decl();
};

typedef std::vector<Decl> declarations_t;

struct VarDecl : public Decl {
	VarDecl() : Decl(eDeclType::VAR) {}
};

struct FunctionDecl : public Decl {
	bool is_event;
	std::vector<VarDecl> arguments;
	declarations_t locals;
	CodeBlock block;

	FunctionDecl() : Decl(eDeclType::FUNCTION) {}
};

struct ClassDecl : public Decl {
	std::string parent;
	declarations_t declarations;

	ClassDecl() : Decl(eDeclType::CLASS) {}
};

struct IfStmt :  public StmtNode {
	ExprNode condition;
	CodeBlock true_block;
	CodeBlock false_block;
};

struct WhileStmt :  public StmtNode {
	ExprNode condition;
	CodeBlock block;
};

struct ForStmt :  public StmtNode {
	ExprNode begin;
	ExprNode condition;
	ExprNode counter;
};

struct ReturnStmt :  public StmtNode {
	ExprStmt return_val;
};

struct ExprStmt :  public StmtNode {
	ExprNode expr;
};

struct Program {
	declarations_t declarations;
};

} //namespace ast
} // namespace nde


