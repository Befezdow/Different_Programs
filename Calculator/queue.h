#pragma once

#include "lexem.h"

struct Item
{
	Lexem* val;
	Item* next;
};

class Queue
{
	int len;
	Item* begin;
	Item* end;
public:
	Queue();
	Queue(const Queue &ob);
	~Queue();
	void push(Lexem* ob);
	Lexem* pop();
	bool empty();
	int size();
	Lexem* front();
	Lexem* back();
	Queue& operator= (Queue& ob);
};
