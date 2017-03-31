#include "binarywriter.h"

using namespace std;

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
BinaryWriter::attach(ostream* stream)
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

ostream*
BinaryWriter::getStream()
{
    return out;
}

void
BinaryWriter::setEncoding(map<char,string> encod)
{
    this->encoding=encod;
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
BinaryWriter::write(char symbol)
{
    if (!out)
    {
        throw "BinaryWriter::write: Stream is'n attached";
    }
    if (encoding.find(symbol)==encoding.end())
    {
        throw "BinaryWriter::write: Out of range";
    }
    string code=encoding.at(symbol);
    for (unsigned int i=0;i<code.size();++i)
    {
        writeNextBit(code.at(i)=='1');
    }
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
