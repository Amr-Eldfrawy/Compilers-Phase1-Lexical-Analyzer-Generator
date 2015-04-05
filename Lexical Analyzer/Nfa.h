#ifndef NFA_H
#define NFA_H

#include "State.h"
#include <iostream>
#include <vector>

using namespace std;

static int curId = 0;

class Nfa {
public:

	vector<State*> root;
	Nfa();

	static int GenerateID();
	State* postToNfa(int rank, string regexName, string postfix);
	void getNfaRoot();

};

#endif // NFA_H
