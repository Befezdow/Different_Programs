#ifndef SYMBOLCODE_H
#define SYMBOLCODE_H

class SymbolCode
{
    long long code;
    unsigned char length;
    void addBit(bool bit);
    std::vector<bool> getCode(int i);
};

#endif // SYMBOLCODE_H
