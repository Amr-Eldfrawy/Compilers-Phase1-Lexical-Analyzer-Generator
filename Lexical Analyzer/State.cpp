#include "State.h"
#define EPSILON 256
#define GOAL 2
#include <iostream>

using namespace std;
State::State()
{
    State::out1=NULL;
    State::out2=NULL;
    State::edge1=EPSILON;
    State::edge2=EPSILON;

}
State::State( int _kind,int _edge1 , int _edge2 , State * first , State* second )
{
    State::kind = _kind;

    State::edge1 =_edge1;
    State::edge2 =_edge2;

    State::out1 = first;
    State::out2 = second;


}

void State::print()
{
    if(kind==GOAL || (out1==NULL && out2==NULL) )
        return;

    cout << kind <<endl;
    cout << "edge1  " <<edge1 << "  edge2  " << edge2 <<endl;

    out1->print();
    out2->print();
}
