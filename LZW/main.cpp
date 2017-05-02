#include "hash.h"
#include "binarywriter.h"
#include "binaryreader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>
#include <cmath>
#include <iomanip>
#include <cstring>

using namespace std;

void compress(ifstream& in, ofstream& out, int sizeOfHash)
{
    int size=pow(2,sizeOfHash);                                 //получаем размер хэш таблицы

    Hash hashTable(size);
    hashTable.init();                                           //инициализировали хэш

    out.write("LZW5",4);                                        //пишем заголовок
    out.put(char(sizeOfHash));

    string tempStr;
    int newCode=256;                                              //код новой строки

    BinaryWriter writer;
    writer.attach(&out);

    while (!in.eof())                                           //пока не конец in файла
    {
        int c=in.get();                                         //читаем символ
        char symbol=char(c);

        int code=hashTable.findCode(tempStr+symbol);            //пытаемся получить код новой строки из таблицы

        if (code==-1)                                           //если символа там нет
        {
            unsigned short outCode=(unsigned short)hashTable.findCode(tempStr);
            cerr<<"Записано: "<<outCode<<" Строка: "<<tempStr<<" Кол-во байт: "<<7 + ceil(double(hashTable.size())/256)<<endl;
            writer.write(outCode,7 + ceil(double(hashTable.size())/256));

            if (newCode<size)
            {
                hashTable.insert(tempStr+symbol,newCode);
                newCode++;
            }
            tempStr.clear();                                    //обновляем временную строку
            tempStr=tempStr+symbol;
        }
        else                                                    //если символ там есть
        {
            tempStr=tempStr+symbol;                             //добавляем его к временной строке
        }
    }
    unsigned short outCode=(unsigned short)hashTable.findCode(tempStr);
    cerr<<"Записано: "<<outCode<<" Строка: "<<tempStr<<" Кол-во байт: "<<7 + ceil(double(hashTable.size())/256)<<endl;
    writer.write(outCode,7 + ceil(double(hashTable.size())/256));
    writer.flush();
}

void uncompress(ifstream& in, ofstream& out)
{
    char header[4];
    in.read(header,4);
    if (header[0]!='L' || header[1]!='Z' || header[2]!='W' || header[3]!='5')
    {
        throw "Unknown format of file";
    }

    int size=in.get();
    int tableSize=pow(2,size);
    vector<string> table;

//    cerr<<"Инициализация вектора:"<<endl;
    for (int i=0;i<256;++i)
    {
        string s;
        s=s+char(i);
//        cerr<<i<<": "<<s<<endl;
        table.push_back(s);
    }

    for (int i=256;i<tableSize;++i)
    {
        table.push_back("");
    }

    int length=256;
    BinaryReader reader;
    reader.attach(&in);

    int readedBits=8;

    unsigned short code=reader.read(readedBits);
    if (readedBits<size)
        readedBits++;
    out.write(table.at(code).c_str(),table.at(code).size());
    cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во байт: "<<7 + ceil(double(length)/256)<<endl;
//    if (length<tableSize)
//    {
//        length++;               //////////////////////////НУЖНО ЛИ ЭТО???
//    }
    //беда в разности кол-ва бит чтения и записи
    //8 бит пишется 1 раз а читается 2
    //НЕ РОБИТ ДЛЯ 8
    unsigned short old;
    while (!in.eof())
    {
        old=code;
        code=reader.read(readedBits);
        if (table[code]!="")
        {
            out.write(table.at(code).c_str(),table.at(code).size());
            cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во байт: "<<7 + ceil(double(length)/256)<<endl;
            if (length<tableSize)
            {
                table[length]=table.at(old)+table.at(code)[0];
//                cerr<<"Добавляем в таблицу "<<table[length]<<endl;
                length++;
            }
        }
        else
        {
            string tempStr=table.at(old)+table.at(old)[0];
            out.write(tempStr.c_str(),tempStr.size());
            cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во байт: "<<7 + ceil(double(length)/256)<<endl;
            if (length<tableSize)
            {
                table[length]=tempStr;
//                cerr<<"Добавляем в таблицу "<<table[length]<<endl;
                length++;
            }
        }
        if (length%256==0 && readedBits<size)
        {
            readedBits++;
        }

    }
}

int main(int argc, char *argv[])
{
    if (argc<4)
    {
        cerr<<"Incorrect count of parameters"<<endl;
        return 1;
    }

    strstream s;                                //получаем размер таблицы
    s<<argv[3];
    int size;
    s>>size;

    if (size<8 || size>16)                      //проверяем размер
    {
        cerr<<"Incorrect size of table"<<endl;
        return 1;
    }

    ifstream in;                                //поток на вход
    in.open(argv[1],ios::in | ios::binary);

    if (!in.is_open())
    {
        cerr<<"In file not open"<<endl;
        return 1;
    }

    ofstream out;                               //поток на выход
    out.open(argv[2],ios::out | ios::binary);

    if (!out.is_open())
    {
        cerr<<"Out file not open"<<endl;
        return 1;
    }

    compress(in,out,size);                      //осуществляем сжатие

    in.close();
    out.close();

    ifstream in2;
    in2.open(argv[2],ios::in | ios::binary);
    if (!in2.is_open())
    {
        cerr<<"Out2 file not open"<<endl;
        return 1;
    }

    ofstream out2;
    out2.open("result.txt",ios::out | ios::binary);
    if (!out2.is_open())
    {
        cerr<<"Result file not open"<<endl;
        return 1;
    }
    uncompress(in2,out2);
    in2.close();
    out2.close();
    return 0;
}
