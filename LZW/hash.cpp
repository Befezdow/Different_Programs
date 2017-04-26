#include "hash.h"

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
    LENGTH(len)
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
    Item* item=array[index];
    Item* newItem=new Item(s,c);
    if (item)
    {
        while (item->getNext())
        {
            item=item->getNext();
        }
    item->setNext(newItem);
    }
    else
        array[index]=newItem;
}

int
Hash::hash(std::string s)
{
    //преобразовать строку в максимально уникальное число % LENGTH
    return 1;
}

void
Hash::init()
{
    for (unsigned int i=0;i<256;++i)
    {
        this->insert(""+char(i),i);
    }
}
