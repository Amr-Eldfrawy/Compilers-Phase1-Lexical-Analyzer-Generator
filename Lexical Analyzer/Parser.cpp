/*
 * Parser.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: mostafa
 */

#include <cstdio>

#include "DFA.h"
#include "DFANode.h"
#include "Frag.h"
#include "Nfa.h"
#include "Parser.h"
#include "State.h"

Parser::Parser(DFA* fromEssam) {
	// TODO Auto-generated constructor stub
	dfa = fromEssam;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::read() {
	freopen("input.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	bool cont = true;
	while (cont) {
		char in[1000];
		int len = 0;
		while (true) {
			in[len++] = getchar();
			//scanf("%c", &input[len++]);
			if (in[len - 1]
					== ' '|| in[len - 1] == '\t'|| in[len - 1] == '\n' || in[len - 1] == EOF) {
				cont = in[len - 1] != EOF;
				break;
			}
		}
		for (int i = 0; i < len; i++) {
			if (in[i] == ' ' || in[i] == '\t' || in[i] == '\n' || in[i] == EOF)
				continue;
			int lastAc = -1;
			int j = i;
			DFANode* u = Parser::dfa->head;
			while (j < len && in[j] != ' ') {
				u = u->matrix[in[j]];
				if (u == NULL)
					break;
				if (u->acc)
					lastAc = j;
				j++;
			}
			if (lastAc != -1) {
				u = Parser::dfa->head;
				for (j = i; j <= lastAc; j++)
					u = u->matrix[in[j]];
				cout << u->token_name << endl;
				i = lastAc;
			} else {
				cout << "Error" << endl;
				break;
			}
		}
	}
//Parser::solve(Parser::dfa->head, 0);
}

