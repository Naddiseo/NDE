#pragma once
#include <vector>
#include <string>
#include "Script.hpp"

NDESCRIPT_NS_BEGIN
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


#define NODEFN(klass, var_name, enum_name)

#define NODETYPE \
	NODEFN(VarType, var_type, VARTYPE) \
	NODEFN(ExprNode, expr_node, EXPRNODE) \
	NODEFN(StmtNode, stmt_node, STMTNODE) \
	NODEFN(expr_list_t, expr_list, EXPRLIST) \
	NODEFN(stmt_list_t, stmt_list, STMTLIST) \
	NODEFN(EmptyExpression, empty_expression, EMPTYEXPRESSION) \
	NODEFN(BinaryExpr, bin_expr, BINEXPR) \
	NODEFN(TernaryExpr, ternary_expr, TERNARYEXPR) \
	NODEFN(UnaryExpr, unary_expr, UNARYEXPR) \
	NODEFN(PrimaryExpr, primary_expr, PRIMARYEXPR) \
	NODEFN(IdentNode, ident_node, IDENTNODE) \
	NODEFN(LiteralExpr, literal_expr, LITERALEXPR) \
	NODEFN(AttributeNode, attribute_node, ATTRIBUTENODE) \
	NODEFN(SubscriptNode, subscript_node, SUBSCRIPTNODE) \
	NODEFN(FunctionCall, function_call, FUNCTIONCALL) \
	NODEFN(CodeBlock, code_block, CODEBLOCK) \
	NODEFN(Decl, decl_node, DECLNODE) \
	NODEFN(VarDecl, var_decl, VARDECL) \
	NODEFN(declarations_t, declarations, DECLARATIONS) \
	NODEFN(vardecls_t, var_decls, VARDECLS) \
	NODEFN(FunctionDecl, function_decl, FUNCTIONDECL) \
	NODEFN(ClassDecl, class_decl, CLASSDECL) \
	NODEFN(IfStmt, if_stmt, IFSTMT) \
	NODEFN(WhileStmt, while_stmt, WHILESTMT) \
	NODEFN(ForStmt, for_stmt, FORSTMT) \
	NODEFN(ExprStmt, expr_stmt, EXPRSTMT) \
	NODEFN(ReturnStmt, return_stmt, RETURNSTMT) \
	NODEFN(ContinueStmt, continue_stmt, CONTINUESTMT)
#undef NODEFN

enum class eNodeType {

#define NODEFN(klass, var_name, enum_name) enum_name,
	NODETYPE
#undef NODEFN
};

#define NODEFN(klass, var_name, enum_name) class klass;
NODETYPE
#undef NODEFN

struct ASTNode {
	virtual ~ASTNode();

	union value_t {
#define NODEFN(klass, var_name, enum_name) klass* var_name;
		NODETYPE
#undef NODEFN
	};

	eNodeType type;
	value_t value;
#define NODEFN(klass, var_name, enum_name) ASTNode(klass* _v) : type(eNodeType::enum_name) { value.var_name = _v; }
	NODETYPE
#undef NODEFN
};

typedef std::vector<ASTNode*> node_list_t;

template<typename T>
class NodeList {
	typedef std::vector<T*> list_t;
	list_t nodes;
public:
	typedef typename std::vector<T*>::iterator iterator;

	~NodeList() {
		for (T* node : nodes) {
			delete node;
		}
	}

	void push_back(T* node) { nodes.push_back(node); }

	iterator begin() { return nodes.begin(); }
	iterator end() { return nodes.end(); }
};

struct VarType {
	eReturnType type;
	std::string class_name; // if type == OBJECT
	bool is_array;

	VarType() {}
	VarType(eReturnType _t) : type(_t) {}
	virtual ~VarType() {}
};

struct ExprNode {
	virtual ~ExprNode() {}
};
struct StmtNode {
	virtual ~StmtNode() {}
};

struct expr_list_t : public NodeList<ExprNode> {};
struct stmt_list_t : public NodeList<StmtNode> {};

struct EmptyExpression : public ExprNode {
	virtual ~EmptyExpression() {}
};

struct BinaryExpr : public ExprNode {
	eBinaryOp op;
	ASTNode* lhs;
	ASTNode* rhs;

	virtual ~BinaryExpr() {}

	BinaryExpr() : op(eBinaryOp::ERROR) {}
	BinaryExpr(eBinaryOp _o) : op(_o) {}
	BinaryExpr(ASTNode* _lhs, eBinaryOp _op, ASTNode* _rhs)
		: op(_op), lhs(_lhs), rhs(_rhs) {}
};

struct TernaryExpr : public ExprNode {
	ASTNode* condition;
	ASTNode* true_cond;
	ASTNode* false_cond;

	TernaryExpr(ASTNode* _c, ASTNode* _t, ASTNode* _f)
		: condition(_c), true_cond(_t), false_cond(_f) {}

	virtual ~TernaryExpr() {}
};

struct UnaryExpr : public ExprNode {
	eUnaryType op;
	ASTNode* expr;

	UnaryExpr(eUnaryType _o, ASTNode* _e)
		: op(_o), expr(_e) {}

	virtual ~UnaryExpr() {}
};

struct PrimaryExpr : public ExprNode {
	virtual ~PrimaryExpr() {}
};

struct IdentNode : public PrimaryExpr {
	std::string ident;

	IdentNode(std::string _i) : ident(_i) {}

	virtual ~IdentNode() {}
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

	virtual ~LiteralExpr() {}

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
	ASTNode* lhs;
	ASTNode* ident;

	AttributeNode(ASTNode* _l, ASTNode* _i)
		: lhs(_l), ident(_i) {}

	virtual ~AttributeNode() {}
};

struct SubscriptNode : public PrimaryExpr {
	ASTNode* base;
	ASTNode* subscript;
};

struct FunctionCall : public PrimaryExpr {
	bool is_trigger;
	ASTNode* name;
	ASTNode* arguments;
};

struct CodeBlock : public StmtNode {
	ASTNode* children;
};

struct Decl : StmtNode {
	ASTNode* type;
	eDeclType decl_type;
	eReturnType value_type;
	std::string* name;

	Decl() : decl_type(eDeclType::ERROR) {}
	Decl(eDeclType _t) : decl_type(_t) {}
	virtual ~Decl();
};

struct declarations_t : public NodeList<Decl> {};

struct VarDecl : public Decl {
	ASTNode* default_value;
	VarDecl() : Decl(eDeclType::VAR) {}
};

struct vardecls_t : public NodeList<VarDecl> {};

struct FunctionDecl : public Decl {
	bool is_event;
	ASTNode* arguments;
	ASTNode* block;

	FunctionDecl() : Decl(eDeclType::FUNCTION) {}
	FunctionDecl(ASTNode* args, ASTNode* b) : Decl(eDeclType::FUNCTION), is_event(false), arguments(args), block(b) {}
	FunctionDecl(bool i_e, ASTNode* args, ASTNode* b) : Decl(eDeclType::FUNCTION), is_event(i_e), arguments(args), block(b) {}
};

struct ClassDecl : public Decl {
	std::string parent;
	ASTNode* declarations;

	ClassDecl() : Decl(eDeclType::CLASS) {}
	ClassDecl(std::string _parent, ASTNode* _decls) : Decl(eDeclType::CLASS), parent(_parent), declarations(_decls) {}
};

struct IfStmt :  public StmtNode {
	ASTNode* condition;
	ASTNode* true_block;
	ASTNode* false_block;

	IfStmt() : condition(NULL), true_block(NULL), false_block(NULL) {}
	IfStmt(ASTNode* _cond, ASTNode* _true) : condition(_cond), true_block(_true), false_block(NULL) {}
	IfStmt(ASTNode* _cond, ASTNode* _true, ASTNode* _false) : condition(_cond), true_block(_true), false_block(_false) {}

	void passDown(ASTNode* block) {
		if (false_block == NULL) {
			false_block = block;
		}
		else {
			false_block->value.if_stmt->passDown(block);
		}
	}
};

struct WhileStmt :  public StmtNode {
	ASTNode* condition;
	ASTNode* block;

	WhileStmt(ASTNode* _cond, ASTNode* _block) : condition(_cond), block(_block) {}
};

struct ForStmt :  public StmtNode {
	ASTNode* begin;
	ASTNode* condition;
	ASTNode* counter;
	ASTNode* block;

	ForStmt(ASTNode* _begin, ASTNode* _cond, ASTNode* _counter, ASTNode* _block)
		: begin(_begin), condition(_cond), counter(_counter), block(_block) {}
};

struct ExprStmt :  public StmtNode {
	ASTNode* expr;

	ExprStmt(ASTNode* _expr) : expr(_expr) {}
};

struct ReturnStmt :  public StmtNode {
	ASTNode* return_val;

	ReturnStmt() : return_val(NULL) {}
	ReturnStmt(ASTNode* rv) : return_val(rv) {}
};

struct BreakStmt : public StmtNode {};
struct ContinueStmt : public StmtNode {};

struct Program {
	node_list_t declarations;
};

} //namespace ast
NDESCRIPT_NS_END


