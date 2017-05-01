#ifndef HASH_H
#define HASH_H

#include <string>

class Hash                      //открытый хэш
{
    class Item                  //элемент хэша
    {
        unsigned short code;    //код строки из списка
        std::string str;        //строка
        Item* next;             //указатель на следующий элемент

    public:
        Item(std::string s="",unsigned short c=0);

        void setNext(Item* n);
        void setCode(unsigned char c);

        unsigned short getCode() const;
        Item* getNext() const;
        std::string getStr() const;
    };

    const int LENGTH;
    Item** array;
    int currentSize;

    int hash(std::string s);

public:
    Hash(int len);
    ~Hash();
    int findCode(std::string s);                        //поиск по строке
    void insert(std::string s, unsigned short c);       //добавление строки с её кодом
    void init();                                        //инициализация хэша алфавитом
    int size() const;
};

#endif // HASH_H
