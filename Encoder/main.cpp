#include "analyzer.h"
#include "translator.h"
#include "item.h"
#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
    if (argc<2) 
    {
        cerr<<"Incorrect count of arguments"<<endl;
        return 1;
    }
    
    Analyzer::setMostCP866();
    Analyzer::setMostCP1251();
    Analyzer::setMostKOI8();
    Translator::setKOI8toCP866(NULL);
    Translator::setKOI8toCP1251(NULL);
    Translator::setCP866toCP1251(NULL);
    Translator::setCP866toKOI8(NULL);
    Translator::setCP1251toCP866(NULL);
    Translator::setCP1251toKOI8(NULL);
    
    /*
    fstream file;
    file.open(argv[1],ios::in | ios::out | ios::binary);
    //Translator::fileKOI8toCP866(file);
    //Translator::fileCP866toKOI8(file);
    //Translator::fileCP866toCP1251(file);
    Translator::fileCP1251toKOI8(file);
    Translator::fileKOI8toCP1251(file);
    Translator::fileCP1251toCP866(file);
    Translator::fileKOI8toCP1251(file);
    //Translator::fileCP866toKOI8(file);
    
    //Translator::fileCP1251toKOI8(file);
    //Translator::fileCP866toCP1251(file);
    //Translator::fileKOI8toCP1251(file);
    //Translator::fileCP866toKOI8(file);
    file.close();
    */
    
    int e=Analyzer::analyze(argv[1]);
    switch(e)
    {
        case Analyzer::KOI8:
            cout<<"This is KOI8-R"<<endl;
            break;
        case Analyzer::CP1251:
            cout<<"This is CP1251"<<endl;
            break;
        case Analyzer::CP866:
            cout<<"This is CP866"<<endl;
            break;
        default:
            cout<<"Unknown encoding"<<endl;
            bool check=Translator::convertFile(argv[1],Analyzer::getQueueConversions(argv[1]));
            if (!check)
                return 1;
            e=Analyzer::analyze(argv[1]);
            if (e==Analyzer::KOI8)
                cout<<"True encoding: KOI8-R"<<endl;
            if (e==Analyzer::CP1251)
                cout<<"True encoding: CP1251"<<endl;
            if (e==Analyzer::CP866)
                cout<<"True encoding: CP866"<<endl;
    }    
    return 0;
}