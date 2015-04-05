#include"Frag.h"

Frag::Frag() {
	Frag::start = NULL;
	Frag::end = NULL;
}
Frag::Frag(State * first, State* second) {
	Frag::start = first;
	Frag::end = second;
}

