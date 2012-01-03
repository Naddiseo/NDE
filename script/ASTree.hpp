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

struct ExprNode {};
typedef std::vector<ExprNode> expr_list_t;

struct Expression : public ExprNode {
	expr_list_t children;
};

struct EmptyExpression : public ExprNode {};

struct ConditionalExpr : public Expression {};
struct OrExpr : public Expression {};
struct AndExpr : public Expression {};
struct NotExpr : public Expression {};
struct ComparisonExpr : public Expression {};


struct Decl {
	eDeclType type;
	eReturnType value_type;
	std::string name;

	Decl() : type(eDeclType::ERROR) {}
	Decl(eDeclType t) : type(t) {}
	virtual ~Decl();

};

struct VarDecl : public Decl {
	VarDecl() : Decl(eDeclType::VAR) {}
};

struct FunctionDecl : public Decl {
	std::vector<VarDecl> arguments;

	FunctionDecl() : Decl(eDeclType::FUNCTION) {}
};

struct Program {
	std::vector<Decl> declarations;
};

} //namespace ast
} // namespace nde


