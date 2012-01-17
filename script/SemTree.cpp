#include "SemTree.hpp"
#include <iostream>
#include "ASTree.hpp"

NDESCRIPT_NS_BEGIN
namespace sem {

#define ASSERT(__expr, msg) { if (!(__expr)) { sem_error(msg); } };

SymbolEntry::SymbolEntry() : level(0) {}

SymbolEntry::SymbolEntry(pClassDecl k)
	: symtype(CLASS), klass(k), level(0) {}

SymbolEntry::SymbolEntry(pVarDecl v)
	: symtype(VARIABLE), var(v), level(0) {}

SymbolEntry::SymbolEntry(pFunctionDecl f)
	: symtype(FUNCTION), func(f), level(0) {}

SymbolEntry::SymbolEntry(pClassDecl k, size_t _level)
	: symtype(CLASS), klass(k), level(_level) {}

SymbolEntry::SymbolEntry(pVarDecl v, size_t _level)
	: symtype(VARIABLE), var(v), level(_level) {}

SymbolEntry::SymbolEntry(pFunctionDecl f, size_t _level)
	: symtype(FUNCTION), func(f), level(_level) {}

SymbolEntry::~SymbolEntry() {}

//std::map<std::string, pSymbolEntry> sym_map;

SymbolTable::~SymbolTable() {}

void SymbolTable::pushScope() {
	level++;
}
void SymbolTable::popScope() {

	for (std::pair<std::string, pSymbolEntry> entry : sym_map) {
		pSymbolEntry current = entry.second;
		if (current->level == level) {
			if (current->next ) {
				current->next->prev.reset();
				sym_map[entry.first] = current->next;
			}
			else {
				if (sym_map.find(entry.first) != sym_map.end()) {
				//TODO: sym_map.erase(entry.first);
				}
			}
		}
	}

	level--;
}

void SymbolTable::pushSymbol(std::string sym, pSymbolEntry& e) {
	e->level = level;
	if (sym_map.find(sym) != sym_map.end()) {
		pSymbolEntry current = sym_map[sym];
		e->next = current;
		current->prev = e;
	}

	sym_map[sym] = e;
}

void
SymbolTable::pushSymbol(std::string sym, pClassDecl& k) {
	pSymbolEntry e(new SymbolEntry(k, level));

	pushSymbol(sym, e);
}

void
SymbolTable::pushSymbol(std::string sym, pVarDecl& v) {
	pSymbolEntry e(new SymbolEntry(v, level));

	pushSymbol(sym, e);
}

void
SymbolTable::pushSymbol(std::string sym, pFunctionDecl& f) {
	pSymbolEntry e(new SymbolEntry(f, level));
	pushSymbol(sym, e);
}


ClassDecl::~ClassDecl() {}

Program::~Program() {}

void
Program::walk(ast::Node* _node) {
	switch (_node->type) {
#define SWITCH_WALK(klass, var_name, enum_name) case ast::eNodeType::enum_name: { walk(_node->var_name); } break;
	NODETYPE(SWITCH_WALK)
	default: break;
	}
}

void
Program::walk(ast::Program* prog) {
	if (prog->declarations == NULL) {
		return;
	}

	ast = prog;

	for (ast::Node* decl : *prog->declarations->declarations) {
		switch (decl->type) {
		case ast::eNodeType::VARDECL: {
			pVarDecl var(new VarDecl());
			walk(decl->var_decl, var);

			global_vars.push_back(var);
		};
			break;
		case ast::eNodeType::FUNCTIONDECL: {
			pFunctionDecl f(new FunctionDecl());
			walk(decl->function_decl, f);

			global_functions.push_back(f);
		};
			break;
		case ast::eNodeType::CLASSDECL: {
			pClassDecl k(new ClassDecl());
			walk(decl->class_decl, k);

			classes.push_back(k);
		};
			break;
		default:
			std::cerr << "Unknown type " << decl->type << std::endl;
			break;
		}

	}
}

void Program::walk(ast::VarType* _node) {}
void Program::walk(ast::ExprNode* _node) {}
void Program::walk(ast::StmtNode* _node) {}
void Program::walk(ast::expr_list_t* _node) {}
void Program::walk(ast::stmt_list_t* _node) {}
void Program::walk(ast::EmptyExpression* _node) {}
void Program::walk(ast::BinaryExpr* _node) {}
void Program::walk(ast::TernaryExpr* _node) {}
void Program::walk(ast::UnaryExpr* _node) {}
void Program::walk(ast::PrimaryExpr* _node) {}
void Program::walk(ast::IdentNode* _node) {}
void Program::walk(ast::LiteralExpr* _node) {}
void Program::walk(ast::AttributeNode* _node) {}
void Program::walk(ast::SubscriptNode* _node) {}
void Program::walk(ast::FunctionCall* _node) {}
void Program::walk(ast::CodeBlock* _node) {}
void Program::walk(ast::Decl* _node) {}
void Program::walk(ast::VarDecl* _node, pVarDecl var) {
	ASSERT(_node->get_return_type() != ast::eReturnType::VOID, "Variables cannot be declared void");

	var->name = _node->name;
	var->is_array = _node->is_array();
	var->return_type = _node->get_return_type();
	var->ast = _node;

	symtab.pushSymbol(var->name, var);

}

void Program::walk(ast::declarations_t* _node) {}
void Program::walk(ast::vardecls_t* _node) {}
void Program::walk(ast::FunctionDecl* _node, pFunctionDecl func) {
	func->name = _node->name;
	func->ast = _node;

	symtab.pushSymbol(func->name, func);
	symtab.pushScope();
	// grab args
	// do code block

	symtab.popScope();
}

void Program::walk(ast::ClassDecl* _node, pClassDecl klass) {

	klass->name = _node->name;
	klass->ast = _node;


	symtab.pushSymbol(klass->name, klass);

	symtab.pushScope();
	for (ast::Node* decl : *_node->declarations->declarations) {
		switch (decl->type) {
		case ast::eNodeType::VARDECL: {
			pVarDecl var(new VarDecl());
			walk(decl->var_decl, var);

			klass->vars.push_back(var);
		};
			break;
		case ast::eNodeType::FUNCTIONDECL: {
			pFunctionDecl func(new FunctionDecl());
			walk(decl->function_decl, func);

			klass->funcs.push_back(func);
		};
			break;
		case ast::eNodeType::CLASSDECL: {
			std::cerr << "Classes cannot contain other classes" << std::endl;
		};
			break;
		default:
			std::cerr << "Unknown type " << decl->type << std::endl;
			break;
		}
	}
	symtab.popScope();

}

void Program::walk(ast::IfStmt* _node) {}
void Program::walk(ast::WhileStmt* _node) {}
void Program::walk(ast::ForStmt* _node) {}
void Program::walk(ast::ExprStmt* _node) {}
void Program::walk(ast::ReturnStmt* _node) {}
void Program::walk(ast::ContinueStmt* _node) {}
void Program::walk(ast::BreakStmt* _node) {}


void
Program::sem_error(std::string msg) {
	std::cerr << "Semantic Error: " << msg << std::endl;
}

} // namespace sem
NDESCRIPT_NS_END
