#include "archivator.h"
#include "hash.h"
#include "hash2.h"
#include "binarywriter.h"
#include "binaryreader.h"
#include <vector>
#include <strstream>
#include <cmath>
#include <cstring>
#include <iostream>

void Archivator::compress(std::ifstream &in, std::ofstream &out, int sizeOfHash)
{
    int size=pow(2,sizeOfHash);                                 //получаем размер хэш таблицы

    Hash hashTable(size);                                       //создали хэш таблицу заданного размера
    hashTable.init();                                           //инициализировали хэш таблицу

    out.write("LZW5",4);                                        //пишем заголовок
    out.put(char(sizeOfHash));                                  //пишем размер хэш таблицы

    std::string tempStr;                                             //буферная строка (кухня алгоритма)
    int newCode=256;                                            //код новой строки

    BinaryWriter writer;                                        //создаем писалку
    writer.attach(&out);                                        //прикрепляем к ней поток

    int writedBits=8;                                           //кол-во записываемых бит

    unsigned short old;
    int code;

//    unsigned int start=clock();

    while (1)                                                   //читаем файл
    {
        int c=in.get();                                         //читаем символ
        if (in.eof())                                           //если конец файла, то прерываемся
            break;
        char symbol=char(c);                                    //кастуем int к символу

        code=hashTable.findCode(tempStr+symbol);                //пытаемся получить код новой строки из хэш таблицы

        if (code==-1)                                           //если символа там нет
        {
//                std::cerr<<"Записано: "<<old<<" Строка: "<<tempStr<<" Кол-во бит: "<<writedBits<<std::endl;
            try
            {
                writer.write(old,writedBits);                   //пишем его с холодным стартом
            }
            catch (const char* str)
            {
                throw str;
            }

            if (newCode<size)                                   //если таблица не полная
            {
                hashTable.insert(tempStr+symbol,newCode);       //добавляем новую строку в таблицу
                newCode++;

                if (((hashTable.size()-1) & (hashTable.size()-2))==0)
                {
                    writedBits++;
                }
            }

            tempStr.clear();                                    //обновляем буферную строку
            tempStr+=symbol;
            old=symbol;
        }
        else                                                    //если символ там есть
        {
            tempStr+=symbol;                                    //добавляем его к буферной строке
            old=code;
        }
        hashTable.clearTempHash();
    }

//    cerr<<"Записано: "<<old<<" Строка: "<<tempStr<<" Кол-во бит: "<<writedBits<<endl;

    try
    {
        writer.write(old,writedBits);                           //пишем его с холодным стартом
    }
    catch (const char* str)
    {
        throw str;
    }

    writer.flush();                                             //скидываем остатки в поток

//    std::cerr<<"Время работы: "<<(clock()-start)/CLOCKS_PER_SEC<<std::endl;

//    hashTable.checkSopels();
}

void Archivator::compress2(std::ifstream &in, std::ofstream &out, int sizeOfHash)
{
    int size=pow(2,sizeOfHash);                                 //получаем размер хэш таблицы

    Hash2 hashTable(size);                                      //создали хэш таблицу заданного размера
    hashTable.init();                                           //инициализировали хэш таблицу

    out.write("LZW5",4);                                        //пишем заголовок
    out.put(char(sizeOfHash));                                  //пишем размер хэш таблицы

    std::string tempStr;                                             //буферная строка (кухня алгоритма)
    int newCode=256;                                            //код новой строки

    BinaryWriter writer;                                        //создаем писалку
    writer.attach(&out);                                        //прикрепляем к ней поток

    int writedBits=8;                                           //кол-во записываемых бит

    int old=-1;
    int code;

//    unsigned int start=clock();
    int co=1; /////////////////////

    while (1)                                                   //читаем файл
    {
        std::cerr<<"Old: "<<old<<std::endl;
        int c=in.get();                                         //читаем символ
        if (in.eof())                                           //если конец файла, то прерываемся
            break;
        char symbol=char(c);                                    //кастуем int к символу

        if (co>=4180 && co<=4200)
        {
            std::cerr<<co<<std::endl;
            std::cerr<<"Читаю символ"<<(unsigned int)(unsigned char)symbol<<std::endl;
        }

        code=hashTable.findCode(old,symbol);                    //пытаемся получить код новой строки из хэш таблицы

        if (code==-1)                                           //если символа там нет
        {
            if (co>=4180 && co<=4200)
            {
                std::cerr<<"Записано: "<<old<<" Строка: "<<tempStr<<" Кол-во бит: "<<writedBits<<std::endl;
            }
            co++;

            try
            {
                writer.write(old,writedBits);                   //пишем его с холодным стартом
            }
            catch (const char* str)
            {
                throw str;
            }

            if (newCode<size)                                   //если таблица не полная
            {
                std::cerr<<"Вставка в хэш строки"<<std::endl;
                hashTable.insert(old,symbol,newCode);           //добавляем новую строку в таблицу
                newCode++;

                if (((hashTable.size()-1) & (hashTable.size()-2))==0)
                {
                    writedBits++;
                }
            }

            tempStr.clear();                                    //обновляем буферную строку
            tempStr+=symbol;
            old=(unsigned char)symbol;
        }
        else                                                    //если символ там есть
        {
            std::cerr<<"Я нашел в хэше строку "<<old<<" "<<(unsigned int)(unsigned char)symbol<<std::endl;
            tempStr+=symbol;                                    //добавляем его к буферной строке
            old=code;
        }
        hashTable.clearTempHash();
    }

    std::cerr<<"Конец цикла"<<std::endl;
    std::cerr<<"Записано: "<<old<<" Строка: "<<tempStr<<" Кол-во бит: "<<writedBits<<std::endl;

    try
    {
        writer.write(old,writedBits);                           //пишем его с холодным стартом
    }
    catch (const char* str)
    {
        throw str;
    }

    writer.flush();                                             //скидываем остатки в поток

//    std::cerr<<"Время работы: "<<(clock()-start)/CLOCKS_PER_SEC<<std::endl;

//    hashTable.checkSopels();
}

void Archivator::uncompress(std::ifstream &in, std::ofstream &out)
{
    char header[4];
    in.read(header,4);                                          //читаем заголовок
    if (header[0]!='L' || header[1]!='Z' || header[2]!='W' || header[3]!='5')
    {
        throw "Unknown format of file";                         //если заголовок не совпадает, то отуидываем exception
    }

    int size=in.get();                                          //получаем размер таблицы
    int tableSize=pow(2,size);                                  //приводим его к норм виду

    std::vector<std::string> table;                             //заводим таблицу перевода

    for (int i=0;i<256;++i)                                     //инициализируем её алфавитом
    {
        std::string s;
        s=s+char(i);
        table.push_back(s);
    }

    for (int i=256;i<tableSize;++i)                             //инициализируем оставщуюся часть
    {
        table.push_back("");
    }

    int length=256;                                             //реальный размер таблицы

    BinaryReader reader;                                        //создаем читалку
    reader.attach(&in);                                         //прикрепляем к нему поток

    int readedBits=8;                                           //кол-во читаемых битов
    bool success;                                               //переменная для опереления конца файла
    unsigned short code;
    try
    {
        code=reader.read(readedBits,success);                   //читаем первый код
    }
    catch (const char* str)
    {
        throw str;
    }

    if (!success)                                               //если файл пуст
        return;                                                 //то отваливаемся

//    cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во бит: "<<readedBits<<endl;

    if (readedBits<size)                                        //если размер таблицы позволяет
        readedBits++;                                           //увеличиваем кол-во читаемых битов
    out.write(table.at(code).c_str(),table.at(code).size());    //получаем строку из кода и пишем её

    unsigned short old;                                         //предыдущий код
    while (1)                                                   //читаем файл
    {
        old=code;                                               //запоминаем пред. код
        try
        {
            code=reader.read(readedBits,success);               //читаем новый код
        }
        catch (const char* str)
        {
            throw str;
        }

        if (!success)                                           //если файл кончился
            return;                                             //то отваливаемся
        if (table[code]!="")                                    //если код есть в таблице
        {
            out.write(table.at(code).c_str(),table.at(code).size());    //получаем строку из кода и пишем её

//            cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во бит: "<<readedBits<<endl;

            if (length<tableSize)                               //если таблица не полная
            {
                table[length]=table.at(old)+table.at(code)[0];  //добавляем в таблицу
                length++;                                       //инкрементируем размер таблицы
            }
        }
        else                                                    //если кода в таблице нету
        {
            std::string tempStr=table.at(old)+table.at(old)[0]; //получаем строку
            out.write(tempStr.c_str(),tempStr.size());          //пишем её в поток

//            cerr<<"Прочтено: "<<code<<" Пишем: "<<table.at(code)<<" Кол-во бит: "<<readedBits<<endl;

            if (length<tableSize)                               //если таблица не полная
            {
                table[length]=tempStr;                          //добавляем в таблицу
                length++;                                       //инкрементируем размер таблицы
            }
        }

        if ((length & (length-1))==0 && readedBits<size)        //если можно и пора увеличить кол-во читаемых бит
        {
            readedBits++;                                       //увеличиваем его
        }
    }
}
