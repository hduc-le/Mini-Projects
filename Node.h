#pragma once
// Node.h
#include<iostream>
#include"Token.h"
using namespace std;

class Node
{
public:
	Node() { pNext = NULL; }
	Token val;
	Node* pNext;
};
