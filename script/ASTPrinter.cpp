#include "script/ASTPrinter.hpp"

NDESCRIPT_NS_BEGIN
namespace ast {

static const char* binop_map[] = {
	"error",
	"=", "|=", "&=", "^=", "<<=", ">>=", "+=", "-=", "*=", "/=", "%=",
	">", "<", "<=", ">=", "<<", ">>",
	"+", "-", "*", "/", "%", "||", "&&", "|", "&", "^", "==", "!="
};

static const char* uop_map[] = {
	"~", "!", "++", "--", "-"
};

ASTPrinter::ASTPrinter() : tabs(0) {}

ASTPrinter::~ASTPrinter() {}
void
ASTPrinter::tab() {
	for (size_t i = 0; i < tabs; i++) {
		std::cout << "\t";
	}
}

void
ASTPrinter::print(Node* _node) {
	switch (_node->type) {
#define SWITCH_PRINT(klass, var_name, enum_name) case eNodeType::enum_name: { print(_node->var_name); } break;
	NODETYPE(SWITCH_PRINT)
	default: break;
	}
}

//#define PRINT(klass, var_name, enum_name) void ASTPrinter::print(klass* _node) { }
//NODETYPE(PRINT)
void ASTPrinter::print(VarType* _node) {
	if (_node->type == eReturnType::OBJECT) {
		std::cout << _node->class_name;
	}
	else {
		std::cout << _node->type;
	}
}

void ASTPrinter::print(ExprNode* _node) { std::cerr << "Printing EXPRNODE"; }
void ASTPrinter::print(StmtNode* _node) { std::cerr << "Printing STMTNODE"; }

void ASTPrinter::print(expr_list_t* _node) {
	printlist(_node);
}
void ASTPrinter::print(stmt_list_t* _node) {
	printlist(_node, ";\n", true, true);
}

void ASTPrinter::print(EmptyExpression* _node) {}
void ASTPrinter::print(BinaryExpr* _node) {
	std::cout << "(";
		print(_node->lhs);
	std::cout << ")" << binop_map[static_cast<char>(_node->op)] << "(";
		print(_node->rhs);
	std::cout << ")";

}
void ASTPrinter::print(TernaryExpr* _node) {
	std::cout << "(";
		print(_node->condition);
	std::cout << " ? ";
		print(_node->true_cond);
	std::cout << " : ";
		print(_node->false_cond);
	std::cout << ")";
}

void ASTPrinter::print(UnaryExpr* _node) {
	std::cout << uop_map[static_cast<char>(_node->op)] << "(";
		print(_node->expr);
	std::cout << ")";
}

void ASTPrinter::print(PrimaryExpr* _node) { std::cerr << "Empty primary expr"; }

void ASTPrinter::print(IdentNode* _node) {
	std::cout << _node->ident << " ";
}

void ASTPrinter::print(LiteralExpr* _node) {
	std::cout << "(";
	switch (_node->type) {
	case eLiteralType::STRINGVAL:
		std::cout << '"' << _node->str_val << '"';
		break;
	case eLiteralType::FLOATVAL:
		std::cout << _node->flt_val << "f";
		break;
	case eLiteralType::INTVAL:
		std::cout << _node->int_val << "i";
		break;
	case eLiteralType::BOOLVAL:
		std::cout << _node->bool_val << "b";
		break;
	case eLiteralType::VECTORVAL:
	default:
		break;
	}

	std::cout << ")";
}

void ASTPrinter::print(AttributeNode* _node) {
	std::cout << "(";
		print(_node->lhs);
	std::cout << ".";
	print(_node->ident);
	std::cout << ")";
}

void ASTPrinter::print(SubscriptNode* _node) {

	std::cout << "(";
	print(_node->base);
	std::cout << "[";
	print(_node->subscript);
	std::cout << "])";
}

void ASTPrinter::print(FunctionCall* _node) {

	if (_node->is_trigger) {
		std::cout << "trigger ";
	}
	print(_node->name);
	std::cout << "(";
	print(_node->arguments);
	std::cout << ")";
}

void ASTPrinter::print(CodeBlock* _node) {

	std::cout << " {" << std::endl;
	tabs++;
	if (_node->children) {
		print(_node->children);
	}
	tabs--;
	tab();
	std::cout << "}" << std::endl;
}

void ASTPrinter::print(Decl* _node) {

	print(_node->return_type);
	std::cout << " " <<_node-> name;
	if (_node->return_type->var_type->is_array) {
		std::cout << "[]";
	}
}

void ASTPrinter::print(VarDecl* _node) {

	print((Decl*)_node);
	if (_node->default_value) {
		std::cout << " = ";
		print(_node->default_value);
	}
}

void ASTPrinter::print(declarations_t* _node) {
	printlist_callback_t callback = [](Node* _node, bool is_last, std::string sep, bool print_last) {
		if (_node->decl_node->decl_type == eDeclType::VAR) {
			std::cout << ";\n";
		}

	};
	printlist(_node, "\n", true, true, callback);
}

void ASTPrinter::print(vardecls_t* _node) {
	printlist(_node, ", ");
}

void ASTPrinter::print(FunctionDecl* _node) {
	if (_node->is_event) {
		std::cout << "event ";
	}
	print((Decl*)_node);
	std::cout << "(";
	print(_node->arguments);
	std::cout << ")";
	print(_node->block);
}

void ASTPrinter::print(ClassDecl* _node) {

	std::cout << "class ";
	//Decl::print(); // return type is null
	std::cout << _node->name;
	if (_node->parent.size()) {
		std::cout << " : " << _node->parent;
	}
	std::cout << " {" << std::endl;
	tabs++;
	print(_node->declarations);
	tabs--;
	tab();
	std::cout << std::endl << "}" << std::endl;
}

void ASTPrinter::print(IfStmt* _node) {

	std::cout << "if (";
	print(_node->condition);
	std::cout << ")";
	print(_node->true_block);
	tab();
	std::cout << " else ";
	print(_node->false_block);
}

void ASTPrinter::print(WhileStmt* _node) {
	std::cout << "while (";
	print(_node->condition);
	std::cout << ")";
	print(_node->block);

}

void ASTPrinter::print(ForStmt* _node) {
	std::cout << "for (";
	print(_node->begin);
	std::cout << ";";
	print(_node->condition);
	std::cout << ";";
	print(_node->counter);
	std::cout << ")";
	print(_node->block);
}

void ASTPrinter::print(ExprStmt* _node) {

	print(_node->expr);
}

void ASTPrinter::print(ReturnStmt* _node) {

	std::cout << "return (";
	print(_node->return_val);
	std::cout << ")";
}

void ASTPrinter::print(ContinueStmt* _node) {
	std::cout << "continue";
}

void ASTPrinter::print(BreakStmt* _node) {
	std::cout << "break";
}

} // namespace nde

NDESCRIPT_NS_END
