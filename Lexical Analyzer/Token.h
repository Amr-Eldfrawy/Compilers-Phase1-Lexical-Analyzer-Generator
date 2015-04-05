#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include <string>


using namespace std;

class Token{

public :
	int rank;
	string name;
	string regex;
	Token();
	Token(string _name,string _regex,int _rank);

};



#endif
