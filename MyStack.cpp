#include"MyStack.h"

MyStack::MyStack()
{
	pHead = NULL;
}

Token MyStack::get_head()
{
	return pHead->val;
}

bool MyStack::push(const Token& x)
{
	Node* p = new Node;
	p->val = x;
	p->pNext = NULL;

	if (empty())
		pHead = p;
	else
	{
		p->pNext = pHead;
		pHead = p;
	}
	return true;
}
bool MyStack::pop(Token& px)
{
	Node* k = pHead;
	if (empty())
		return false;
	pHead = pHead->pNext;
	px = k->val;
	delete k;
	return true;
}
bool MyStack::empty()
{
	return pHead == NULL;
}
/*
void MyStack::CleanUp()
{
	Token x;
	Node* k = pHead;
	while (k != NULL)
	{
		pop(x);
		k = k->pNext;
	}
	delete k;
}
int MyStack::get_size() const
{
	int count = 0;
	Node* k = pHead;
	while (k != NULL)
	{
		k = k->pNext;
		count++;
	}
	return count;
}
*/