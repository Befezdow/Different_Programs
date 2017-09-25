#include "hash2.h"
#include <iostream>
#include <cstring>

Hash2::Item::Item(int p, char s, unsigned short c):
    next(nullptr),
    parentCode(p),
    symbol(s),
    code(c)
{}

void Hash2::Item::setCode(unsigned short c)
{
    code=c;
}

void Hash2::Item::setNext(Hash2::Item *n)
{
    next=n;
}

Hash2::Item *Hash2::Item::getNext() const
{
    return next;
}

int Hash2::Item::getParentCode() const
{
    return parentCode;
}

unsigned short Hash2::Item::getCode() const
{
    return code;
}

char Hash2::Item::getSymbol() const
{
    return symbol;
}

unsigned short Hash2::hash(int p, char s)
{
    if (tempHash==-1)
    {
        char mass[2]={s,s};
        short sh;
        memcpy(&sh,mass,2);
        tempHash=sh^p;
//        tempHash=s^p; ((char *)&p)[1] ^ s
        return (unsigned int)(tempHash) % LENGTH;
    }
    else
    {
        return (unsigned int)(tempHash) % LENGTH;
    }
}

Hash2::Hash2(int len):
    LENGTH(len),
    currentSize(0),
    tempHash(-1)
{
    array=new Item* [LENGTH];                   //создаем массив указателей длиной LENGTH
    for (int i=0;i<LENGTH;++i)                  //инициализируем его
    {
        array[i]=nullptr;
    }
}

Hash2::~Hash2()
{
    for (int i=0;i<LENGTH;++i)                  //идем по массиву указателей
    {
        Item* cur;                              //текущий элемент
        Item* nextItem;                         //следующий элемент

        cur=array[i];                           //инициализируем текущий

        while (cur)                             //пока не конец
        {
            nextItem=cur->getNext();            //берем следующий указатель в волосе
            delete cur;                         //удаляем текущий
            cur=nextItem;                       //ставим следующий текущим
        }
    }
    delete [] array;                            //удаляем сам массив указателей
}

int Hash2::findCode(int p, char s)
{
    int index=hash(p,s);                        //получаем нужный индекс в массиве указателей
    Item* item=array[index];                    //получаем соответствующий корень волоса

    while (item && (item->getParentCode()!=p || item->getSymbol()!=s))
    {                                           //идем по волосу до конца, пока не нашли нужный
        item=item->getNext();
    }

    if (item)                                   //если нашелся
    {
        return item->getCode();                 //возвращаем код
    }
    else                                        //если не нашелся
    {
        return -1;                              //откидываем -1
    }
}

void Hash2::insert(int p, char s, unsigned short c)
{
    int index=hash(p,s);                        //получаем индекс в массиве указателей
    Item* item=array[index];                    //получаем соответствующий корень волоса

    if (item)                                   //если корень волоса не пуст
    {
        while (item->getNext())                 //идем по волосу
        {
            if (item->getParentCode()==p && item->getSymbol()==s)  //если элемент с такой строкой уже есть
            {
                item->setCode(c);               //меняем ему код
                return;                         //отваливаемся
            }
            item=item->getNext();
        }

        Item* newItem=new Item(p,s,c);          //создаем новый элемент
        item->setNext(newItem);                 //ставим нащ элемент в конец волоса
    }
    else                                        //если корень волоса пуст
    {
        Item* newItem=new Item(p,s,c);          //создаем новый элемент
        array[index]=newItem;                   //ставим наш элемент в корень
    }

    currentSize++;                              //инкрементируем размер хэш таблицы
}

void Hash2::init()
{
    for (unsigned int i=0;i<256;++i)            //перебираем алфавит
    {
        this->insert(-1,(unsigned char)(i),i);  //добавляем символ в таблицу
        clearTempHash();
    }
}

int Hash2::size() const
{
    return currentSize;
}

void Hash2::checkSopels() const
{
    int count=0;
    int tempCount;
    for (int i=0;i<LENGTH;++i)
    {
        tempCount=0;
        Item* current=array[i];
        while(current)
        {
            tempCount++;
            current=current->getNext();
        }
        if (tempCount>3)
            std::cout<<i<<": "<<tempCount<<std::endl;
        if (tempCount==0)
            count++;
    }
    std::cerr<<"Общее кол-во пустых: "<<count<<std::endl;
}

void Hash2::clearTempHash()
{
    tempHash=-1;
}
