#pragma once

#include "lexem.h"

class Operator:public Lexem
{
	char value;
	int priority;
public:
	Operator();
	Operator(char c);
	char getValue();
	bool operator> (Operator& ob);
	bool operator< (Operator& ob);
	bool operator>= (Operator& ob);
	bool operator<= (Operator& ob);
	bool operator== (Operator& ob);
};
