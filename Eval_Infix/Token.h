#ifndef __Token__
#define __Token__
// Token.h
#include<string>
struct Token
{
	int type;
	std::string value;
};

#define TOK_ERROR 0 
#define TOK_EOF 1 // end off 
#define TOK_OP1 2 // binary operator
#define TOK_OP2 3 // unary operator
#define TOK_OPRND 4 // operand
#define TOK_PRTHESES -1
#endif // !__Token__

