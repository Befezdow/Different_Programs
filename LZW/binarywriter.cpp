#include "binarywriter.h"
#include <cstring>
#include <iostream>

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
    unsigned char bytes[2];
    memcpy(bytes,&code,2);

    std::string str;                                    //возвращаемая строка

    for (int i=0;i<8;++i)
    {
        if ((0b00000001<<i) & bytes[0])
            str+="1";
        else
            str+="0";
    }

    countOfBits-=8;

    for (int i=0;i<countOfBits;++i)
    {
        if ((0b00000001<<i) & bytes[1])
            str+="1";
        else
            str+="0";
    }

    return str;
}

void
BinaryWriter::writeNextBit(bool bit)
{
    if (bit)
    {
        buffer=(0b10000000>>currentBit) | buffer;
    }
    currentBit++;
    if (currentBit>7)
    {
        (*out)<<buffer;
        buffer=0;
        currentBit=0;
    }
}

void
BinaryWriter::write(unsigned short code, int countOfBits)
{
    std::string str=toString(code,countOfBits);
    for (unsigned int i=0;i<str.size();++i)
        this->writeNextBit(str[i]=='1');
    std::cerr<<"Writer: "<<str<<std::endl;
}

void
BinaryWriter::flush()
{
    if (currentBit!=0)
    {
        if (out)
        {
            (*out)<<buffer;
        }
        currentBit=0;
        buffer=0;
    }
}
