#include <iostream>
#include<string>
#include <stdio.h>
#include <set>
#include <queue>
#include <stdlib.h>

#include "Nfa.h"
#include "State.h"
#include "Frag.h"
#include "State.cpp"
#include "Frag.cpp"
#include "Nfa.cpp"
#include "DFA.cpp"
#include "DFA.h"
#include "DFANode.h"
#include "DFANode.cpp"
#include "Token.h"
#include "Token.cpp"
#include "Scanner.h"
#include "Scanner.cpp"
#include "DFAMinimizer.h"
#include "DFAMinimizer.cpp"


using namespace std;

void dump (DFA* dfa){
	
	DFANode *dfa_node = dfa->head;
	set <int> s;
	queue <DFANode*> q;
	q.push(dfa_node);
	
	set <State*>::iterator it;

	while (!q.empty()){
		DFANode* c = q.front();
		q.pop();

		if (s.find (c->id) != s.end())
			continue;

		s.insert (c->id);

		if (c->acc)
			printf ("Accepting ");

		printf ("%d:\n", c->id);
		printf ("##\n");

		printf ("{");
		for (it=c->states_container.begin();it!=c->states_container.end();it++){
			if (it != c->states_container.begin())
				printf (", ");
			printf ("%d", (*it)->id);
		}
		printf ("}\n");

		for (int i=0;i<256;i++){
			if (c->matrix.find(i) != c->matrix.end()){
				printf ("%c %d\n", (char)i, c->matrix[i]->id);
				q.push(c->matrix[i]);
			}
		}
		
		//system ("pause");

	}
}

int main()
{
    //Nfa* s = new Nfa();
    Nfa* a = new Nfa();

    //State* x = a->postToNfa("ab|*a.b.b.");
    //State* x = a->postToNfa("ab.b.cb.b.|");
    //State* y = a->postToNfa("ab.b.cb.b.|");

    //vector <State*> v;
    //v.push_back(x);
    //v.push_back(y);

    //a->root = v;

	//a->getNfaRoot();
	
	State* x = a->postToNfa(0, "7amada", "ab`b`cb`b`|");
	vector <State*> v;
	v.push_back(x);
	
	x->print(10);
	
	a->root = v;

	printf ("NFA ready\n");
    DFA* dfa = new DFA(a);
	printf ("%d\n", dfa->mapper.size());

	//x->print(10);

	dump (dfa);

   // y->print();

	cout << "OLD CODE OFF\n";

	DFAMinimizer* mini = new DFAMinimizer(dfa);
	dfa = mini->minimize();

	dump (dfa);

    return 0;
}
