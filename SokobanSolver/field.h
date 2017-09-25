#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <fstream>

#define MAX_BOXES_SIZE 4

class StaticField
{
    std::vector<bool> walls;            //положение стен
    std::vector<bool> places;           //положение мест под коробки
                                        //вектор из bool потому что так быстрее

    unsigned char boxesCount;           //кол-во коробок в поле

    unsigned char fieldWidth;           //ширина поля
    unsigned char fieldHeight;          //высота поля

public:
    StaticField(std::vector<unsigned char> map,int width,int height);

    bool checkPlaceAt(unsigned char i) const;       //проверить, есть ли место на этой позиции
    bool checkWallAt(unsigned char i) const;        //проверить, есть ли стена на этой позиции

    unsigned char getBoxesCount() const;
    unsigned char getFieldWidth() const;
    unsigned char getFieldHeight() const;
};

class DynamicField
{
    unsigned char boxes[MAX_BOXES_SIZE];            //массив, хранящий положения коробок
    unsigned char playerPos;                        //позиция игрока в поле

    static StaticField* stField;                    //указатель на статическое поле,
                                                    //т.к все хранить здесь - плохо
    void sortBoxes();                               //отсортировать массив коробок

public:
    enum {Start = 0,Up = 0,Down,Left,Right,End};    //Энамы для определения направлений
                                                    //Start,End нужны для перебора
    DynamicField(std::vector<unsigned char> map);

    int checkBoxAt(unsigned char c) const;          //проверить коробку по этому индексу
    bool move(int md);                              //сместить игрока в это направление
                                                    //true - сместился, false - нет

    void print() const;                             //напечатать поле
    unsigned long long getCheckIndex();             //получить индекс для проверки
    static void setStField(StaticField* st);        //установить статическое поле
                                                    //нужно для детерминизации индекса
    bool checkForLose(unsigned char posOfBox);      //проверка на проигрыш
    bool checkForWin() const;                       //проверка на победу
};

#endif // FIELD_H
