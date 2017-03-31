#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <map>
#include <iostream>
#include <string>

class BinaryWriter
{
    std::map<char,std::string> encoding;
    std::ostream* out;
    char buffer;
    int currentBit;

    void writeNextBit(bool bit);
public:
    BinaryWriter();
    ~BinaryWriter();
    void attach(std::ostream* stream);
    void detach();
    std::ostream* getStream();
    void setEncoding(std::map<char,std::string> encod);
    std::map<char,std::string> getEncoding();
    void write(char symbol);
    void flush();
};

#endif // BINARYWRITER_H
