#ifndef CAT_H
#define CAT_H
#include <string>
#include <fstream>
#include <iostream>

#define MAX_SIZE_OF_NAME 22                 //размер имени котика из БД
#define MAX_SIZE_OF_BREED 61                //размер породы котика из БД
#define CAT_SIZE 88                         //размер одного котика для записи

class Cat
{
    std::string name;                       //имя котика
    std::string breed;                      //порода
    unsigned int age;                       //возраст
    char gender;                            //пол

public:
    Cat(std::string name="",std::string breed="",int age=0,char gender='m');

    friend std::ostream& operator<<(std::ostream& stream, Cat &cat);
    friend std::istream& operator>>(std::istream& stream,Cat &cat);

    bool lessByName(const Cat& ob);         //сравнение котиков по имени
    bool lessByBreed(const Cat& ob);        //сравнение котиков по породе
    bool lessByAge(const Cat& ob);          //сравнение котиков по возрасту

    void print();                           //напечатать котика

    unsigned int getAge() const;
    std::string getName() const;
    std::string getBreed() const;
    char getGender() const;
};

#endif // CAT_H
