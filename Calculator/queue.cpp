#include "queue.h"
#include <iostream>

Queue::Queue()
{
	len=0;
	begin=NULL;
	end=NULL;
}

void Queue::push(Lexem* ob)
{
	Item* it=new Item;
	it->val=ob;
	it->next=NULL;
	if (end)
		end->next=it;
	end=it;
	if (!begin)
		begin=end;
	len++;
}

Queue::~Queue()
{
	Item* it=this->begin;
	while (it)
	{
		Item* it1=it->next;
		delete it;
		it=it1;
	}
}

Lexem* Queue::pop()
{
	if (len==0)
	{
		std::cerr<<"Queue is empty"<<std::endl;
		return NULL;
	}
	Item* result=this->begin;
	if (result==this->end)
		this->end=this->end->next;
	Lexem* r=result->val;
	this->begin=this->begin->next;
	delete result;
	len--;
	return r;
}

Queue::Queue(const Queue& ob)
{
	begin=NULL;
	end=NULL;
	Item* it=ob.begin;
	while (it)
	{
		this->push(it->val);
		it=it->next;
	}
}

bool Queue::empty()
{
	return len==0;
}

int Queue::size()
{
	return len;
}

Lexem* Queue::front()
{
	if (len==0)
	{
		std::cerr<<"Queue is empty"<<std::endl;
		return NULL;
	}
	return begin->val;
}

Lexem* Queue::back()
{
	if (len==0)
	{
		std::cerr<<"Queue is empty"<<std::endl;
		return NULL;
	}
	return end->val;
}

Queue& Queue::operator= (Queue& ob)
{
	while (!this->empty())
	{
		this->pop();
	}
	Item* it=ob.begin;
	while (it)
	{
		this->push(it->val);
		it=it->next;
	}
}
