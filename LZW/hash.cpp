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

void
Hash::Item::setCode(unsigned char c)
{
    code=c;
}

unsigned short
Hash::Item::getCode() const
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
    array=new Item* [LENGTH];                   //создаем массив указателей длиной LENGTH
    for (int i=0;i<LENGTH;++i)                  //инициализируем его
    {
        array[i]=nullptr;
    }
}

Hash::~Hash()
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

int
Hash::findCode(std::string s)
{
    int index=hash(s);                          //получаем нужный индекс в массиве указателей
    Item* item=array[index];                    //получаем соответствующий корень волоса

    while (item && item->getStr()!=s)           //идем по волосу до конца, пока не нашли нужный
    {
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

void
Hash::insert(std::string s,unsigned short c)
{
    int index=hash(s);                          //получаем индекс в массиве указателей
    Item* item=array[index];                    //получаем соответствующий корень волоса

    if (item)                                   //если корень волоса не пуст
    {
        while (item->getNext())                 //идем по волосу
        {
            if (item->getStr()==s)              //если элемент с такой строкой уже есть
            {
                item->setCode(c);               //меняем ему код
                return;                         //отваливаемся
            }
            item=item->getNext();
        }
        Item* newItem=new Item(s,c);            //создаем новый элемент
        item->setNext(newItem);                 //ставим нащ элемент в конец волоса
    }
    else                                        //если корень волоса пуст
    {
        Item* newItem=new Item(s,c);            //создаем новый элемент
        array[index]=newItem;                   //ставим наш элемент в корень
    }

    currentSize++;                              //инкрементируем размер хэш таблицы
}

int
Hash::hash(std::string s)
{
    if (tempHash==-1)
    {
        if(s.size() == 1)
        {
            prevHash = 13562473;
        }

        prevHash = prevHash * 37 + s.back();
        tempHash=prevHash;

        return prevHash % LENGTH;
    }
    else
    {
        return tempHash % LENGTH;
    }
}

void
Hash::init()
{
    for (unsigned int i=0;i<256;++i)            //перебираем алфавит
    {
        std::string s;
        s=s+char(i);                            //преобразуем символ в строку
        this->insert(s,i);                      //добавляем её в таблицу
        clearTempHash();
    }
}

int
Hash::size() const
{
    return currentSize;
}

void Hash::checkSopels() const
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

void Hash::clearTempHash()
{
    tempHash=-1;
}
