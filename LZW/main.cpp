#include "hash.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc<4)
    {
        cerr<<"Incorrect count of parameters"<<endl;
        return 1;
    }

    strstream s;                        //получаем размер таблицы
    s<<argv[2];
    int size;
    s>>size;

    if (size<8)
    {
        cerr<<"Incorrect size of table"<<endl;
        return 1;
    }

    Hash hashTable(size);
    vector<string> table(size);

    for (unsigned int i=0;i<256;++i)    //инициализировали таблицу
    {
        table[i]=""+char(i);
    }
    hashTable.init();                   //инициализировали хэш

    ifstream in;
    in.open(argv[1],ios::in | ios::binary);

    if (!in.is_open())
    {
        cerr<<"In file not open"<<endl;
        return 1;
    }

    ofstream out;
    out.open(argv[3],ios::out | ios::binary);

    if (!out.is_open())
    {
        cerr<<"Out file not open"<<endl;
        return 1;
    }

    string tempStr;
    int currentLen=0;
    while (!in.eof())                                           //пока не конец in файла
    {
        int c=in.get();                                         //читаем символ
        char symbol=(char)c;
        int code=hashTable.findCode(tempStr+symbol);            //пытаемся получить его код из таблицы
        if (code==-1)                                           //если символа там нет
        {
            //пишем код tempStr
            table.push_back(tempStr+symbol);                    //добавляем в таблицу новую строку
            currentLen++;
            hashTable.insert(tempStr+symbol,currentLen-1);
            tempStr=""+symbol;                                  //обновляем временную строку
        }
        else                                                    //если символ там есть
        {
            tempStr+=symbol;                                    //добавляем его к временной строке
        }
    }
    //пишем hashTable.findCode(tempStr);

    in.close();
    out.close();
    return 0;
}
