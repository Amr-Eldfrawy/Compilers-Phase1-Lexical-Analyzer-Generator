#include <iostream>
#include<string>

#include "Nfa.h"
#include "State.h"
#include "Frag.h"
#include "State.cpp"
#include "Frag.cpp"
#include "Nfa.cpp"



using namespace std;

int main()
{
    //Nfa* s = new Nfa();
    Nfa a;
    a.postToNfa("ab|")->print();



    return 0;
}
