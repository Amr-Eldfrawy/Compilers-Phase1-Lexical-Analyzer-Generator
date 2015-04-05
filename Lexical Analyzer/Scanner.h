
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "Token.h"

#include <iostream>
#include <stack>
#include <map>
#include <vector>
using namespace std;

class Scanner{
public :
	Scanner();
	map<string, string> strings;
	void parse(string a, int i);
	string make(string u);
	string solve(string a, int i);
	int del(string a, int i);
	string range(char start, char end);
	vector<Token> scan();
	void marks(string a , int i );
	string solveConc(string a);

};
#endif
