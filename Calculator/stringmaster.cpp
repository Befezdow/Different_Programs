#include "stringmaster.h"
#include "stack.h"
#include "operator.h"
#include "operand.h"
#include <sstream>
#include <string>

using namespace std;

int StringMaster::checkString(string sourceString)
{
	if (sourceString.empty())
	{
		cerr<<"Bad expression: String is empty"<<endl;
		return 1;
	}


	if (!isdigit(sourceString[0]) && sourceString[0]!='-' && sourceString[0]!='(')
	{
		cerr<<"Bad expression: The first symbol is bad"<<endl;
		return 2;
	}


	if (!isdigit(sourceString[sourceString.size()-1]) && sourceString[sourceString.size()-1]!=')')
	{
		cerr<<"Bad expression: The last symbol is bad"<<endl;
		return 3;
	}


	char availableSymbols[8]={'+','-','*','/','^','(',')','.'};
	int openBracesCount=0;
	bool dotState=true;
	bool charAvailable=true;
	bool digitAvailable=true;
	for (int i=0;i<sourceString.size();i++)
	{
		char symbol=sourceString[i];
		if (!isdigit(symbol))
		{
			if (symbol!='(' && !charAvailable)
			{
				cerr<<"Error 1"<<endl;
				return 1;
			}
			int tempCount=0;
			for (int j=0;j<8;j++)
			{
				if (symbol==availableSymbols[j])
					tempCount++;
			}
			if (!tempCount)
			{
				cerr<<"Bad expression: Incorrect symbol in the string"<<endl;
				return 4;
			}
			charAvailable=false;
			digitAvailable=true;
			if (symbol!='.')
			{
				if (!digitAvailable)
				{
					cerr<<"Error"<<endl;
					return 1;
				}
				dotState=true;
			}
			else
				dotState=false;
			if (symbol=='(')
			{
				openBracesCount++;
				charAvailable=true;
			}
			if (symbol==')')
			{
				if (openBracesCount<=0)
				{
					cerr<<"Error 2"<<endl;
					return 1;
				}
				openBracesCount--;
				charAvailable=true;
				digitAvailable=false;
			}
			if (symbol!='(' && symbol!='-' && i!=0 && sourceString[i-1]=='(')
			{
				cerr<<"Error 3"<<endl;
				return 1;
			}			
		}
		else
		{	
			if (!digitAvailable)
			{
				cerr<<"Error"<<endl;
				return 1;
			}
			charAvailable=true;
		}
	}
	if (openBracesCount!=0)
	{
		cerr<<"Bad expression: Invalid braces"<<endl;
		return 10;
	}
	return 0;
}

Queue StringMaster::parseString(string sourceString)
{
	stringstream stream;
	stream<<sourceString;
	Queue finalQueue;
	bool readState=true;
	while (!stream.eof())
	{
		char c=stream.peek();
		if (isdigit(c))
		{
			double d;
			stream>>d;
			Operand* pOperand=new Operand(d);
			finalQueue.push(pOperand);
			readState=false;
		}
		else
		{
			if (c=='-' && readState)
			{
				double d;
				stream>>d;
				Operand* pOperand=new Operand(d);
				finalQueue.push(pOperand);
				readState=false;
			}	
			char ch;
			stream>>ch;
			if (stream.eof())
				break;
			if (ch=='(')
				readState=true;
			else
				readState=false;
			Operator* pOperator=new Operator(ch);
			finalQueue.push(pOperator);
		}
	}
	return finalQueue;
}

void StringMaster::infixToPostfix(Queue& sourceQueue)
{
	Queue finalQueue;
	Stack<Operator> operatorStack;
	while (!sourceQueue.empty())
	{
		Lexem* lex=sourceQueue.pop();
		Operator* pOperator=dynamic_cast<Operator*> (lex);
		if (pOperator)
		{
			if (pOperator->getValue()=='(')
			{
				operatorStack.push(pOperator);
				continue;
			}
			if (pOperator->getValue()==')')
			{
				while (!operatorStack.empty())
				{
					if (operatorStack.top()->getValue()=='(')
					{
						delete operatorStack.pop();
						break;
					}
					else
					{
						Lexem* lex=operatorStack.pop();
						finalQueue.push(lex);
					}
				}
				continue;
			}
			while (!operatorStack.empty() && *pOperator<=(*(operatorStack.top())))
			{
				if (operatorStack.top()->getValue()=='(')
					break;
				Lexem* lex=operatorStack.pop();
				finalQueue.push(lex);
			}
			operatorStack.push(pOperator);
		}
		Operand* pOperand=dynamic_cast<Operand*> (lex);
		if (pOperand)
		{
			finalQueue.push(lex);
		}
	}
	while (!operatorStack.empty())
	{
		Lexem* lex=operatorStack.pop();
		finalQueue.push(lex);
	}
	sourceQueue=finalQueue;
	return;
}

double StringMaster::calculate(Queue& sourceQueue)
{
	Stack<Operand> operandStack;
	while (!sourceQueue.empty())
	{
		Lexem* lex=sourceQueue.pop();
		Operator* pOperator=dynamic_cast<Operator*> (lex);
		if (pOperator)
		{
			Operand* first=operandStack.pop();
			Operand* second=operandStack.pop();
			switch (pOperator->getValue())
			{
				case '+':
					*first=(*first)+(*second);
					operandStack.push(first);
					delete second;
					break;
				case '-':
					*first=(*second)-(*first);
					operandStack.push(first);
					delete second;
					break;
				case '*':
					*first=(*first)*(*second);
					operandStack.push(first);
					delete second;
					break;
				case '/':
					*first=(*second)/(*first);
					operandStack.push(first);
					delete second;
					break;
				case '^':
					*first=(*second)^(*first);
					operandStack.push(first);
					delete second;
					break;
			}
		}
		Operand* pOperand=dynamic_cast<Operand*> (lex);
		if (pOperand)
		{
			operandStack.push(pOperand);
		}
	}
	Operand* pOperand=operandStack.pop();
	double d=pOperand->getValue();
	delete pOperand;
	return d;
}
