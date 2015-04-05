#include<iostream>
#include<string>
#include<stack>
#include<vector>

#define DEFAULT 0
#define EPSILON 256
#define SPLIT 1
#define GOAL 2

#include "Nfa.h"
#include "Frag.h"
#include "State.h"
#include"Scanner.h"
#include"Token.h"

using namespace std;

Nfa::Nfa() {
	curId = 0;
}
int Nfa::GenerateID() {
	curId++;
	return curId;
}
void Nfa::getNfaRoot() {
	Scanner x;
	vector<Token> tokens = x.scan();

	for (int i = 0; i < tokens.size(); i++)
		Nfa::root.push_back(
				postToNfa(tokens[i].rank, tokens[i].name, tokens[i].regex));

}

State* Nfa::postToNfa(int rank, string regexName, string postfix) {

	stack<Frag> fragStack;
	Frag e1, e2, e;
	for (int i = 0; i < postfix.size(); i++) {
		char cur = postfix[i];

		if (cur == '`') {
			e2 = fragStack.top();
			fragStack.pop();
			e1 = fragStack.top();
			fragStack.pop();

			e1.end->kind = DEFAULT;
			e1.end->out1 = e2.start;

			fragStack.push(Frag(e1.start, e2.end));
		}

		else if (cur == '|') {
			e2 = fragStack.top();
			fragStack.pop();
			e1 = fragStack.top();
			fragStack.pop();

			State * s = new State(SPLIT, EPSILON, EPSILON, e1.start, e2.start);
			State * End = new State(GOAL, EPSILON, EPSILON, NULL, NULL);

			e1.end->kind = DEFAULT;
			e2.end->kind = DEFAULT;

			e1.end->out1 = End;
			e2.end->out1 = End;

			fragStack.push(Frag(s, End));
		} else if (cur == '*') {
			e = fragStack.top();
			fragStack.pop();
			State * end = new State(GOAL, EPSILON, EPSILON, NULL, NULL);
			State * s = new State(SPLIT, EPSILON, EPSILON, e.start, end);

			e.end->kind = DEFAULT;
			e.end->out1 = s;

			fragStack.push(Frag(s, end));
		} else if (cur == '+') {
			e = fragStack.top();
			fragStack.pop();
			State * end = new State(GOAL, EPSILON, EPSILON, NULL, NULL);
			State * s = new State(SPLIT, EPSILON, EPSILON, e.start, end);
			e.end->kind = DEFAULT;
			e.end->out1 = s;

			fragStack.push(Frag(e.start, end));
		} else {
			if (cur == '\\')
				cur = postfix[++i];

			State * end = new State(GOAL, EPSILON, EPSILON, NULL, NULL);
			State * s = new State(DEFAULT, cur, EPSILON, end, NULL);
			fragStack.push(Frag(s, end));
		}

	}

	e = fragStack.top();
	// cout << e.start->kind << " " << e.end->kind <<endl;
	fragStack.pop();

	e.end->priority = rank;
	e.end->token_name = regexName;

	return (e.start);
}
