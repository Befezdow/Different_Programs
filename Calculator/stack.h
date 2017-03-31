#pragma once

#include <iostream>

template <typename T>
class Stack
{
	T** array;
	int len;
	int reserveLen;
public:
	Stack();
	~Stack();
	void push(T* ob);
	T* pop();
	T* top();
	T* bottom();
	bool empty();
	int size();
	void reserve (int count);
	void exempt();
};

template <typename T>
Stack<T>::Stack()
{
	array=new T* [10];
	len=0;
	reserveLen=10;
}

template <typename T>
Stack<T>::~Stack()
{
	delete array;
}

template <typename T>
void Stack<T>::reserve (int count)
{
	if (count<=reserveLen)
	return;
	T** newArray=new T* [count];
	for (int i=0;i<len;i++)
		newArray[i]=array[i];
	delete [] array;
	array=newArray;
	reserveLen=count;
}

template <typename T>
void Stack<T>::exempt ()
{
	if (reserveLen<=len)
		return;
	T** newArray=new T* [len];
	for (int i=0;i<len;i++)
		newArray[i]=array[i];
	delete [] array;
	array=newArray;
	reserveLen=len;
	return;
}

template <typename T>
void Stack<T>::push(T* ob)
{
	if (len>=reserveLen)
		this->reserve(len+10);
	array[len]=ob;
	len++;
}

template<typename T>
T* Stack<T>::pop()
{
	if (len==0)
	{
		std::cerr<<"Stack is empty"<<std::endl;
		return NULL;
	}
	len--;
	return array[len];
}

template<typename T>
T* Stack<T>::top()
{
	if (len==0)
	{
		std::cerr<<"Stack is empty"<<std::endl;
		return NULL;
	}
	return array[len-1];
}

template<typename T>
T* Stack<T>::bottom()
{
	if (len==0)
	{
		std::cerr<<"Stack is empty"<<std::endl;
		return NULL;
	}
	return array[0];
}

template<typename T>
int Stack<T>::size()
{
	return len;
}

template<typename T>
bool Stack<T>::empty()
{
	return len==0;
}
