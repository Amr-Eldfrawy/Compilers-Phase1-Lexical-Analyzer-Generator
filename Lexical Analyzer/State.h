#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include<iostream>

using namespace std;


class State
{
public:
    int kind ;
    int edge1;
    int edge2;
    State * out1;
    State * out2;

    State();
    State ( int _kind,int _edge1 , int _edge2 , State * first , State* second );
    void print(int depth);

};

#endif // STATE_H_INCLUDED
