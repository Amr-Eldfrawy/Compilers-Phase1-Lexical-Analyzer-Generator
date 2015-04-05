#ifndef DFA_NODE_H
#define DFA_NODE_H

#include <map>

#include "State.h"
#include "Nfa.h"

class DFA_Node{
public:
	vector <State*> states_container;
	map <int, DFA_Node*> matrix;
	string token_name;
	int token_priority;
	int id;
	bool acc;
	DFA_Node();
};

#endif
