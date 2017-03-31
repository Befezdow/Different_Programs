#pragma once

#include "lexem.h"

class Operand:public Lexem
{
	double value;
public:
	Operand();
	Operand(double d);
	double getValue();
	Operand operator+ (Operand ob);
	Operand operator- (Operand ob);
	Operand operator* (Operand ob);
	Operand operator/ (Operand ob);
	Operand operator^ (Operand ob);
	Operand operator= (Operand ob);
};
