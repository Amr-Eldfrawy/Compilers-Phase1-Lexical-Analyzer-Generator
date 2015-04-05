#include "DFANode.h"

DFANode::DFANode() {
	id = group = 0;
	acc = false;
	token_priority = 0;
	matrix.clear();
}
