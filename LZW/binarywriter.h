#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <fstream>

class BinaryWriter                                  //битовая писалка
{
    std::ofstream* out;                             //выходной поток
    char buffer;                                    //буфер, который копим, а потом выдаем
    int currentBit;                                 //текущий бит в буфере (кухня чтения)

    void writeNextBit(bool bit);                    //записать следующий бит (параметр - этот бит)
    std::string toString(unsigned short code, int countOfBits);
                                                    //преобразовать указанное кол-во байт из short в строку (нужно для кухни)
public:
    BinaryWriter();
    ~BinaryWriter();
    void attach(std::ofstream* stream);             //присоединить поток к врайтеру
    void detach();                                  //отсоединить поток
    std::ofstream* getStream();                     //получить прикрепленный поток
    void write(unsigned short code, int countOfBits);
                                                    //записать указанное кол-во бит из short
    void flush();                                   //добивает остаток до байта и выкидывает в поток
};

#endif // BINARYWRITER_H
