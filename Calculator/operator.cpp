#include "operator.h"
#include <iostream>

Operator::Operator()
{
	value=0;
	priority=0;
}

Operator::Operator(char c)
{
	value=c;
	switch(c)
	{
		case '+':
			priority=1;
			break;
		case '-':
			priority=1;
			break;
		case '*':
			priority=2;
			break;
		case '/':
			priority=2;
			break;
		case '^':
			priority=3;
			break;
		case '(':
			priority=0;
			break;
		case ')':
			priority=0;
			break;
		default:
			std::cerr<<"Unavailable symbol for operator"<<std::endl;
			priority=0;
			break;
	}
}

char Operator::getValue()
{
	return value;
}

bool Operator::operator> (Operator& ob)
{
	return this->priority>ob.priority;
}

bool Operator::operator< (Operator& ob)
{
	return this->priority<ob.priority;
}

bool Operator::operator>= (Operator& ob)
{
	return this->priority>=ob.priority;
}

bool Operator::operator<= (Operator& ob)
{
	return this->priority<=ob.priority;
}

bool Operator::operator== (Operator& ob)
{
	return this->priority==ob.priority;
}
