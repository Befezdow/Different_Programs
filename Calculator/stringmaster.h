#include "queue.h"
#include <string>

class StringMaster
{
public:
	static int checkString(std::string sourceString);
	static Queue parseString(std::string sourceString);
	static void infixToPostfix(Queue& sourceQueue);
	static double calculate(Queue& sourceQueue);
};
