#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include <vector>

#include "Token.h"
#include "Scanner.h"

using namespace std;
#define MAX 999999
vector<Token> t;

string Scanner::range(char start, char end) {
	string ans = "";
	ans = ans + start;
	for (char w = start + 1; w <= end; w++) {
		ans = ans + w + "|";
	}
	return ans;
}
int Scanner::del(string a, int i) {
	while (i < (int) a.size() && a[i] == ' ')
		i++;
	return i;
}

string Scanner::solve(string a, int i) {
	string u = "";
	i = del(a, i);
	string ret = "";
	string val1 = "", val2 = "";
	stack<char> stack;
	while (i < (int) a.size()) {
		val1 = val2 = "";
		if (a[i] == '\\') {
			if (a[i + 1] == 'L') {
				i += 2;
				val1 = val1 + "\\" + "^";
			} else if (a[i + 1] == '\\') {
				i += 2;
				val1 = val1 + "\\" + "\\";
			} else if (a[i + 1] == '*') {
				i += 2;
				val1 = val1 + "\\" + "*";
			} else if (a[i + 1] == '+') {
				i += 2;
				val1 = val1 + "\\" + "+";
			} else if (a[i + 1] == '|') {
				i += 2;
				val1 = val1 + "\\" + "|";
			} else {
				val1 = val1 + a[i + 1];
				i += 2;
			}
		} else if (a[i] == '>' || a[i] == '<' || a[i] == '!' || a[i] == '/') {
			val1 = val1 + a[i];
			i++;
		} else if (a[i] == '.') {
			if (!stack.empty())
				while (stack.top() == '+' || stack.top() == '*') {
					u = u + stack.top() + "";
					stack.pop();
					if (stack.empty())
						break;
				}
			u = u + ".";
			stack.push('`');
			stack.push('`');
			i++;
			continue;
			/*      }else if(!((a[i] >= 'a' && a[i] <= 'z')
			 || (a[i] >= 'A' && a[i] <= 'Z')
			 || (a[i] >= '0' && a[i] <= '9'))){
			 val1  = val1  + a[i];
			 */
		} else {
			while (i < (int) a.size()
					&& ((a[i] >= 'a' && a[i] <= 'z')
							|| (a[i] >= 'A' && a[i] <= 'Z')
							|| (a[i] >= '0' && a[i] <= '9'))) {
				val1 = val1 + a[i++];
			}
		}
		if (val1 == "E") {
			u = u + val1;
			continue;
		}
		i = del(a, i);
		if (a[i] == '-') {
			i++;
			i = del(a, i);
			while (i < (int) a.size()
					&& ((a[i] >= 'a' && a[i] <= 'z')
							|| (a[i] >= 'A' && a[i] <= 'Z')
							|| (a[i] >= '0' && a[i] <= '9'))) {
				val2 = val2 + a[i++];
			}
			val1 = range(val1[0], val2[0]);
			i = del(a, i);
		}
		if (strings.find(val1) != strings.end()) {
			val1 = strings[val1];
		}
		char t = a[i];
		u = u + val1;
//		if (stack.empty()) {
//			if(t == )
//			stack.push(t);
//			continue;
//		}
		/*
		 * 		 (  ) 	{*, + }  . |
		 * */
		if (t == '|') {
			i++;
			if (!stack.empty())
				while (stack.top() == '+' || stack.top() == '*'
						|| stack.top() == '`' || stack.top() == '|') {
					u = u + stack.top() + "";
					stack.pop();
					if (stack.empty())
						break;
				}
			// `
			stack.push(t);
		} else if (t == '.') {
			if (!stack.empty())
				while (stack.top() == '+' || stack.top() == '*') {
					u = u + stack.top() + "";
					stack.pop();
					if (stack.empty())
						break;
				}
			u = u + t;
			i++;
			stack.push('`');
			stack.push('`');
		} else if (t == '(') {
			if (val1 != "") {
				stack.push('`');
			}
			stack.push(t);
			i++;
		} else if (t == ')') {
			while (stack.top() != '(') {
				u = u + stack.top() + "";
				stack.pop();
				if (stack.empty())
					break;
			}
			if (!stack.empty())
				stack.pop();
			i++;
		} else if (t == '*' || t == '+') {
			u = u + t;
			i++;
		} else {
			if (!stack.empty())
				while (stack.top() == '+' || stack.top() == '*') {
					u = u + stack.top() + "";
					stack.pop();
					if (stack.empty())
						break;
				}
			if (i != (int) a.size()) {
				stack.push('`');
			}
		}
		i = del(a, i);
	}

	while (!stack.empty()) {
		u = u + stack.top() + "";
		stack.pop();
	}
	return u;
}

string Scanner::make(string u) {
	if (u.size() == 0)
		return u;
	string ans = "";
	int i = 1;
	ans = ans + u[0];
	while (i < (int) u.size())
		ans = ans + u[i++] + "`";
	return ans;
}
void Scanner::parse(string a, int i) {
	string u = "";
	while (i < (int) a.size()) {
		u = "";
		i = del(a, i);
		while (i < (int) a.size()
				&& ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z')
						|| (a[i] >= '0' && a[i] <= '9'))) {
			u = u + a[i++];
		}
		i = del(a, i);
		t.push_back(Token(u, make(u), MAX));

		if (i >= (int) a.size() || a[i] == '}')
			break;
	}
}

void Scanner::marks(string a, int i) {
	string val1 = "", val = "";
	while (i < a.size() - 1) {
		i = del(a, i);
		val1 = val = "";
		if (i + 1 > a.size())
			return;
		if (a[i] == '\\') {
			if (i + 1 > a.size())
				return; // error
			if (a[i + 1] == 'L') {
				i += 2;
				val = val + "\\" + "^";
				val1 = val1 + "\\" + "^";
			} else if (a[i + 1] == '\\') {
				i += 2;
				val = val + "\\";
				val1 = val1 + "\\" + "\\";
			} else if (a[i + 1] == '*') {
				i += 2;
				val = val + "*";
				val1 = val1 + "\\" + "*";
			} else if (a[i + 1] == '+') {
				val = val + "+";
				i += 2;
				val1 = val1 + "\\" + "+";
			} else if (a[i + 1] == '|') {
				i += 2;
				val = val + "|";
				val1 = val1 + "\\" + "|";
			} else {
				val = val + a[i + 1];
				val1 = val1 + "\\" + a[i + 1];
				i += 2;
			}
			t.push_back(Token(val, val1, MAX));

		} else {
			if (i == a.size() - 1)
				break;
			string q = "";
			q = q + a[i];
			t.push_back(Token(q, q, MAX));
			i++;
		}
	}
}
vector<Token> Scanner::scan() {
	int num = MAX - 1;
	string a;

	freopen("in.in", "r", stdin);

	while (getline(cin, a)) {
		cout << a << endl;
		stack<char> q;
		string w = "";

		w = "";
		int i = 0;
		while (i < (int) a.size()
				&& ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z')
						|| (a[i] >= '0' && a[i] <= '9'))) {
			w = w + a[i++];
		}
		//letter = a-z | A-Z
		while (i < (int) a.size() && a[i] == ' ')
			i++;
		if (a[i] == '=' || a[i] == ':') {
			strings[w] = solve(a, i + 1);
			t.push_back(Token(w, strings[w], num--));
		} else if (a[i] == '{') {
			parse(a, i + 1);
		} else if (a[i] == '[') {
			marks(a, i + 1);
		}

	}
	return t;

}

Scanner::Scanner() {

}
