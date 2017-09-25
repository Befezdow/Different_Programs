#include "sorter.h"
#include "finder.h"
#include <cstdio>

using namespace std;

void sortData(std::string fileName,std::string outName,std::string outBreed,std::string outAge)
{           //сортирует данные из файла fileName и помещает их в три выходных файла
    Sorter sorter;                              //сортировщик
    sorter.setFile(fileName);                   //устанавливаем ему входной файл

    sorter.sort(&Cat::lessByName,outName);      //сортируем по имени
    sorter.sort(&Cat::lessByBreed,outBreed);    //сортируем по породе
    sorter.sort(&Cat::lessByAge,outAge);        //сортируем по возрасту

/*
    cout<<"Итог:"<<endl;
    Cat cat;
    ifstream in;
    in.open(outAge,ios::binary);
    for (int i=0; i<100; ++i)
    {
        in>>cat;
        cout<<i<<" ";
        cat.print();
    }
    in.close();
*/
}

int main(int argc, char *argv[])
{
    if (argc!=4)
    {
        cerr<<"Unexpected count of parameters"<<endl;
        return 1;
    }

    sortData(argv[1],"sortedByName.dat","sortedByBreed.dat","sortedByAge.dat");
                                                                //вызываем сортировку
    Finder finder;                                              //поисковик
    finder.attachNameFile("sortedByName.dat");                  //прикрепляем sorted файл с именами
    finder.attachBreedFile("sortedByBreed.dat");                //прикрепляем sorted файл с породами
    finder.attachAgeFile("sortedByAge.dat");                    //прикрепляем sorted файл с возрастами

    cout<<"Find by age: "<<endl;
    finder.findByAgeInterval(atoi(argv[2]),atoi(argv[3]));

    return 0;
}
