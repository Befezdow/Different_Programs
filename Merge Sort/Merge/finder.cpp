#include "finder.h"

int
Finder::comparePartOfName(Cat ob, std::string partOfName) const
{
    std::string sub=ob.getName().substr(0,partOfName.size());   //получаем начало имени

    if (sub==partOfName)                                        //если совпало
    {
        return 0;
    }

    if (sub>partOfName)                                         //если больше
    {
        return 1;
    }
                                                                //если меньше
    return -1;
}

int
Finder::compareBreed(Cat ob, std::string breed) const
{
    std::string obBreed=ob.getBreed();                          //получаем породу

    if (obBreed==breed)                                         //если совпало
    {
        return 0;
    }

    if (obBreed>breed)                                          //если больше
    {
        return 1;
    }
                                                                //если меньше
    return -1;
}

int
Finder::compareAge(Cat ob, std::string age) const
{
    unsigned int ageNumber=stoi(age);                           //преобразуем в число
    unsigned int obAge=ob.getAge();                             //получаем возраст

    if (obAge==ageNumber)                                       //если совпало
    {
        return 0;
    }

    if (obAge>ageNumber)                                        //если больше
    {
        return 1;
    }
                                                                //если меньше
    return -1;
}

long long
Finder::findFirstOfThem(int (Finder::*compare)(Cat, std::string) const, std::string findValue, std::ifstream &in) const
{
    in.seekg(0,in.end);                                     //получаем кол-во котиков в файле
    unsigned int countOfCats=in.tellg()/CAT_SIZE;

    unsigned int bottom=countOfCats;                        //нижняя граница
    unsigned int top=0;                                     //верхняя граница

    Cat temp;                                               //временная переменная
    unsigned int currentPos;                                //текущая позиция в файле

    while (true)
    {
        currentPos=(bottom-top)/2+top;                      //получаем середину интервала
        if (currentPos==top)                                //если интервал минимален
        {
            return -1;                                      //говорим, что не нашли элемент
        }
        in.seekg(currentPos*CAT_SIZE,in.beg);               //перемещаемся на текущую позицию
        in>>temp;                                           //читаем котика

        int val=(this->*compare)(temp,findValue);           //ставниваем занчения

        if (val==0)                                         //если нашли
        {
            break;                                          //останавливаем цикл
        }
        else if (val>0)                                     //если значение в котике больше
        {
            bottom=currentPos;                              //берем
        }
        else                                                //если меньше
        {
            top=currentPos;
        }
    }

    unsigned int topLine=currentPos;                        //инициализируем верхнюю линию

    while ((this->*compare)(temp,findValue)==0)             //пока значение не перестанет совпадать
    {
        if (topLine==0)                                     //если это предел
        {
            break;                                          //прерываем цикл
        }

        topLine--;                                          //поднимаем линию
        in.seekg(topLine*CAT_SIZE,in.beg);                  //пепемещаемся на неё
        in>>temp;                                           //читаем котика
    }
    if (topLine!=0)                                         //если это был не потолок
    {
        topLine++;                                          //опускаемся внз на 1
    }

    return topLine;                                         //возвраем верхнюю линию с поисковым значением
}

Finder::Finder(std::string sbn, std::string sbb, std::string sba):
    sortedByName(sbn),
    sortedByBreed(sbb),
    sortedByAge(sba)
{}

void
Finder::attachNameFile(std::string fileName)
{
    sortedByName=fileName;
}

void
Finder::attachBreedFile(std::string fileName)
{
    sortedByBreed=fileName;
}

void
Finder::attachAgeFile(std::string fileName)
{
    sortedByAge=fileName;
}

void
Finder::findByNameBeginning(std::string nameBeginning) const
{
    std::ifstream in;                                   //поток ввода
    in.open("sortedByName.dat");                        //открываем
    if (!in.is_open())                                  //если не открылся
    {
        throw "sortedByName.dat isn't open";            //отваливаемся
    }

    long long topLine=Finder::findFirstOfThem(&Finder::comparePartOfName,nameBeginning,in);
    if (topLine==-1)                                    //ищем верхнюю линию, если не нашли
    {
        std::cout<<"Element not found"<<std::endl;      //говорим, что не нашли
        return;
    }

    in.seekg(topLine*CAT_SIZE,in.beg);                  //перемещаемся в начало чтения

    Cat temp;                                           //временная переменная
    int sizeOfBeginning=nameBeginning.size();           //размер начала имени
    while (true)                                        //выводим элементы
    {
        in>>temp;                                       //читаем котика
        std::string sub=temp.getName().substr(0,sizeOfBeginning);
                                                        //получаем подстроку из имени
        if (sub!=nameBeginning || in.eof())             //если строки не совпадают или конец файла
        {
            break;                                      //отваливаемся
        }
        temp.print();                                   //если не отвалились, пишем котика
    }
}

void
Finder::findByBreed(std::string findBreed) const
{
    std::ifstream in;                                   //поток ввода
    in.open("sortedByBreed.dat");                       //открываем его
    if (!in.is_open())                                  //если не открылся
    {
        throw "sortedByBreed.dat isn't open";           //отваливаемся
    }

    long long topLine=Finder::findFirstOfThem(&Finder::compareBreed,findBreed,in);
    if (topLine==-1)                                    //ищем верхнюю линию, если не нашли
    {
        std::cout<<"Element not found"<<std::endl;      //говорим, что не нашли
        return;
    }

    in.seekg(topLine*CAT_SIZE,in.beg);                  //перемещаемся в начало чтения

    Cat temp;                                           //временная переменная
    while (true)                                        //выводим элементы
    {
        in>>temp;                                       //читаем котика
        if (temp.getBreed()!=findBreed || in.eof())     //если порода не совпала или файл кончился
        {
            break;                                      //отваливаемся
        }
        temp.print();                                   //выводим котика
    }
}

void
Finder::findByAgeInterval(unsigned int min, unsigned int max) const
{
    if (min>max)                                        //если недопустимые значения
    {
        return;                                         //отваливаемся
    }

    std::ifstream in;                                   //поток ввода
    in.open("sortedByAge.dat");                         //открываем его
    if (!in.is_open())                                  //если не открылся
    {
        throw "sortedByAge.dat isn't open";             //отваливаемся
    }

    long long topLine=Finder::findFirstOfThem(&Finder::compareAge,std::to_string(min),in);
    if (topLine==-1)                                    //ищем верхнюю линию, если не нашли
    {
        std::cout<<"Element not found"<<std::endl;      //говорим, что не нашли
        return;
    }

    in.seekg(topLine*CAT_SIZE,in.beg);                  //перемещаемся в начало чтения

    Cat temp;                                           //временная переменная
    while (true)                                        //выводим элементы
    {
        in>>temp;                                       //читаем котика
        if (temp.getAge()>max || in.eof())              //если возраст не подходит или конец файла
        {
            break;                                      //отваливаемся
        }
        temp.print();                                   //пишем котика
    }
}
