#pragma once
// MyStack.h
#include"Node.h"
class MyStack
{
	Node* pHead;
public:
	MyStack();
	Token get_head();
	bool push(const Token& x);
	bool pop(Token& px);
	bool empty();
	~MyStack() {};
};

