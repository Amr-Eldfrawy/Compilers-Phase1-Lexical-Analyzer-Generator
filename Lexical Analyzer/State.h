#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include<iostream>

using namespace std;


class State
{
public:
    int kind ;
    char edge1;
    char edge2;
    State * out1;
    State * out2;

    State();
    State ( int _kind,char _edge1 , char _edge2 , State * first , State* second );
    void print();

};

#endif // STATE_H_INCLUDED
