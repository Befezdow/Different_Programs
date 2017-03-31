#include "analyzer.h"
#include "item.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

unsigned char Analyzer::mostCP866[6];
unsigned char Analyzer::mostCP1251[6];
unsigned char Analyzer::mostKOI8[6];

void Analyzer::setMostCP866(int e,int a,int o,int y,int t,int n)
{
    Analyzer::mostCP866[0]=(unsigned char)e;
    Analyzer::mostCP866[1]=(unsigned char)a;
    Analyzer::mostCP866[2]=(unsigned char)o;
    Analyzer::mostCP866[3]=(unsigned char)y;
    Analyzer::mostCP866[4]=(unsigned char)t;
    Analyzer::mostCP866[5]=(unsigned char)n;
}

void Analyzer::setMostCP1251(int e,int a,int o,int y,int t,int n)
{
    Analyzer::mostCP1251[0]=(unsigned char)e;
    Analyzer::mostCP1251[1]=(unsigned char)a;
    Analyzer::mostCP1251[2]=(unsigned char)o;
    Analyzer::mostCP1251[3]=(unsigned char)y;
    Analyzer::mostCP1251[4]=(unsigned char)t;
    Analyzer::mostCP1251[5]=(unsigned char)n;
}

void Analyzer::setMostKOI8(int e,int a, int o,int y,int t,int n)
{
    Analyzer::mostKOI8[0]=(unsigned char)e;
    Analyzer::mostKOI8[1]=(unsigned char)a;
    Analyzer::mostKOI8[2]=(unsigned char)o;
    Analyzer::mostKOI8[3]=(unsigned char)y;
    Analyzer::mostKOI8[4]=(unsigned char)t;
    Analyzer::mostKOI8[5]=(unsigned char)n;
}

void Analyzer::getMostCP866(unsigned char &e, unsigned char &a, unsigned char &o,
                            unsigned char &y, unsigned char &t, unsigned char &n)
{
    e=Analyzer::mostCP866[0];
    a=Analyzer::mostCP866[1];
    o=Analyzer::mostCP866[2];
    y=Analyzer::mostCP866[3];
    t=Analyzer::mostCP866[4];
    n=Analyzer::mostCP866[5];
}

void Analyzer::getMostCP1251(unsigned char &e, unsigned char &a, unsigned char &o,
                             unsigned char &y, unsigned char &t, unsigned char &n)
{
    e=Analyzer::mostCP1251[0];
    a=Analyzer::mostCP1251[1];
    o=Analyzer::mostCP1251[2];
    y=Analyzer::mostCP1251[3];
    t=Analyzer::mostCP1251[4];
    n=Analyzer::mostCP1251[5];
}


void Analyzer::getMostKOI8(unsigned char &e, unsigned char &a, unsigned char &o,
                           unsigned char &y, unsigned char &t, unsigned char &n)
{
    e=Analyzer::mostKOI8[0];
    a=Analyzer::mostKOI8[1];
    o=Analyzer::mostKOI8[2];
    y=Analyzer::mostKOI8[3];
    t=Analyzer::mostKOI8[4];
    n=Analyzer::mostKOI8[5];
}

int Analyzer::analyze(char* filename)
{
    ifstream file;
    file.open(filename);
    if (!file)
    {
        cerr<<"analyze: File open error"<<endl;
        return NONE;
    }
    unsigned char c;
    long long size=0;
    int sim[128];
    for (int i=0;i<128;i++)
        sim[i]=0;
    while (file)
    {
        file>>c;
        if (!file) break;
        if ((int)c>127)
        {
            sim[int(c)-128]++;
            size++;
        }
    }
    file.close();
    int firstNum=0;
    int secondNum=0;
    int thirdNum=0;
    unsigned char first;
    unsigned char second;
    unsigned char third;
    for (int i=0;i<128;i++)
    {
        if (firstNum<sim[i])
        {
            first=(unsigned char)(i+128);
            firstNum=sim[i];
        }
    }
    for (int i=0;i<128;i++)
    {
        if (secondNum<sim[i] && i!=first-128)
        {
            second=(unsigned char)(i+128);
            secondNum=sim[i];
        }
    }
    for (int i=0;i<128;i++)
        if (thirdNum<sim[i] && i!=first-128 && i!=second-128)
        {
            third=(unsigned char)(i+128);
            thirdNum=sim[i];
        }
    /*
    //подробный символьный отчет
    int j=1;
    for (int i=0;i<128;i++)
    {
        cout<<(i+128)<<" "<<sim[i]<<"\t";
        if (j%8==0) 
            cout<<endl;
        j++;
    }
    cout<<endl;
    */
    int koi=0;
    int cp1=0;
    int cp8=0;
    for (int i=0;i<3;i++)
    {
        if (int(first)==int(mostKOI8[i]) || 
        int(second)==int(mostKOI8[i]) || int(third)==int(mostKOI8[i]))
            koi++;
        if (int(first)==int(mostCP1251[i]) || 
        int(second)==int(mostCP1251[i]) || int(third)==int(mostCP1251[i]))
            cp1++;
        if (int(first)==int(mostCP866[i]) || 
        int(second)==int(mostCP866[i]) || int(third)==int(mostCP866[i]))
            cp8++;
    }
    if (koi>1 && koi>cp1 && koi>cp8)
        return KOI8;
    if (cp1>1 && cp1>koi && cp1>cp8)
        return CP1251;
    if (cp8>1 && cp8>koi && cp8>cp1)
        return CP866;
    return NONE;
}

bool Analyzer::getMostChars(char* filename, unsigned char &firstChar, unsigned char &secondChar, unsigned char &thirdChar,
                            unsigned char &fourthChar, unsigned char &fifthChar, unsigned char &sixthChar)
{
    ifstream file;
    file.open(filename);
    if (!file)
    {
        cerr<<"getMostChars: File open error"<<endl;
        return false;
    }
    unsigned char c;
    int sim[128];
    for (int i=0;i<128;i++)
        sim[i]=0;
    while (file)
    {
        file>>c;
        if (!file) break;
        if ((int)c>127)
            sim[int(c)-128]++;
    }
    file.close();
    int firstNum=0;
    int secondNum=0;
    int thirdNum=0;
    int fourthNum=0;
    int fifthNum=0;
    int sixthNum=0;
    unsigned char first,second,third,fourth,fifth,sixth;
    for (int i=0;i<128;i++)
    {
        if (firstNum<sim[i])
        {
            first=(unsigned char)(i+128);
            firstNum=sim[i];
        }
    }
    for (int i=0;i<128;i++)
    {
        if (secondNum<sim[i] && i!=first-128)
        {
            second=(unsigned char)(i+128);
            secondNum=sim[i];
        }
    }
    for (int i=0;i<128;i++)
        if (thirdNum<sim[i] && i!=first-128 && i!=second-128)
        {
            third=(unsigned char)(i+128);
            thirdNum=sim[i];
        }
    for (int i=0;i<128;i++)
        if (fourthNum<sim[i] && i!=first-128 && i!=second-128 && i!=third-128)
        {
            fourth=(unsigned char)(i+128);
            fourthNum=sim[i];
        }
    for (int i=0;i<128;i++)
        if (fifthNum<sim[i] && i!=first-128 && i!=second-128 && i!=third-128 && i!=fourth-128)
        {
            fifth=(unsigned char)(i+128);
            fifthNum=sim[i];
        }
    for (int i=0;i<128;i++)
        if (sixthNum<sim[i] && i!=first-128 && i!=second-128 && i!=third-128 && i!=fourth-128 && i!=fifth-128)
        {
            sixth=(unsigned char)(i+128);
            sixthNum=sim[i];
        }
    firstChar=first;
    secondChar=second;
    thirdChar=third;
    fourthChar=fourth;
    fifthChar=fifth;
    sixthChar=sixth;
    return true;
}

queue<int> Analyzer::getQueueConversions(char* filename)
{
    unsigned char f,s,t,fo,fi,si;
    if (!Analyzer::getMostChars(filename,f,s,t,fo,fi,si))
        return queue<int>();
    stack<Item> tree;
    Item item(f,s,t,fo,fi,si);
    Item best=item;
    int check1=item.compareWithCP866();
    int check2=item.compareWithCP1251();
    int check3=item.compareWithKOI8();
    int bestNum;
    if (check1>check2)
    {
        if (check1>check3)
            bestNum=check1;
        else
            bestNum=check3;
    }
    else
    {
        if (check2>check3)
            bestNum=check2;
        else
            bestNum=check3;
    }
    tree.push(item);
    while(!tree.empty())
    {
        Item it=tree.top();
        tree.pop();
        int check1=it.compareWithCP866();
        int check2=it.compareWithCP1251();
        int check3=it.compareWithKOI8();
        if (check1 || check2 || check3)
        {
            if (check1>bestNum)
            {
                if (!Analyzer::hasGraphicsCP866(filename,it.getConversions()))	//не срабатывает ни разу, посмотеть почему так
                {
                    best=it;
                    bestNum=check1;
                }
            }
            if (check2>bestNum)
            {
                if (!Analyzer::hasGraphicsCP1251(filename,it.getConversions()))
                {
                    best=it;
                    bestNum=check2;
                }
            }
            if (check3>bestNum)
            {
                if (!Analyzer::hasGraphicsKOI8(filename,it.getConversions()))
                {
                    best=it;
                    bestNum=check3;
                }
            }
        }
        if (it.getLevel()<4)
        {
            int check=it.getLastConversion();
            if (check==-1)
            {
                Item it1=it;
                Item it2=it;
                Item it3=it;
                Item it4=it;
                Item it5=it;
                Item it6=it;
                it1.convertFromCP866toCP1251();
                it2.convertFromCP866toKOI8();
                it3.convertFromCP1251toCP866();
                it4.convertFromCP1251toKOI8();
                it5.convertFromKOI8toCP866();
                it6.convertFromKOI8toCP1251();
                tree.push(it1);
                tree.push(it2);
                tree.push(it3);
                tree.push(it4);
                tree.push(it5);
                tree.push(it6);
            }
            else
            {
                Item it1=it;
                Item it2=it;
                Item it3=it;
                Item it4=it;
                switch (check)
                {
                    case Analyzer::CP866:
                        it1.convertFromCP1251toCP866();
                        it2.convertFromCP1251toKOI8();
                        it3.convertFromKOI8toCP866();
                        it4.convertFromKOI8toCP1251();
                        tree.push(it1);
                        tree.push(it2);
                        tree.push(it3);
                        tree.push(it4);
                        break;
                    case Analyzer::CP1251:
                        it1.convertFromCP866toCP1251();
                        it2.convertFromCP866toKOI8();
                        it3.convertFromKOI8toCP866();
                        it4.convertFromKOI8toCP1251();
                        tree.push(it1);
                        tree.push(it2);
                        tree.push(it3);
                        tree.push(it4);
                        break;
                    case Analyzer::KOI8:
                        it1.convertFromCP866toCP1251();
                        it2.convertFromCP866toKOI8();
                        it3.convertFromCP1251toCP866();
                        it4.convertFromCP1251toKOI8();
                        tree.push(it1);
                        tree.push(it2);
                        tree.push(it3);
                        tree.push(it4);
                        break;
                    default:
                        cerr<<"getQueueConversions: Error of queue"<<endl;
                        return queue<int>();
                }
            }
        }
    }
    return best.getConversions();
}

bool Analyzer::hasGraphicsCP866(char* filename,queue<int> que)
{
    ifstream file;
    file.open(filename,ios::binary | ios::in);
    if (!file)
    {
        cerr<<"hasGraphicsCP866: File not open"<<endl;
        return false;
    }
    char c;
    unsigned char ch;
    while(file)
    {
        file.get(c);
        if (!file)
            break;
        ch=(unsigned char)c;
        ch=Translator::convertSymbol(ch,que);
        if (0==(int)ch)
        {
            cerr<<"hasGraphicsCP866: Zero symbol"<<endl;
            file.close();
            return true;
        }
        int i=(int)ch;
        if ((i>175 && i<224) || (i>243 && i<256))
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
bool Analyzer::hasGraphicsCP1251(char* filename,queue<int> que)
{
    ifstream file;
    file.open(filename,ios::binary | ios::in);
    if (!file)
    {
        cerr<<"hasGraphicsCP1251: File not open"<<endl;
        return false;
    }
    char c;
    unsigned char ch;
    while(file)
    {
        file.get(c);
        if (!file)
            break;
        ch=(unsigned char)c;
        ch=Translator::convertSymbol(ch,que);
        if (0==(int)ch)
        {
            cerr<<"hasGraphicsCP1251: Zero symbol"<<endl;
            file.close();
            return true;
        }
        int i=(int)ch;
        if ((i>127 && i<192) && i!=168 && i!=184 && i!=130 && i!=132 && i!=145 && i!=146 && i!=147 && i!=148 && i!=150 && i!=151 && i!=171 && i!=187)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
bool Analyzer::hasGraphicsKOI8(char* filename,queue<int> que)
{
    ifstream file;
    file.open(filename,ios::binary | ios::in);
    if (!file)
    {
        cerr<<"hasGraphicsCP1251: File not open"<<endl;
        return false;
    }
    char c;
    unsigned char ch;
    while(file)
    {
        file.get(c);
        if (!file)
            break;
        ch=(unsigned char)c;
        ch=Translator::convertSymbol(ch,que);
        if (0==(int)ch)
        {
            cerr<<"hasGraphicsKOI8: Zero symbol"<<endl;
            file.close();
            return true;
        }
        int i=(int)ch;
        if ((i>127 && i<192) && i!=163 && i!=164 && i!=179 && i!=180)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}