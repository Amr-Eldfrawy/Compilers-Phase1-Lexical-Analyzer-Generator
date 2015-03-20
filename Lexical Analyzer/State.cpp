#include "State.h"
#define EPSILON 256
#define GOAL 2
#include <iostream>

using namespace std;
bool vis[500];
State::State()
{
   out1=NULL;
   out2=NULL;
    edge1=EPSILON;
    edge2=EPSILON;


}
State::State( int _kind,int _edge1 , int _edge2 , State * first , State* second )
{
    kind = _kind;

    edge1 =_edge1;
    edge2 =_edge2;

    out1 = first;
    out2 = second;


}

void State::print(int depth)
{
    if(kind==GOAL || depth == 10 ){
        cout << "Goal  \n";
        return;
    }



    cout << "kind " << kind <<endl;
    cout << "edge1  " <<edge1 << "  edge2  " << edge2 <<endl;
    if(out1!=NULL)
        out1->print(depth+1);
    if(out2!=NULL)
        out2->print(depth+1);
}
