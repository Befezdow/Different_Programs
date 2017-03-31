#ifndef SYMBOLSCOUNTER_H
#define SYMBOLSCOUNTER_H

#include <vector>
#include <fstream>

class SymbolsCounter
{
public:
    static std::vector<int> getSymbolsCount(std::ifstream& file);
    static void printSymbols(std::vector<int> vec);
};

#endif // SYMBOLSCOUNTER_H
