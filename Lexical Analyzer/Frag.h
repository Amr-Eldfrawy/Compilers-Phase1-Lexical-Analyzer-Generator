#ifndef FRAG_H_INCLUDED
#define FRAG_H_INCLUDED
#include"State.h"

class Frag {
public:
	State *start;
	State * end;
	Frag();
	Frag(State * first, State* second);
};
#endif // FRAG_H_INCLUDED
