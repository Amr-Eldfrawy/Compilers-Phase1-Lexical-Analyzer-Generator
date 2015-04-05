#ifndef DFAMinimizer_H
#define DFAMinimizer_H

#include "DFA.h"
#include "DFANode.h"
//#include "DFANode.cpp"

#include <vector>
using namespace std;

class DFAMinimizer{
	public:
		vector <set <DFANode*> > groups;
		DFA* dfa;
		bool init;
		DFAMinimizer ();
		DFAMinimizer (DFA* dfa);
		DFA* minimize();
		void destroy();
};

#endif
