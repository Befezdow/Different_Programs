#include "stringmaster.h"
#include <sstream>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		std::cerr<<"Incorrect cout of arguments"<<std::endl;
		return 1;
	}
	std::string str(argv[1]);
	int state=StringMaster::checkString(str);
	if (state)
		return 1;
	Queue queue=StringMaster::parseString(str);
	StringMaster::infixToPostfix(queue);
	double d=StringMaster::calculate(queue);
	std::cout<<"Answer: "<<d<<std::endl;
	return 0;
}
