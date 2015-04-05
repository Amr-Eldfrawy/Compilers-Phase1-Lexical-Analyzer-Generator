/*
 * Parser.h
 *
 *  Created on: Mar 20, 2015
 *      Author: mostafa
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "DFA.h"

class Parser {
public:
	Parser(DFA* fromEssam);
	DFA* dfa;
	void read();
	// bool solve(DFA_Node* u, int i);
	virtual ~Parser();
};

#endif /* PARSER_H_ */
