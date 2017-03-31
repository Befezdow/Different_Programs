#ifndef BINARYREADER_H
#define BINARYREADER_H

#include "binarytree.h"
#include <iostream>

class BinaryReader
{
    char buffer;
    int currentBit;
    std::istream* in;
    BinaryTree* readTree;

    bool readNextBit();
public:
    BinaryReader();
    ~BinaryReader();
    void attach(std::istream* stream);
    void detach();
    std::istream* getStream();
    void setReadTree(BinaryTree* tree);
    BinaryTree* getReadTree();
    char read();
};

#endif // BINARYREADER_H
