#include "ASTVisitor.hpp"
#include "ASTree.hpp"
NDESCRIPT_NS_BEGIN
namespace ast {

void
Visitor::walk(Node* _node) {
	switch (_node->type) {
#define SWITCH_WALK(klass, var_name, enum_name) case eNodeType::enum_name: { walk(_node->var_name); } break;
	NODETYPE(SWITCH_WALK)
	default: break;
	}
}


} // namespace ast
NDESCRIPT_NS_END
