#include "hash.h"
#include <iostream>

Hash::Item::Item(std::string s, unsigned short c):
    code(c),
    str(s),
    next(nullptr)
{}

void
Hash::Item::setNext(Item* n)
{
    next=n;
}

void Hash::Item::setCode(unsigned char c)
{
    code=c;
}

unsigned short Hash::Item::getCode() const
{
    return code;
}

Hash::Item*
Hash::Item::getNext() const
{
    return next;
}

std::string
Hash::Item::getStr() const
{
    return str;
}

Hash::Hash(int len):
    LENGTH(len),
    currentSize(0)
{
    array=new Item* [LENGTH];
    for (int i=0;i<LENGTH;++i)
    {
        array[i]=nullptr;
    }
}

Hash::~Hash()
{
    for (int i=0;i<LENGTH;++i)
    {
        Item* cur;
        Item* nextItem;
        cur=array[i];
        while (cur)
        {
            nextItem=cur->getNext();
            delete cur;
            cur=nextItem;
        }
    }
    delete [] array;
}

int
Hash::findCode(std::string s)
{
    int index=hash(s);
    Item* item=array[index];
    while (item && item->getStr()!=s)
    {
        item=item->getNext();
    }
    if (item)
    {
        return item->getCode();
    }
    else
    {
        return -1;
    }
}

void
Hash::insert(std::string s,unsigned short c)
{
    int index=hash(s);
//    std::cerr<<index<<std::endl;
    Item* item=array[index];
    Item* newItem=new Item(s,c);
    if (item)
    {
        while (item->getNext())
        {
            if (item->getStr()==s)
            {
                item->setCode(c);
                return;
            }
            item=item->getNext();
        }
        item->setNext(newItem);
    }
    else
        array[index]=newItem;
    currentSize++;
}

int
Hash::hash(std::string s)
{
    unsigned int result=13562473;
    int size=s.size();
    for (int i=0;i<size;++i)
    {
        result=(result*37+s[i]*size)%LENGTH;
    }
    return result%LENGTH;
}

void
Hash::init()
{
//    std::cerr<<"Инициализация хэша:"<<std::endl;
    for (unsigned int i=0;i<256;++i)
    {
        std::string s;
        s=s+char(i);
//        std::cerr<<i<<": "<<s<<std::endl;
        this->insert(s,i);
    }
}

int Hash::size() const
{
    return currentSize;
}
