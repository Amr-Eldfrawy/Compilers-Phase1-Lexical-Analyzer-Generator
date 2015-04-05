#ifndef DFA_H
#define DFA_H

#include "State.h"
#include "Nfa.h"
#include "DFANode.h"

#include <set>
#include <map>

class DFA{
	public:
	DFANode* head;
	bool init;
	map <set<int>, DFANode*> mapper;

	DFA ();
	DFA (Nfa* nfa_head);

	set<int> expand (set<State*>* vec);
	void dump();
};

#endif // DFA_H
