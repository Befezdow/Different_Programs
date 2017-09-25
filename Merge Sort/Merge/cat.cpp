#include "cat.h"
#include <iomanip>
#include <cmath>

Cat::Cat(std::string name, std::string breed, int age, char gender):
    name(name),
    breed(breed),
    age(age),
    gender(gender)
{}

bool Cat::lessByName(const Cat &ob)
{
    return name<ob.name;
}

bool Cat::lessByBreed(const Cat &ob)
{
    return breed<ob.breed;
}

bool Cat::lessByAge(const Cat &ob)
{
    return age<ob.age;
}

void Cat::print()
{
    unsigned int maxName=MAX_SIZE_OF_NAME+4;                //определяем поле для имени
    unsigned int maxBreed=MAX_SIZE_OF_BREED+4;              //определяем поля для породы

    if (maxName%2==1)                                       //если нечетная
    {
        maxName++;                                          //делаем четным
    }

    if (maxBreed%2==1)                                      //если нечетная
    {
        maxBreed++;                                         //делаем четным
    }

    std::cout<<"Name: "<<this->name;                        //выводим имя

    for (unsigned int i=0; i<(maxName-this->name.size())/2; ++i)
    {
        std::cout<<" ";                                     //дописываем поле
    }
    std::cout<<"Breed: "<<this->breed;                      //выводим породу

    for (unsigned int i=0; i<(maxBreed-this->breed.size())/2; ++i)
    {
        std::cout<<" ";                                     //дописываем поле
    }
    std::cout<<"Age: "<<std::setw(4)<<std::left<<this->age; //выводим возраст
    std::cout<<"Gender: "<<this->gender<<std::endl;         //выводим пол
}

unsigned int Cat::getAge() const
{
    return this->age;
}

std::string Cat::getName() const
{
    return this->name;
}

std::string Cat::getBreed() const
{
    return this->breed;
}

char Cat::getGender() const
{
    return this->gender;
}

std::istream& operator>>(std::istream &stream,Cat &cat)
{
    char name[MAX_SIZE_OF_NAME];
    char breed[MAX_SIZE_OF_BREED];

    stream.read(name,MAX_SIZE_OF_NAME);
    stream.read(breed,MAX_SIZE_OF_BREED);
    stream.read((char*)&(cat.age),sizeof(int));

    cat.name = name;
    cat.breed = breed;
    cat.gender = stream.get();

    return stream;
}

std::ostream& operator<<(std::ostream &stream,Cat &cat)
{
    stream.write(cat.name.c_str(),MAX_SIZE_OF_NAME);
    stream.write(cat.breed.c_str(),MAX_SIZE_OF_BREED);
    stream.write((char*)&cat.age,sizeof(int));
    stream.put(cat.gender);

    return stream;
}
