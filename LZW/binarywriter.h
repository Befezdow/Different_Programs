#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <fstream>

class BinaryWriter
{
    std::ofstream* out;
    char buffer;
    int currentBit;

    void writeNextBit(bool bit);
    std::string toString(unsigned short code, int countOfBits);

public:
    BinaryWriter();
    ~BinaryWriter();
    void attach(std::ofstream* stream);
    void detach();
    std::ofstream* getStream();
    void write(unsigned short code, int countOfBits);
    void flush();
};

#endif // BINARYWRITER_H
