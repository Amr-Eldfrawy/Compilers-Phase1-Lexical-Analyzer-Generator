#define EPSILON 256
#define GOAL 2
#include <iostream>

#include "State.h"
#include "Nfa.h"
using namespace std;

State::State() {
	//int c =++Nfa::curId;
	id = Nfa::GenerateID();
	out1 = NULL;
	out2 = NULL;
	edge1 = EPSILON;
	edge2 = EPSILON;

}
State::State(int _kind, int _edge1, int _edge2, State * first, State* second) {
	//int c= ++Nfa::curId;
	id = Nfa::GenerateID();

	kind = _kind;
	edge1 = _edge1;
	edge2 = _edge2;

	out1 = first;
	out2 = second;

}

void State::print(int depth) {
	if (kind == GOAL || depth == 0) {
		cout << "Goal  \n";
		cout << priority << " .... " << token_name << endl;
		return;
	}

	// cout << "kind " << kind  << " id " << id <<endl;

	//if(edge1 != EPSILON)
	//cout <<  "kind " << kind  << " id " << id << " edge1  " <<edge1 << "  edge2  " << edge2 <<endl;
	cout << id << endl;
	if (out1 != NULL)
		cout << edge1 << " " << out1->id << endl;
	if (out2 != NULL)
		cout << edge2 << " " << out2->id << endl;
	if (out1 != NULL)
		out1->print(depth - 1);
	if (out2 != NULL)
		out2->print(depth - 1);
}
