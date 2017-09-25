#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>

class BinaryReader                          //битовая читалка
{
    char buffer;                            //буфер, который мы накапливаем, а потом выдаем
    int currentBit;                         //текущий бит (нужен для буфера)
    std::ifstream* in;                      //входной поток

    bool readNextBit(bool &success);        //возвращает бит, второй параметр - успех операции
                                            //(true - прочитал, false - не прочитал)
public:
    BinaryReader();
    ~BinaryReader();
    void attach(std::ifstream *stream);     //прикрепить входной поток к ридеру
    void detach();                          //открепить входной поток
    std::istream *getStream() const;        //получить прикрепленный поток
    unsigned short read(int countOfBits, bool &success);
};                                          //функция чтения указанного кол-ва бит записаннх в short
                                            //второй параметр аналогичен readNextBit

#endif // BINARYREADER_H
