#ifndef NFA_H
#define NFA_H

#include "State.h"
#include <iostream>
#include <vector>

using namespace std;

class Nfa
{
public:
    vector <State*> root;
    Nfa();

    State* postToNfa(string postfix);
    vector <State*> getNfaRoot(vector <string> allPosifix);

};

#endif // NFA_H
