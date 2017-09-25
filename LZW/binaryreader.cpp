#include "binaryreader.h"
#include <cstring>
//#include <iostream>

BinaryReader::BinaryReader()
{
    in=nullptr;
    buffer=0;
    currentBit=8;
}

BinaryReader::~BinaryReader()
{
    in=nullptr;
    buffer=0;
    currentBit=8;
}

void BinaryReader::attach(std::ifstream *stream)
{
    in=stream;
    buffer=0;
    currentBit=8;
}

void BinaryReader::detach()
{
    in=nullptr;
    buffer=0;
    currentBit=8;
}

std::istream *BinaryReader::getStream() const
{
    return in;
}

bool BinaryReader::readNextBit(bool& success)
{
    success=true;                       //инициализируем успех операции
    if (currentBit>7)                   //если кол-во бит превышает длину байта
    {
        buffer=in->get();               //получаем новый байт

        if (in->eof())                  //если конец входного потока
        {
            success=false;              //то откидываем ошибку чтения
            return false;
        }

        currentBit=0;                   //текущий бит ставим нулем
    }
    bool result=bool((0b00000001<<currentBit) & buffer);    //читаем бит
    currentBit++;                       //икрементируем текущий бит
    return result;
}

unsigned short BinaryReader::read(int countOfBits,bool& success)
{
    if (!in)
    {
        throw "BinaryReader: Stream isn't attached";
    }

    if (countOfBits<0 || countOfBits>16)
    {
        throw "BinaryReader: Unexpected count of bits";
    }

    success=true;                       //инициализируем успех операции

//    std::cerr<<"Reader: ";

    unsigned char bytes[2]={0b00000000,0b00000000}; //инициализируем возвращаемые байты

//    std::string code1;
    for (int i=0;i<8;++i)               //идем по 1 байту
    {
        bool bit=readNextBit(success);  //читаем бит

        if (!success)                   //если ошибка чтения
        {
            return 0;                   //откидываемся
        }

        if (bit)                        //пишем бит в 1 байт
        {
            bytes[0]=((0b00000001<<i) | bytes[0]);
//            code1="1"+code1;
        }
//        else
//        {
//            code1="0"+code1;
//        }
    }

    countOfBits-=8;                     //готовимся читать второй байт

//    std::string code2;
    for (int i=0;i<countOfBits;++i)     //идем по 2 байту
    {
        bool bit=readNextBit(success);  //читаем бит

        if (!success)                   //если ошибка чтения
        {
            return 0;                   //откидываемся
        }

        if (bit)                        //пишем бит во 2 байт
        {
            bytes[1]=((0b00000001<<i) | bytes[1]);
//            code2="1"+code2;
        }
//        else
//        {
//            code2="0"+code2;
//        }
    }
//    std::cerr<<code1+" "+code2<<std::endl;

    unsigned short result;              //возвращаемое значение
    memcpy(&result,bytes,2);            //копируем инфу из 2 байт в short
    return result;
}
