#include "sorter.h"
#include <cstdlib>

Cat Sorter::readOneCat(bool priorityInStream, bool &itsOk)
{
    Cat result;                                     //возвращаемое значение
    itsOk=true;                                     //инициализируем успех
    if (readedFromIn[int(priorityInStream)]<currentBufferSize)
    {                                               //если еще можно читать из этого потока
        ins[int(priorityInStream)]>>result;         //читаем

        if (!ins[int(priorityInStream)].eof())      //если конец файла не достигнут
        {
            readedFromIn[int(priorityInStream)]++;  //увеличиваем кол-во прочтенных с этого потока на 1
            return result;                          //отваливаемся
        }
    }
    //если не удалось прочитать с приоритетного потока
    if (readedFromIn[int(!priorityInStream)]<currentBufferSize)
    {                                               //если можем читать с оставшегося
        ins[int(!priorityInStream)]>>result;        //читаем

        if (!ins[int(!priorityInStream)].eof())     //если конец файла не достигнут
        {
            readedFromIn[int(!priorityInStream)]++; //увеличиваем кол-во прочтенных с этого потока на 1
            return result;                          //отваливаемся
        }
    }
    //если не удалось прочитать и со второго потока
    itsOk=false;                                    //говорим не удалось прочитать
    return result;                                  //отваливаемся
}

void Sorter::init()
{
    readedFromIn[0]=0;
    readedFromIn[1]=0;
    currentOut=false;
    outCounter=0;
    catForRead=false;
    currentBufferSize=1;
}

void Sorter::writeCatIntoCurrentOut(Cat ob)
{
    outs[int(currentOut)]<<ob;                      //пишем котика в текущий выходной поток
    outCounter++;                                   //увеличиваем кол-во записанных в этот поток
    if (outCounter==currentBufferSize*2)            //если оно равно удвоенному размеру буфера
    {
        currentOut=!currentOut;                     //переключаем поток
        outCounter=0;                               //зануляем кол-во записанных котиков
    }
}

void Sorter::openStreams()
{
    ins[0].open(nameIn1,std::ios::binary);          //открываем входные потоки
    ins[1].open(nameIn2,std::ios::binary);

    if (!ins[0].is_open() || !ins[1].is_open())     //если хоть один не открылся
    {
        throw "One of in files in cycle not open";  //откидываем exception
    }

    outs[0].open(nameOut1,std::ios::binary);        //открываем выходные потоки
    outs[1].open(nameOut2,std::ios::binary);

    if (!outs[0].is_open() || !outs[1].is_open())   //если хоть один не открылся
    {
        throw "One of out files in cycle not open"; //откидываем exception
    }
}

void Sorter::closeAndSwitchStreams()
{
    ins[0].close();                                 //закрываем потоки
    ins[1].close();
    outs[0].close();
    outs[1].close();

    std::string tempStr;

    tempStr=nameIn1;                                //свапаем имена
    nameIn1=nameOut1;
    nameOut1=tempStr;

    tempStr=nameIn2;
    nameIn2=nameOut2;
    nameOut2=tempStr;
}

bool Sorter::fileExists(std::string str)
{
    std::ifstream stream(str);
    bool result=stream.good();
    stream.close();
    return result;
}

void Sorter::split()
{
    std::ifstream in;                               //входной поток

    in.open(originalFileName,std::ios::binary);     //открываем его
    if (!in.is_open())                              //если не открылся
    {
        throw "In stream isn't open";               //откидываем exception
    }

    std::ofstream out1;                             //выходные потоки
    std::ofstream out2;
    out1.open(nameIn1);                             //открываем их
    out2.open(nameIn2);

    if (!out1.is_open() || !out2.is_open())         //если хоть один не открылся
    {
        throw "One of buffer files isn't open";     //откидываем exception
    }

    Cat tempCat;                                    //временный буфер

    for (unsigned int i=0; i<originalFileSize/2; ++i)
    {                                               //первую половину пишем в первый файл
        in>>tempCat;
        out1<<tempCat;
    }

    for (unsigned int i=originalFileSize/2; i<originalFileSize; ++i)
    {                                               //вторую половину пишем во второй файл
        in>>tempCat;
        out2<<tempCat;
    }

    in.close();                                     //закрываем потоки
    out1.close();
    out2.close();
}

Sorter::Sorter():
    originalFileSize(0),
    nameIn1("buffer1.dat"),
    nameIn2("buffer2.dat"),
    nameOut1("buffer3.dat"),
    nameOut2("buffer4.dat"),
    readedFromIn{0,0},
    currentOut(false),
    outCounter(0),
    catForRead(false),
    currentBufferSize(1)
{}

void Sorter::setFile(std::string fileName)
{
    originalFileName=fileName;                      //устанавливаем имя файла

    std::ifstream in;                               //входной поток

    in.open(originalFileName,std::ios::binary);     //открываем его
    if (!in.is_open())                              //если не открылся
    {
        throw "In stream isn't open";               //откидываем exception
    }

    in.seekg(0,in.end);                             //перемещаемся в конец файла
    originalFileSize=in.tellg()/CAT_SIZE;           //получаем кол-во котиков в файле

    in.close();                                     //закрываем поток
}

void Sorter::sort(bool (Cat::*compare)(const Cat& ob),std::string outFileName)
{
    split();                                                //разбиваем присоединенный файл на 2 части
    init();
    bool end=false;                                         //переменная для определения конца
    while (true)
    {                                                       //вроде и так норм
        openStreams();                                      //открываем соответствующие потоки на чтение и запись

        currentOut=false;                                   //инициализируем начальным выходным потоком первый
        outCounter=0;

        while (!ins[0].eof() || !ins[1].eof())              //пока не кончились файлы
        {
            readedFromIn[0]=0;                              //инициализируем кол-во прочтенных с потоков элементов
            readedFromIn[1]=0;

            bool check;                                     //переменная для проверки чтения
            catsBuffer[0]=readOneCat(0,check);              //читаем первого котика
            if (!check)                                     //если он не прочелся
            {
                break;                                      //то конец файла
            }
            catForRead=true;                                //говорим, что нужно начинать читать со второго котика

            while (true)                                    //пока не кончатся ячейки
            {
                catsBuffer[int(catForRead)]=readOneCat(catForRead,check);
                                                            //читаем котика, которого мы записали из буфера на пред. шаге
                if (!check)                                 //если не прочелся, значит ячейки кончились
                {
                    break;                                  //выходим из цикла
                }

                if ((catsBuffer[0].*compare)(catsBuffer[1]))//вызываем функцию сравнения, переданную как параметр
                {
                    writeCatIntoCurrentOut(catsBuffer[0]);  //пишем нужного котика
                    catForRead=false;                       //говорим,что его нужно перечитать в след. цикле
                }
                else
                {
                    writeCatIntoCurrentOut(catsBuffer[1]);  //пишем нужного котика
                    catForRead=true;                        //говорим,что его нужно перечитать в след. цикле
                }
            }

            writeCatIntoCurrentOut(catsBuffer[int(!catForRead)]);
                                                            //выписываем котика, который остался в буфере
        }

        closeAndSwitchStreams();                            //закрываем потоки и меняем им имена

        if (end)                                            //если конец
        {
            break;                                          //отваливаемся
        }
        currentBufferSize*=2;                               //удваиваем размер буфера
        std::cerr<<"Size of buffer: "<<currentBufferSize<<std::endl;
        if (currentBufferSize>originalFileSize/2)           //если размер буфера превзошел
        {                                                   //половину размера исходного файла
            end=true;                                       //говорим, что следующий цикл будет последним
        }

    }
    remove(nameOut1.c_str());                               //удаляем лишние файлы
    remove(nameOut2.c_str());
    remove(nameIn2.c_str());

    if (fileExists(outFileName))                           //если уже существует
    {
        remove(outFileName.c_str());                               //удаляем выходной файл
    }

    rename(nameIn1.c_str(),outFileName.c_str());                   //переименовываем оставшийся файл в выходной
}
