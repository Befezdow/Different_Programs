#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include <fstream>

class Archivator
{
public:
    static void compress(std::ifstream& in, std::ofstream& out, int sizeOfHash);
    static void compress2(std::ifstream& in, std::ofstream& out, int sizeOfHash);
    static void uncompress(std::ifstream& in, std::ofstream& out);
};

#endif // ARCHIVATOR_H
