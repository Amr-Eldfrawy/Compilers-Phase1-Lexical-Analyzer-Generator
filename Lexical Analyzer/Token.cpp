
#include "Token.h"
#include "Scanner.h"
using namespace std;

Token::Token()
{

}

Token::Token(string _name,string _regex,int _rank)
{
	name = _name;
	regex = _regex;
	rank = _rank;
}
