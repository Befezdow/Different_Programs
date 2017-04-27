#include "binarywriter.h"

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
    char byte1=((char*)&code)[0];                       //получаем первый байт
    char byte2=((char*)&code)[1];                       //получаем второй байт

    std::string str;                                    //возвращаемая строка

    for (int i=0;i<8;++i)
    {
        if ((0b00000001<<i) & byte1)
            str+="1";
        else
            str+="0";
    }

    countOfBits-=8;

    for (int i=0;i<countOfBits;++i)
    {
        if ((0b00000001<<i) & byte2)
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
