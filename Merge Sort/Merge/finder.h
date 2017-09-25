#ifndef FINDER_H
#define FINDER_H

#include "cat.h"

class Finder
{
    std::string sortedByName;                   //имя отсортиованного файла с именами
    std::string sortedByBreed;                  //имя отсортиованного файла с породами
    std::string sortedByAge;                    //имя отсортиованного файла с возрастами

    //эти три функции - адаптации поиска под один шаблон
    int comparePartOfName(Cat ob,std::string partOfName) const; //сравнить начало имени
    int compareBreed(Cat ob,std::string breed) const;           //сравнить породу
    int compareAge(Cat ob,std::string age) const;               //сравнить возраст

    long long findFirstOfThem(int (Finder::*compare)(Cat,std::string) const, std::string findValue, std::ifstream &in) const;
                //функция находит номер строки какого-нить из нужных элементов если он есть, иначе возвращет -1
                //первый параметр - функция сравнения элемента и поискового значения
                //второй параметр - поисковое значение
                //третий параметр - входной поток, по которому происходит поиск
public:
    Finder(std::string sbn="",std::string sbb="",std::string sba="");

    void attachNameFile(std::string fileName);  //прикрепляет отсортированный файл с именами
    void attachBreedFile(std::string fileName); //прикрепляет отсортированный файл с породами
    void attachAgeFile(std::string fileName);   //прикрепляет отсортированный файл с возрастами

    void findByNameBeginning(std::string nameBeginning) const;          //поиск по началу имени
    void findByBreed(std::string findBreed) const;                      //поиск по породе
    void findByAgeInterval(unsigned int min, unsigned int max) const;   //поиск по интервалу возрастов
};

#endif // FINDER_H
