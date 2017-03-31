#include "operand.h"
#include <cmath>

Operand::Operand()
{
	value=0;
}

Operand::Operand(double d)
{
	value=d;
}

double Operand::getValue()
{
	return value;
}

Operand Operand::operator+ (Operand ob)
{
	Operand result;
	result.value=this->value+ob.value;
	return result;
}

Operand Operand::operator- (Operand ob)
{
	Operand result;
	result.value=this->value-ob.value;
	return result;
}

Operand Operand::operator* (Operand ob)
{
	Operand result;
	result.value=this->value*ob.value;
	return result;
}

Operand Operand::operator/ (Operand ob)
{
	Operand result;
	result.value=this->value/ob.value;
	return result;
}

Operand Operand::operator^ (Operand ob)
{
	Operand result;
	result.value=pow(this->value,ob.value);
	return result;
}

Operand Operand::operator= (Operand ob)
{
	this->value=ob.value;
	return *this;
}
