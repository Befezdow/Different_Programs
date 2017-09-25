#include "binarywriter.h"
#include <cstring>
//#include <iostream>

BinaryWriter::BinaryWriter()
{
    this->out=nullptr;
    this->buffer=0;
    this->currentBit=0;
}

BinaryWriter::~BinaryWriter()
{
    this->out=nullptr;
    this->buffer=0;
    this->currentBit=0;
}

void
BinaryWriter::attach(std::ofstream *stream)
{
    this->out=stream;
    this->buffer=0;
    this->currentBit=0;
}

void
BinaryWriter::detach()
{
    this->out=nullptr;
    this->buffer=0;
    this->currentBit=0;
}

std::ofstream*
BinaryWriter::getStream()
{
    return out;
}

std::string
BinaryWriter::toString(unsigned short code, int countOfBits)
{
    unsigned char bytes[2];                             //2 байта, которые будем анализировать
    memcpy(bytes,&code,2);                              //копируем в них инфу из short'а

    std::string str;                                    //возвращаемая строка

    for (int i=0;i<8;++i)                               //идем по 1 байту
    {
        if ((0b00000001<<i) & bytes[0])                 //записываем биты в строку
        {
            str+="1";
        }
        else
        {
            str+="0";
        }
    }

    countOfBits-=8;                                     //готовимся писать 2 байт

    for (int i=0;i<countOfBits;++i)                     //идем по 2 байту
    {
        if ((0b00000001<<i) & bytes[1])                 //записываем биты в строку
        {
            str+="1";
        }
        else
        {
            str+="0";
        }
    }

    return str;
}

void
BinaryWriter::writeNextBit(bool bit)
{
    if (bit)                                            //пишем бит в буфер
    {
        buffer=(0b00000001<<currentBit) | buffer;
    }

    currentBit++;                                       //инкрементируем текущий бит

    if (currentBit>7)                                   //если байт полный
    {
        (*out)<<buffer;                                 //пишем его в поток

        buffer=0;                                       //зануляем буфер
        currentBit=0;                                   //зануляем бит
    }
}

void
BinaryWriter::write(unsigned short code, int countOfBits)
{
    if (!out)                                           //если поток не прикреплен, то откидываем exception
    {
        throw "BinaryWriter: Stream isn't attached";
    }

    if (countOfBits<0 || countOfBits>16)
    {
        throw "BinaryReader: Unexpected count of bits";
    }

    std::string str=toString(code,countOfBits);         //преобразуем биты из short в строку

    for (unsigned int i=0;i<str.size();++i)             //идем по строке
    {
        this->writeNextBit(str[i]=='1');                //пишем биты в поток
    }

//    std::cerr<<"Writer: "<<str<<std::endl;
}

void
BinaryWriter::flush()
{
    if (!out)                                           //если поток не прикреплен, то откидываем exception
    {
        throw "BinaryWriter: Stream isn't attached";
    }

    if (currentBit!=0)                                  //если текущий бит
    {
        (*out)<<buffer;                                 //выкидываем буфкр в поток
        currentBit=0;                                   //инициализируем текущий бит
        buffer=0;                                       //инициализируем буфер
    }
}
