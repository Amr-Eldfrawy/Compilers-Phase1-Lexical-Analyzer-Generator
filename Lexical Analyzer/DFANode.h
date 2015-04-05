#ifndef DFANode_H
#define DFANode_H

#include "State.h"
#include "Nfa.h"

#include <set>
#include <map>

class DFANode{
public:
	set <State*> states_container;
	map <int, DFANode*> matrix;
	string token_name;
	int token_priority;
	int id, group;
	bool acc;
	DFANode();
};

#endif
