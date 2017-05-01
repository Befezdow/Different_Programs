#include "binaryreader.h"
#include <cstring>
#include <iostream>

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

bool BinaryReader::readNextBit()
{
    if (currentBit>7)
    {
        buffer=in->get();
        if (in->eof())
        {
//            throw "BinaryReader::readNextBit: The end of the file has been reached";
        }
        currentBit=0;
    }
    bool result=bool((0b10000000>>currentBit) & buffer);
    currentBit++;
    return result;
}

unsigned short BinaryReader::read(int countOfBits)
{
    std::cerr<<"Reader: ";
    unsigned char bytes[2]={0b00000000,0b00000000};
    for (int i=0;i<8;++i)
    {
        if (readNextBit())
        {
            bytes[0]=((0b00000001<<i) | bytes[0]);
            std::cerr<<"1";
        }
        else
            std::cerr<<"0";
    }
    countOfBits-=8;
    for (int i=0;i<countOfBits;++i)
    {
        if (readNextBit())
        {
            bytes[1]=((0b00000001<<i) | bytes[1]);
            std::cerr<<"1";
        }
        else
            std::cerr<<"0";
    }
    std::cerr<<std::endl;
    unsigned short result;
    memcpy(&result,bytes,2);
//    std::cerr<<int(bytes[0])<<" "<<int(bytes[1])<<std::endl;
    return result;
}
