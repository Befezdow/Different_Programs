#include "binaryreader.h"

using namespace std;

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

void
BinaryReader::attach(std::istream* stream)
{
    in=stream;
    buffer=0;
    currentBit=8;
}

void
BinaryReader::detach()
{
    in=nullptr;
    buffer=0;
    currentBit=8;
}

std::istream*
BinaryReader::getStream()
{
    return in;
}

void
BinaryReader::setReadTree(BinaryTree* tree)
{
    readTree=tree;
}

BinaryTree*
BinaryReader::getReadTree()
{
    return readTree;
}

bool
BinaryReader::readNextBit()
{
    if (!this->in)
    {
        throw "BinaryReader::readNextBit: Stream is'n attached";
    }
    if (currentBit>7)
    {
        buffer=in->get();
        if (in->eof())
        {
            throw "BinaryReader::readNextBit: The end of the file has been reached";
        }
        currentBit=0;
    }
    bool result=bool((0b10000000>>currentBit) & buffer);
    currentBit++;
    return result;
}

char
BinaryReader::read()
{
    std::shared_ptr<TreeItem>  cur=readTree->getRoot();
    while (cur->firstChild || cur->secondChild)
    {
        bool turn;
        try
        {
            turn=readNextBit();
        }
        catch (const char* str)
        {
            throw str;
        }

        if (!turn)
        {
            if (cur->firstChild)
            {
                cur=cur->firstChild;
            }
            else
            {
                throw "BinaryReader::read: Unknown path";
            }
        }
        else
        {
            if (cur->secondChild)
            {
                cur=cur->secondChild;
            }
            else
            {
                throw "BinaryReader::read: Unknown path";
            }
        }
    }
    return cur->getSymbol();
}
