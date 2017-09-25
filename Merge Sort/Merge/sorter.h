#ifndef SORTER_H
#define SORTER_H

#include "cat.h"
#include <functional>

class Sorter
{
    std::string originalFileName;           //имя исходного файла
    unsigned int originalFileSize;          //кол-во котиков в исходном файле

    std::string nameIn1;                    //имя первого входного потока
    std::string nameIn2;                    //имя второго входного потока
    std::string nameOut1;                   //имя первого выходного потока
    std::string nameOut2;                   //имя второго выходного потока
    //не стоит привязыватся к названиям входной и выходной,
    //так как они все равно будут меняться ролями

    std::ifstream ins[2];                   //входные потоки
    std::ofstream outs[2];                  //выходные потоки
    unsigned int readedFromIn[2];           //кол-во элементов, прочтеных с потоков
    bool currentOut;                        //текущий выходной поток
    unsigned int outCounter;

    Cat catsBuffer[2];                      //буфер котиков
    bool catForRead;                        //котик, которого нужно перечитать

    unsigned currentBufferSize;             //текущий размер буфера

    Cat readOneCat(bool priorityInStream, bool& itsOk);
                                            //читает котика, первый параметр - приоритетный поток
                                            //второй - успешность прочтения

    void init();                            //инициализирует переменные сортировки
    void writeCatIntoCurrentOut(Cat ob);    //пишет котика, меняет текущий выходной поток
    void openStreams();                     //открывает потоки ввода и вывода
    void closeAndSwitchStreams();           //закрывает потоки ввода и вывода
                                            //свапает названия входных и выходных потоков

    bool fileExists(std::string str);       //проверяет, существует ли файл
    void split();                           //разделяет прикрепленный файл на 2 части

public:
    Sorter();

    void setFile(std::string fileName);     //функция присоединения файла к сортировщику
    void sort(bool (Cat::*compare)(const Cat& ob), std::string outFileName);
                                            //сама функция сортировки, параметр - функция сравнения котиков
};

#endif // SORTER_H
