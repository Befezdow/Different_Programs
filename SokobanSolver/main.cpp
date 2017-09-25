#include "field.h"
#include "treenode.h"
#include <iostream>
#include <cmath>
#include <list>
#include <unistd.h>

std::vector<unsigned char>
readFromFile(std::ifstream &in,unsigned char& width,unsigned char& height)
{
    std::vector<std::string> lines;
    std::string tempStr;

    width=0;
    height=0;

    std::vector<unsigned char> result;

    while (true)
    {
        getline(in,tempStr);

        lines.push_back(tempStr);

        if (tempStr.size()>width)
        {
            width=tempStr.size();
        }

        height++;

        if (in.eof())
        {
            break;
        }
    }

    for (unsigned int i=0;i<lines.size();++i)
    {
        tempStr=lines.at(i);
        while (lines.at(i).size()<width)
        {
            lines[i]+=' ';
        }
    }

    for (unsigned int i=0;i<height;++i)
    {
        tempStr=lines.at(i);
        for (unsigned int j=0;j<width;++j)
        {
            unsigned char c=tempStr.at(j);

            if (c!='#' && c!='$' && c!='o' && c!='X' && c!=' ' && c!='*')
            {
                throw "Unknown symbol on map";
            }

            result.push_back(c);
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc!=2)                                    //если не задана карта
    {
        std::cerr<<"Incorrect count of arguments"<<std::endl;
        return 1;                                   //отваливаемся
    }
    std::ifstream in;                               //поток ввода
    in.open(argv[1]);                               //открываем его
    if (!in.is_open())                              //если не открылся
    {
        std::cerr<<"Map not open"<<std::endl;
        return 1;                                   //отваливаемся
    }

    std::vector<unsigned char> vec;                 //вектор для символов карты
    unsigned char width;                            //ширина поля
    unsigned char height;                           //высота поля

    try
    {
        vec=readFromFile(in,width,height);          //читаем карту в вектор
    }
    catch (const char* str)
    {
        std::cerr<<str<<std::endl;
        return 1;
    }

    StaticField sf(vec,width,height);               //создаем статическое поле
    DynamicField::setStField(&sf);                  //устанавливаем его

    std::vector<bool> check(pow(width*height,sf.getBoxesCount()+1));
                                                    //создаем вектор для проверки повторов
    std::list<TreeNode> tree;                       //вектор для хранения узлов дерева
    DynamicField df(vec);                           //исходное динамическое поле

    std::cout<<"Ширина: "<<(unsigned int)width<<std::endl;
    std::cout<<"Высота: "<<(unsigned int)height<<std::endl;
    std::cout<<"Исходное поле: "<<std::endl;
    df.print();                                     //выводим исходное поле

    if (df.checkForWin())                           //проверяем исходное поле на победу
    {
        std::cout<<"Win on start!"<<std::endl;
        return 0;
    }

    tree.push_back(TreeNode(df,nullptr));           //засовываем исходное поле в дерево
    check[df.getCheckIndex()]=true;                 //ставим, что мы в нем были

    std::list<TreeNode>::iterator currentNode=tree.begin();
                                                    //текущий рассматриваемый узел
    bool found=false;                               //флаг о победе

    while (!found)                                  //пока не победа
    {
        if (currentNode==tree.end())                //если перебрали все, что можно
        {
            break;                                  //отваливаемся
        }

        for (int i=DynamicField::Start; i<DynamicField::End; ++i)   //бежим по всем направлениям
        {
            DynamicField f = currentNode->getField();               //получаем поле из тек. узла
            bool status=f.move(i);                                  //двигаем игрока

            if (status)                                             //если подвинулся
            {
                unsigned long long checkIndex=f.getCheckIndex();    //получаем индкс поля
                if (!check.at(checkIndex))                          //если мы в этом состоянии не были
                {
                    check[checkIndex]=true;                         //ставим, что были
                    TreeNode newTreeNode(f,&(*currentNode));        //создаем новый узел дерева
                    tree.push_back(newTreeNode);                    //кидаем его в дерево

                    if (f.checkForWin())                            //если выйграли
                    {
                        found=true;                                 //меняем флаг
                        break;                                      //отваливаемся
                    }
                }
            }
        }
        currentNode++;                                              //инкрементируем текущий узел
    }

    if (found)                                                      //если нашли победу
    {
        std::cout<<"The way has been found!"<<std::endl;
        sleep(1);                                                   //ждем 1 секунду
        tree.back().printWinnerWay();                               //пишем победную стратегию
    }
    else
    {
        std::cout<<"The way hasn't been found :("<<std::endl;
    }

    return 0;
}
