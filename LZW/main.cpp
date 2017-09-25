#include "archivator.h"
#include "hash.h"
#include "hash2.h"
#include "binarywriter.h"
#include "binaryreader.h"
#include <iostream>
#include <vector>
#include <strstream>
#include <cmath>
#include <cstring>

int main(int argc, char *argv[])
{
    if (argc<2)                                         //проверяем кол-во аргументов
    {
        std::cerr<<"Incorrect count of parameters"<<std::endl;
        return 1;
    }

    if (strcmp(argv[1],"-c")==0)
    {
        if (argc!=5)
        {
            std::cerr<<"Incorrect count of parameters"<<std::endl;
            return 1;
        }

        std::strstream s;                               //получаем размер таблицы
        s<<argv[4];
        int size;
        s>>size;

        if (size<8 || size>16)                          //проверяем размер
        {
            std::cerr<<"Incorrect size of table"<<std::endl;
            return 1;
        }

        std::ifstream in;                               //поток на вход
        in.open(argv[2],std::ios::in | std::ios::binary);     //открываем его

        if (!in.is_open())                              //если не открылся
        {
            std::cerr<<"In file not open"<<std::endl;
            return 1;                                   //отваливаемся
        }

        std::ofstream out;                              //поток на выход
        out.open(argv[3],std::ios::out | std::ios::binary);   //открываем его

        if (!out.is_open())                             //если не открылся
        {
            std::cerr<<"Out file not open"<<std::endl;
            return 1;                                   //отваливаемся
        }

        try
        {
            Archivator::compress2(in,out,size);         //осуществляем сжатие
        }
        catch (const char* str)
        {
            std::cerr<<"Interception of error:"<<std::endl;
            std::cerr<<str<<std::endl;
            std::terminate();
        }

        in.close();                                     //закрываем входной поток
        out.close();                                    //закрываем выходной поток

    }
    else if (strcmp(argv[1],"-d")==0)
    {
        if (argc!=4)
        {
            std::cerr<<"Incorrect count of parameters"<<std::endl;
            return 1;
        }

        std::ifstream in;
        in.open(argv[2],std::ios::in | std::ios::binary);
        if (!in.is_open())
        {
            std::cerr<<"Out2 file not open"<<std::endl;
            return 1;
        }

        std::ofstream out;
        out.open(argv[3],std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr<<"Result file not open"<<std::endl;
            return 1;
        }

        try
        {
            Archivator::uncompress(in,out);             //осуществляем распаковку
        }
        catch (const char* str)
        {
            std::cerr<<"Interception of error:"<<std::endl;
            std::cerr<<str<<std::endl;
            std::terminate();
        }

        in.close();                                     //закрываем входной поток
        out.close();                                    //закрываем выходной поток
    }
    else
    {
        std::cerr<<"Unknown key"<<std::endl;
        return 1;
    }

    return 0;
}
