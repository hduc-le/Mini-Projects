#include "Infix.h"
// Declare functions
bool _whitechar(const char& c);
bool _operand(const string& s);
bool _operator(const string& s);
bool _spcialOP(const string& s);
bool _parentheses(const string& s);
int _precedence(const string& s);

// Define the functions
bool _whitechar(const char& c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool _operand(const string& s)
{
	return ("0" <= s && s <= "9");
}

bool _operator(const string& s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "sqrt" || s == "log" || s == "abs" || s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "^" || s == "exp");
}

bool _spcialOP(const string& s)
{
	return (s == "sqrt" || s == "log" || s == "abs" || s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "exp");
}

bool _parentheses(const string& s)
{
	return (s == "(" || s == ")");
}

int _precedence(const string& s)
{
	if (_spcialOP(s) || s == "^")
		return 3;
	if (s == "*" || s == "/")
		return 2;
	if (s == "+" || s == "-")
		return 1;
	return -1;
}

Token Infix::_get_token()
{
	Token tok;
	string s = string(1, Istr[pos]);

	/*
	// ignore white characters
	while (pos < Istr.length() && _whitechar(Istr[pos]))
		pos++;
	
	*/
	// processing the special operators (sqrt, log, abs, exp, etc...) 

	while ('a' <= Istr[pos] && Istr[pos] <= 'z')
	{
		if (s[0] == Istr[pos])
			s.clear();
		s.push_back(Istr[pos]); 
		pos++;
	}

	if (pos == Istr.length())
		tok.type = TOK_EOF;
	else if (_parentheses(s))
	{
		tok.type = TOK_PRTHESES;
		tok.value = s;
		pos++;
	}
	else if (_operator(s))
	{
		if (_spcialOP(s))
		{
			pos--;
			tok.type = TOK_OP1;
		}
		else
		{
			if (s == "-" || s == "+")
			{
				if (pos <= 0)
					tok.type = TOK_OP1;
				else if (_operator(string(1, Istr[pos - 1])) || string(1, Istr[pos - 1]) == "(")
					tok.type = TOK_OP1;
				else
				{
					tok.type = TOK_OP2;
					int index = pos;
					string front_tok = string(1, Istr[index - 1]);
					string back_tok = string(1, Istr[index + 1]);
					while ('a' <= Istr[index+1] && Istr[index+1] <= 'z')
					{
						if (back_tok[0] == Istr[index+1])
							back_tok.clear();
						back_tok.push_back(Istr[index+1]); 
						index++;
					}
					if (!_operand(front_tok) && front_tok != ")")
						tok.type = TOK_ERROR;
					if (!_operand(back_tok) && back_tok != "(" && back_tok != "+" && back_tok != "-" && !_spcialOP(back_tok))
						tok.type = TOK_ERROR;
				}
			}
			else
			{
				tok.type = TOK_OP2;
				if (pos <= 0) tok.type = TOK_ERROR;
				else {
					int index = pos;
					string front_tok = string(1, Istr[index - 1]);
					string back_tok = string(1, Istr[index + 1]);
					while ('a' <= Istr[index + 1] && Istr[index + 1] <= 'z')
					{
						if (back_tok[0] == Istr[index + 1])
							back_tok.clear();
						back_tok.push_back(Istr[index+1]); 
						index++;
					}
					if (!_operand(front_tok) && front_tok != ")")
						tok.type = TOK_ERROR;
					if (!_operand(back_tok) && back_tok != "(" && back_tok != "+" && back_tok != "-" && !_spcialOP(back_tok))
						tok.type = TOK_ERROR;
				}
			}
		}
		tok.value = s;
		pos++;
	}
	else if (_operand(s))
	{
		tok.type = TOK_OPRND;
		pos++;
		while (pos < Istr.length() && ('0' <= Istr[pos] && Istr[pos] <= '9' || Istr[pos] == '.' || Istr[pos] == 'e'))
		{
			s.push_back(Istr[pos]); pos++;
		}
		tok.value = s;
	}
	else
	{
		tok.type = TOK_ERROR;
		pos++;
	}
	return tok;
}

string CalcValue(string opr, string op)
{
	string sResult;
	if (op == "sqrt")
		sResult = to_string(sqrt(stod(opr)));
	else if (op == "log")
		sResult = to_string(log(stod(opr)));
	else if (op == "exp")
		sResult = to_string(exp(stod(opr)));
	else if (op == "abs")
		sResult = to_string(fabs(stod(opr)));
	else if (op == "sin")
		sResult = to_string(sin(stod(opr)));
	else if (op == "cos")
		sResult = to_string(cos(stod(opr)));
	else if (op == "tan")
		sResult = to_string(tan(stod(opr)));
	else if (op == "cot")
		sResult = to_string(double(1) / tan(stod(opr)));
	else if (op == "+")
		sResult = to_string(0 + stod(opr));
	else if (op == "-")
		sResult = to_string(0 - stod(opr));
	return sResult;
}

string CalcValue(string opr2, string opr1, string op)
{
	string sResult;
	if (op == "*")
		sResult = to_string(stod(opr2) * stod(opr1));
	else if (op == "/")
		sResult = to_string(stod(opr2) / stod(opr1));
	else if (op == "+")
		sResult = to_string(stod(opr2) + stod(opr1));
	else if (op == "-")
		sResult = to_string(stod(opr2) - stod(opr1));
	else if (op == "^")
		sResult = to_string(pow(stod(opr2), stod(opr1)));
	else if (op == "%")
		sResult = to_string(stoi(opr2) % stoi(opr1));
	return sResult;
}

bool Infix::eval(double& result)
{
	MyStack operatorStack, operandStack;
	Token operand1, operand2;
	Token op;
	Token _result;

	Token tok = _get_token();

	while (tok.type != TOK_EOF)
	{
		if (tok.type == TOK_ERROR) return false;
		if (tok.type == TOK_OPRND)
		{
			operandStack.push(tok);

			while (!operatorStack.empty() && operatorStack.get_head().type == TOK_OP1)
			{
				operatorStack.pop(op);
				operandStack.pop(operand1);
				_result.value = CalcValue(operand1.value, op.value);
				_result.type = TOK_OPRND;
				operandStack.push(_result);
			}
		}
		else if (tok.type == TOK_PRTHESES)
		{
			if (tok.value == "(")
				operatorStack.push(tok);
			else
			{
				if (operatorStack.empty()) 
					return false;
				while (operatorStack.get_head().value != "(")
				{
					if (operatorStack.get_head().type == TOK_OP1)
					{
						operandStack.pop(operand1);
						operatorStack.pop(op);
						_result.value = CalcValue(operand1.value, op.value);
					}
					else if (operatorStack.get_head().type == TOK_OP2)
					{
						operandStack.pop(operand1);
						operatorStack.pop(op);
						operandStack.pop(operand2);
						_result.value = CalcValue(operand2.value, operand1.value, op.value);
					}
					else
						return false;

					if (operatorStack.empty()) return false;
					_result.type = TOK_OPRND;
					operandStack.push(_result);
				}
				operatorStack.pop(op);
			}
		}
		else if (tok.type == TOK_OP2)
		{
			while (!operatorStack.empty() && _precedence(tok.value) <= _precedence(operatorStack.get_head().value))
			{
				if (operatorStack.get_head().type == TOK_OP1)
				{
					operandStack.pop(operand1);
					operatorStack.pop(op);
					_result.value = CalcValue(operand1.value, op.value);
				}
				else
				{
					operandStack.pop(operand1);
					operandStack.pop(operand2);
					operatorStack.pop(op);
					_result.value = CalcValue(operand2.value, operand1.value, op.value);
				}
				_result.type = TOK_OPRND;
				operandStack.push(_result);
			}
			operatorStack.push(tok);
		}
		else if (tok.type == TOK_OP1)
			operatorStack.push(tok);
		tok = _get_token();
	}

	while (!operatorStack.empty())
	{
		if (operatorStack.get_head().type == TOK_OP1)
		{
			operandStack.pop(operand1);
			operatorStack.pop(op);
			_result.value = CalcValue(operand1.value, op.value);
		}
		else if (operatorStack.get_head().type == TOK_OP2)
		{
			operandStack.pop(operand1);
			operatorStack.pop(op);
			operandStack.pop(operand2);
			_result.value = CalcValue(operand2.value, operand1.value, op.value);
		}
		else break;
		_result.type = TOK_OPRND;
		operandStack.push(_result);
	}

	if (operandStack.empty())
		return false;

	operandStack.pop(_result);
	result = stod(_result.value);

	if (!operandStack.empty() || !operatorStack.empty())
		return false;
	return true;
}

