#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>

class BinaryReader
{
    char buffer;
    int currentBit;
    std::ifstream* in;

    bool readNextBit();
public:
    BinaryReader();
    ~BinaryReader();
    void attach(std::ifstream *stream);
    void detach();
    std::istream *getStream() const;
    unsigned short read(int countOfBits);
};

#endif // BINARYREADER_H
