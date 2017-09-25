#ifndef HASH2_H
#define HASH2_H

class Hash2                                         //Открытая хэш-таблица
{
    class Item                                      //Элемент хэш-таблицы
    {
        Item* next;                                 //указатель на следующий элемент
        int parentCode;                             //код строки - родителя
        char symbol;                                //новый символ, отличайщий строк от родителя
        unsigned short code;                        //код этой строки

    public:
        Item(int p=-1, char s=0, unsigned short c=0);

        void setCode(unsigned short c);
        void setNext(Item* n);

        Item* getNext() const;
        int getParentCode() const;
        unsigned short getCode() const;
        char getSymbol() const;
    };

    const int LENGTH;                               //длина массива хэш таблицы
    Item** array;                                   //сам массив (по сути, его элементы - корни волос)
    int currentSize;                                //текущее кол-во элементов в хэш таблице
    int tempHash;

    unsigned short hash(int p,char s);                        //хэш-функция

public:
    Hash2(int len);
    ~Hash2();

    int findCode(int p,char s);                     //поиск кода в хэше (возвращает -1 если не нашел)
    void insert(int p, char s, unsigned short c);   //добавление элемента
    void init();                                    //инициализация хэша алфавитом
    int size() const;                               //возвращает размер хэш таблицы

    void checkSopels() const;
    void clearTempHash();
};

#endif // HASH2_H
