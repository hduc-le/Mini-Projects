#ifndef __Infix__
#define __Infix__
#include<string>
#include "Token.h"
#include "MyStack.h"
#include<math.h>
class Infix
{
	std::string Istr;
	int pos;

	Token _get_token();

public:
	Infix(string str) { Istr = str; pos = 0; }
	bool eval(double& result);
};
string CalcValue(string opr, string op);
string CalcValue(string opr2, string opr1, string op);
#endif // !__Infix__

