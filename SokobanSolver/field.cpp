#include "field.h"
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>

StaticField::StaticField(std::vector<unsigned char> map,int width,int height):
    boxesCount(0),
    fieldWidth(width),
    fieldHeight(height)
{
    //TODO чекнуть размер вектора на out of memory
    for (unsigned int i=0;i<map.size();++i)             //идем по вектору с символами
    {
        unsigned char c=map.at(i);                      //получаем символ
        if (c=='#')                                     //если это стена
        {
            walls.push_back(true);                      //ставим на этой позиции стену
        }
        else                                            //иначе
        {
            walls.push_back(false);                     //ставим что стены нету
        }

        if (c=='o' || c=='*')                           //если это место под ящик
        {
            places.push_back(true);                     //ставим на этой позиции место
        }
        else                                            //иначе
        {
            places.push_back(false);                    //ставим что его нету
        }
        if (c=='$' || c=='*')                           //если это ящик
        {
            boxesCount++;                               //увеличиваем кол-во ящиков на 1
        }
    }
}

bool
StaticField::checkPlaceAt(unsigned char i) const
{
    return places.at(i);                            //возвращаем, есть ли место
}

bool
StaticField::checkWallAt(unsigned char i) const
{
    return walls.at(i);                             //возвращаем, есть ли стена
}

unsigned char
StaticField::getBoxesCount() const
{
    return boxesCount;
}

unsigned char
StaticField::getFieldWidth() const
{
    return fieldWidth;
}

unsigned char
StaticField::getFieldHeight() const
{
    return fieldHeight;
}

StaticField* DynamicField::stField=nullptr;             //инициализируем указатель

DynamicField::DynamicField(std::vector<unsigned char> map)
{
    int count=0;                                        //счетчик для массива коробок

    for (unsigned char i=0;i<map.size();++i)            //идем по вектору
    {
        unsigned char c=map.at(i);                      //получаем символ

        if (c=='$' || c=='*')                           //если это коробка
        {
            boxes[count]=i;                             //добавляем ящик
            count++;                                    //увеличиваем счетчик на 1
        }
        if (c=='X')                                     //если это игрок
        {
            playerPos=i;                                //устанавливаем игрока
        }
    }
}

int DynamicField::checkBoxAt(unsigned char c) const
{
    unsigned char boxesCount=stField->getBoxesCount();  //получаем кол-во коробок
    for (unsigned int i=0;i<boxesCount;++i)             //идем по массиву коробок
    {
        if (boxes[i]==c)                                //если позиции совпадают
        {
            return i;                                   //возвращаем индекс в массиве
        }
    }
    return -1;                                          //иначе возвращаем -1
}

bool
DynamicField::move(int md)
{
    int delta;                                          //смещение
    switch (md)                                         //смотрим направление и ставим смещение
    {
    case DynamicField::Up:
        delta=-stField->getFieldWidth();
        break;
    case DynamicField::Down:
        delta=stField->getFieldWidth();
        break;
    case DynamicField::Left:
        delta=-1;
        break;
    case DynamicField::Right:
        delta=1;
        break;
    default:
        return false;
    }

    unsigned char newPlayerPos=playerPos+delta;         //определяем новую позицию
    bool nextIsClear=true;                              //инициализируем, что в новой позиции нет ящика

    if (stField->checkWallAt(newPlayerPos))             //если на новой позиции стена
    {
        return false;                                   //отваливаемся
    }

    int temp=checkBoxAt(newPlayerPos);                  //смотрим, есть ли коробка на новом месте
    if (temp!=-1)
    {
        nextIsClear=false;                              //ставим, что на новой позиции ящик

        if (checkBoxAt(newPlayerPos+delta)!=-1 || stField->checkWallAt(newPlayerPos+delta))
        {                                               //если за ним что-то есть
            return false;                               //отваливаемся
        }
    }

    if (nextIsClear)                                    //если на новой позиции нет коробки
    {
        playerPos=newPlayerPos;                         //перемещаем игрока
    }
    else                                                //иначе
    { 
        boxes[temp]=(unsigned char)(newPlayerPos+delta);//перемещаем коробку
        playerPos=newPlayerPos;                         //перемещаем игрока

        if (checkForLose(newPlayerPos+delta))           //если ход проигрышный
        {
            return false;                               //отваливаемся
        }

    }

    return true;                                        //говорим, что сходили успешно
}

void
DynamicField::print() const
{
    const unsigned char width=stField->getFieldWidth(); //получаем ширину
    const unsigned int size=width*stField->getFieldHeight();
                                                        //получаем размер поля
    int count=0;                                        //счетчик символов

    for (unsigned char i=0;i<size;++i)                  //идем по полю
    {
        if (checkBoxAt(i)!=-1)                          //если на позиции коробка
        {
            if (stField->checkPlaceAt(i))               //есть ли под ней место
            {
                std::cout<<'*';
            }
            else                                        //иначе
            {
                std::cout<<'$';
            }
        }
        else if (i==playerPos)                          //если на позиции игрок
        {
            std::cout<<'X';
        }
        else if (stField->checkWallAt(i))               //если на позиции стена
        {
            std::cout<<'#';
        }
        else if (stField->checkPlaceAt(i))              //если на позиции место
        {
            std::cout<<'o';
        }
        else                                            //если ничего нет
        {
            std::cout<<' ';
        }

        count++;                                        //увеличиваем счетчик символов на 1
        if (count>=width)                               //если счетчик >= ширины поля
        {
            count=0;                                    //обнуляем счетчик
            std::cout<<std::endl;                       //переносим строку
        }
    }
}

unsigned long long DynamicField::getCheckIndex()
{
    unsigned long long result=playerPos;                //первые 2 цифры - позиция игрока
    unsigned int fieldSize=stField->getFieldWidth()*stField->getFieldHeight();
                                                        //получаем размер поля
    unsigned char boxesCount=stField->getBoxesCount();  //получаем кол-во коробок
    //каждая коробка занимает 2 цифры, и так по порядку
    for (int i=0;i<boxesCount;++i)
    {
        result=result+boxes[i]*pow(fieldSize,i+1);
    }
    return result;                                      //возвращаем полученный индекс
}

bool DynamicField::checkForWin() const
{
    unsigned char boxesCount=stField->getBoxesCount();  //получаем кол-во коробок
    for (unsigned int i=0;i<boxesCount;++i)             //идем по массиву коробок
    {
        if (!stField->checkPlaceAt(boxes[i]))           //стоит ли коробка не на месте
        {
            return false;                               //отваливаемся
        }
    }
    return true;                                        //говорим, что вин
}

void
DynamicField::setStField(StaticField *st)
{
    stField=st;
}

void
DynamicField::sortBoxes()
{
    unsigned char boxesCount=stField->getBoxesCount();  //получаем кол-во коробок
    if (boxesCount<2)                                   //если коробок меньше 2
    {
        return;                                         //отваливаемся
    }
    else                                                //иначе
    {
        for (int i=1; i<boxesCount; ++i)                //сортировка вставками
        {
            char key=boxes[i];
            int j=i-1;
            while (j>=0 && boxes[j]>key)
            {
                boxes[j+1]=boxes[j];
                j--;
            }
            boxes[j+1]=key;
        }
    }
}

bool
DynamicField::checkForLose(unsigned char posOfBox)
{
    unsigned char sides[5];                             //массив с соседними позициями
    unsigned char width=stField->getFieldWidth();       //получаем ширину поля

    sides[0]=posOfBox-width;                            //заполняем соседними позициями
    sides[1]=posOfBox-1;
    sides[2]=posOfBox+width;
    sides[3]=posOfBox+1;
    sides[4]=posOfBox-width;                            //это для цикла

    int counter=0;                                      //счетчик для углов
    for (int i=0; i<4; ++i)                             //идем по массиву
    {
        if (stField->checkWallAt(sides[i]) && stField->checkWallAt(sides[i+1]))
        {                                               //если ящик в углу
            counter++;                                  //инкрементируем счетчик
        }
    }
    if (counter>1 && !stField->checkPlaceAt(posOfBox))  //если счетчик больше 1 и ящик не на месте
    {
        return true;                                    //говорим, что луз
    }

    unsigned char boxesCount=stField->getBoxesCount();

    //НЕ ОБЯЗАТЕЛЬНО СМОТРЕТЬ ВСЕ КОРОБКИ
    //МОЖНО ТОЛЬКО ТЕКУЩУЮ И 4 ВАРИАНТА ЛУЗА
    // C*  *C   **  **
    // **  **   C*  *C
    if (boxesCount<4)
    {
        return false;
    }
    else
    {
        sortBoxes();

        for (int i=boxesCount-1; i>2; --i)
        {
            bool boxesOnPlaces=(stField->checkPlaceAt(boxes[i]) &&
                                stField->checkPlaceAt(boxes[i-1]) &&
                                stField->checkPlaceAt(boxes[i-2]) &&
                                stField->checkPlaceAt(boxes[i-3]));

            if (boxes[i]-boxes[i-1]==1 && boxes[i]-boxes[i-2]==width &&
                    boxes[i]-boxes[i-3]==width+1 && !boxesOnPlaces)
            {
                return true;
            }
        }
    }
    return false;
}
