#include <map>
#include <set>
#include <queue>
#include <stdio.h>

#include "State.h"
#include "Nfa.h"
#include "DFA.h"
#include "DFANode.h"

DFA::DFA() {
	head = new DFANode();
	DFA::mapper.clear();
	init = false;
}

set<int> DFA::expand(set<State*>* vec) {
	queue<State*> q;
	set<int> init;
	set<State*>::iterator it;

	for (it = vec->begin();it!=vec->end();++it) {
		q.push(*it);
		init.insert((*it)->id);
	}

	while (!q.empty()) {
		State* c = q.front();
		q.pop();

		if (c->edge1 == 256) {
			if (c->out1 != NULL && init.find(c->out1->id) == init.end()) {
				vec->insert(c->out1);
				init.insert(c->out1->id);
				q.push(c->out1);
			}
		}
		if (c->edge2 == 256) {
			if (c->out2 != NULL && init.find(c->out2->id) == init.end()) {
				vec->insert(c->out2);
				init.insert(c->out2->id);
				q.push(c->out2);
			}
		}
	}
	return init;
}

DFA::DFA(Nfa* nfa_head) {
	DFA::head = new DFANode();
	mapper.clear();

	for (size_t i = 0; i < nfa_head->root.size(); i++)
		head->states_container.insert(nfa_head->root[i]);

	queue<DFANode*> q;

	q.push(DFA::head);
	set<int> cont;
	set<State*> vec;

	cont = expand(&(DFA::head->states_container));
	mapper[cont] = DFA::head;

	while (!q.empty()) {
		DFANode* c = q.front();
		q.pop();
		
		cont.clear();

		for (int l = 0; l < 256; l++) {
			set <State*>::iterator it;
			for (it = c->states_container.begin();it != c->states_container.end(); it++) {
				if ((*it)->edge1 == l) {
					if (cont.find((*it)->out1->id)
							== cont.end()) {
						cont.insert((*it)->out1->id);
						vec.insert((*it)->out1);
					}
				}
				if ((*it)->edge2 == l) {
					if (cont.find((*it)->out2->id)
							== cont.end()) {
						cont.insert((*it)->out2->id);
						vec.insert((*it)->out2);
					}
				}
			}
			//printf ("-letter %d checked\n", l);
			if (vec.size() == 0)
				continue;
			cont.clear();
			cont = expand(&vec);
			if (DFA::mapper.find(cont) == DFA::mapper.end()) {
				DFA::mapper[cont] = new DFANode();
				DFA::mapper[cont]->id = DFA::mapper.size()-1;
				printf ("%d\n", DFA::mapper[cont]->id);
				for (it = vec.begin();it != vec.end(); it++) {
					if ((*it)->kind == 2) {
						if ((*it)->priority
								>= DFA::mapper[cont]->token_priority) {
							DFA::mapper[cont]->token_priority =
									(*it)->priority;
							DFA::mapper[cont]->token_name = (*it)->token_name;
						}
						DFA::mapper[cont]->acc = true;
					}
				}
				q.push(DFA::mapper[cont]);
			}
			//printf ("--New node created\n");
			c->matrix[l] = DFA::mapper[cont];
			for (it = vec.begin();it != vec.end(); it++)
				DFA::mapper[cont]->states_container.insert(*it);
			//printf ("---%d Node data copied", DFA::mapper[cont]->states_container.size());
			cont.clear();
			vec.clear();
		}

	}

	init = true;
}
