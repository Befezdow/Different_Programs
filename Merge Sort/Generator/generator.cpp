#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc,char** argv)
{
    if (argc!=2)
    {
        std::cerr<<"Unexpected count of parameters"<<std::endl;
        return 1;
    }
    
    unsigned int size=atoi(argv[1]);
    
    std::cout<<"Size of dictionary: "<<size<<std::endl;

    std::ifstream in1;
    std::ifstream in2;
    std::ifstream in3;
    in1.open("heCat.txt");
    in2.open("sheCat.txt");
    in3.open("breeds.txt");
    if (!in1.is_open() || !in2.is_open() || !in3.is_open())
    {
        std::cerr<<"One of in files isn't open"<<std::endl;
        return 1;
    }
    
    std::vector<std::string> males;
    std::vector<std::string> females;
    std::vector<std::string> breeds;
    
    std::string tempStr;
    int maxNameLen=0;
    int maxBreedLen=0;
    
    while (1)
    {
        getline(in1,tempStr);
        
        if (in1.eof())
        {
            break;
        }
        
        males.push_back(tempStr);
        
        if (tempStr.size()>maxNameLen)
        {
            maxNameLen=tempStr.size();
        }
    }
    
    while (1)
    {
        getline(in2,tempStr);
        
        if (in2.eof())
        {
            break;
        }
        
        females.push_back(tempStr);
        
        if (tempStr.size()>maxNameLen)
        {
            maxNameLen=tempStr.size();
        }
    }
    
    while (1)
    {
        getline(in3,tempStr);
        
        if (in3.eof())
        {
            break;
        }
        
        breeds.push_back(tempStr);
        
        if (tempStr.size()>maxBreedLen)
        {
            maxBreedLen=tempStr.size();
        }
    }
    
    //std::cout<<males.at(males.size()-1).size()<<std::endl;
    //std::cout<<females.at(females.size()-1).size()<<std::endl;
    //std::cout<<breeds.at(breeds.size()-1).size()<<std::endl;
    
    std::cout<<"Максимальная длина имени: "<<maxNameLen<<std::endl;
    std::cout<<"Максимальная длина породы: "<<maxBreedLen<<std::endl;
    
    in1.close();
    in2.close();
    in3.close();
    
    std::ofstream out;
    out.open("dictionary.txt",std::ios::out | std::ios::binary);
    if (!out.is_open())
    {
        std::cerr<<"Out file isn't open"<<std::endl;
        return 1;
    }
    
    srand(time(0));
    for (unsigned int i=0; i<size; ++i)
    {
        unsigned int seed=rand();
        
        bool gender=seed%2;
        
        std::string name;
        if (gender)
        {
            name=males.at(seed%males.size());
        }
        else
        {
            name=females.at(seed%females.size());
        }
        std::string breed=breeds.at(seed%breeds.size());
        
        unsigned int age=((seed+rand())%100);
        age++;
        
        out.write(name.c_str(),maxNameLen);
        out.write(breed.c_str(),maxBreedLen);
        out.write((char*)&age,4);
        if (gender)
        {
            out.put('m');
        }
        else
        {
            out.put('f');
        }
    }
    
    out.close();
    return 0;
}