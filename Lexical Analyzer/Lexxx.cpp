//============================================================================
// Name        : Lexxx.cpp
// Author      : Mostafa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DFA.h"
#include "DFAMinimizer.h"
#include "DFANode.h"
#include "Frag.h"
#include "Nfa.h"
#include "Parser.h"
#include "Scanner.h"
#include "State.h"
#include "Token.h"
#include "DFA.cpp"
#include "DFAMinimizer.cpp"
#include "DFANode.cpp"
#include "Frag.cpp"
#include "Nfa.cpp"
#include "Parser.cpp"
#include "Scanner.cpp"
#include "State.cpp"
#include "Token.cpp"


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
			printf ("Token %s Accepting ", c->token_name.c_str());

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



int main() {

	Nfa a;
	a.getNfaRoot();
	cout << a.root.size() << endl;
	DFA* dfa = new DFA(&a);
	DFAMinimizer* mini = new DFAMinimizer(dfa);
	dfa = mini->minimize();
	
	//dump (dfa);
	
	Parser* p = new Parser(dfa);
	p->read();

	//cout << "Hello UPC World" << endl; // prints Hello UPC World
	return 0;
}
