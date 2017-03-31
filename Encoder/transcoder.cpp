#include "translator.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc,char** argv)
{   
    if (argc!=3)
    {
        cerr<<"Incorrect count of arguments"<<endl;
        return 1;
    }
    fstream file;
    file.open(argv[1],ios::binary | ios::in | ios::out);
    if (!file)
    {
        cerr<<"File not open"<<endl;
        return 1;
    }
    
    Translator::setKOI8toCP866(NULL);
    Translator::setKOI8toCP1251(NULL);
    Translator::setCP866toCP1251(NULL);
    Translator::setCP866toKOI8(NULL);
    Translator::setCP1251toCP866(NULL);
    Translator::setCP1251toKOI8(NULL);
    
    if (!strcmp(argv[2],"-cw"))
    {
        Translator::fileCP866toCP1251(file);
        cout<<argv[1]<<" is transcoded from CP866 to CP1251"<<endl;
        file.close();
        return 0;
    }
    if (!strcmp(argv[2],"-ck"))
    {
        Translator::fileCP866toKOI8(file);
        cout<<argv[1]<<" is transcoded from CP866 to KOI8-R"<<endl;
        file.close();
        return 0;
    }
    if (!strcmp(argv[2],"-wc"))
    {
        Translator::fileCP1251toCP866(file);
        cout<<argv[1]<<" is transcoded from CP1251 to CP866"<<endl;
        file.close();
        return 0;
    }
    if (!strcmp(argv[2],"-wk"))
    {
        Translator::fileCP1251toKOI8(file);
        cout<<argv[1]<<" is transcoded from CP1251 to KOI8-R"<<endl;
        file.close();
        return 0;
    }
    if (!strcmp(argv[2],"-kc"))
    {
        Translator::fileKOI8toCP866(file);
        cout<<argv[1]<<" is transcoded from KOI8-R to CP866"<<endl;
        file.close();
        return 0;
    }
    if (!strcmp(argv[2],"-kw"))
    {
        Translator::fileKOI8toCP1251(file);
        cout<<argv[1]<<" is transcoded from KOI8-R to CP1251"<<endl;
        file.close();
        return 0;
    }
    cerr<<"Incorrect key"<<endl;
    file.close();
    return 1;
}