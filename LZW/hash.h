#ifndef HASH_H
#define HASH_H

#include <string>

class Hash                                          //открытая хэш таблица
{
    class Item                                      //элемент хэш таблицы
    {
        unsigned short code;                        //код строки из списка
        std::string str;                            //строка
        Item* next;                                 //указатель на следующий элемент

    public:
        Item(std::string s="",unsigned short c=0);  //s - строка c - её код

        void setNext(Item* n);
        void setCode(unsigned char c);

        unsigned short getCode() const;
        Item* getNext() const;
        std::string getStr() const;
    };

    const int LENGTH;                               //длина массива хэш таблицы
    Item** array;                                   //сам массив (по сути, его элементы - корни волос)
    int currentSize;                                //текущее кол-во элементов в хэш таблице

    unsigned int prevHash;
    long tempHash;

    int hash(std::string s);                        //хэш-функция

public:
    Hash(int len);
    ~Hash();
    int findCode(std::string s);                        //поиск кода по строке (возвращает -1 если не нашел)
    void insert(std::string s, unsigned short c);       //добавление строки с её кодом
    void init();                                        //инициализация хэша алфавитом
    int size() const;                                   //возвращает размер хэш таблицы
    void checkSopels() const;
    void clearTempHash();
};

#endif // HASH_H
