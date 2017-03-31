#include "translator.h"
#include "analyzer.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

unsigned char Translator::KOI8toCP866[128];
unsigned char Translator::KOI8toCP1251[128];
unsigned char Translator::CP866toKOI8[128];
unsigned char Translator::CP866toCP1251[128];
unsigned char Translator::CP1251toKOI8[128];
unsigned char Translator::CP1251toCP866[128];

unsigned char Translator::fromKOI8toCP866(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"KOI8 to CP866: out of array"<<endl;
        return (unsigned char)0;
    }
    return KOI8toCP866[int(c)-128];
}

unsigned char Translator::fromKOI8toCP1251(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"KOI8 to CP1251: out of array"<<endl;
        return (unsigned char)0;
    }
    return KOI8toCP1251[int(c)-128];
}

unsigned char Translator::fromCP866toKOI8(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"CP866 to KOI8: out of array"<<endl;
        return (unsigned char)0;
    }
    return CP866toKOI8[int(c)-128];
}

unsigned char Translator::fromCP866toCP1251(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"CP866 to CP1251: out of array"<<endl;
        return (unsigned char)0;
    }
    return CP866toCP1251[int(c)-128];
}

unsigned char Translator::fromCP1251toKOI8(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"CP1251 to KOI8: out of array"<<endl;
        return (unsigned char)0;
    }
    return CP1251toKOI8[int(c)-128];
}

unsigned char Translator::fromCP1251toCP866(unsigned char c)
{
    if (int(c)>255 || int(c)<128)
    {
        cerr<<"CP1251 to CP866: out of array"<<endl;
        return (unsigned char)0;
    }
    return CP1251toCP866[int(c)-128];
}

void Translator::setKOI8toCP866(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
	192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
	208, 209, 210, 241, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222,
	223, 242, 243, 240, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
	238, 160, 161, 230, 164, 165, 228, 163, 229, 168, 169, 170, 171, 172, 173, 174,
	175, 239, 224, 225, 226, 227, 166, 162, 236, 235, 167, 232, 237, 233, 231, 234,
	158, 128, 129, 150, 132, 133, 148, 131, 149, 136, 137, 138, 139, 140, 141, 142,
	143, 159, 144, 145, 146, 147, 134, 130, 156, 155, 135, 152, 157, 153, 151, 154};	
	
        for (int i=0;i<128;i++)
            Translator::KOI8toCP866[i]=(unsigned char)prom[i];
        return;
    }
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setKOI8toCP866: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::KOI8toCP866[i]=mass[i];
    return;
}

void Translator::setKOI8toCP1251(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 184, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175,
	176, 177, 178, 168, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191,
	254, 224, 225, 246, 228, 229, 244, 227, 245, 232, 233, 234, 235, 236, 237, 238,
	239, 255, 240, 241, 242, 243, 230, 226, 252, 251, 231, 248, 253, 249, 247, 250,
	222, 192, 193, 214, 196, 197, 212, 195, 213, 200, 201, 202, 203, 204, 205, 206,
	207, 223, 208, 209, 210, 211, 198, 194, 220, 219, 199, 216, 221, 217, 215, 218};
	        
        for (int i=0;i<128;i++)
            Translator::KOI8toCP1251[i]=(unsigned char)prom[i];
        return;
    }
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setKOI8toCP1251: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::KOI8toCP1251[i]=mass[i];
    return;
}

void Translator::setCP866toKOI8(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
	242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
	193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
	210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209,
	179, 163, 177, 178, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191};
        
        for (int i=0;i<128;i++)
            Translator::CP866toKOI8[i]=(unsigned char)prom[i];
        return;
    }    
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setCP866toKOI8: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::CP866toKOI8[i]=mass[i];
    return;
}

void Translator::setCP866toCP1251(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
	208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
	224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 176,
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
	168, 184, 177, 178, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191};
	
        for (int i=0;i<128;i++)
            Translator::CP866toCP1251[i]=(unsigned char)prom[i];
        return;
    }
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setCP866toCP1251: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::CP866toCP1251[i]=mass[i];
    return;
}

void Translator::setCP1251toKOI8(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 164, 165, 166, 167, 168, 179, 169, 170, 171, 172, 173, 174, 175,
	176, 177, 178, 180, 181, 182, 183, 184, 163, 185, 186, 187, 188, 189, 190, 191,
	225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
	242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
	193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,
	210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209};
        
        for (int i=0;i<128;i++)
            Translator::CP1251toKOI8[i]=(unsigned char)prom[i];
        return;
    }
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setCP1251toKOI8: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::CP1251toKOI8[i]=mass[i];
    return;   
}

void Translator::setCP1251toCP866(unsigned char* mass)
{
    if (!mass)
    {
        int prom[128]={
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
	192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
	208, 209, 210, 211, 212, 213, 214, 215, 240, 216, 217, 218, 219, 220, 221, 222,
	223, 242, 243, 244, 245, 246, 247, 248, 241, 249, 250, 251, 252, 253, 254, 255,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
	224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239};
        
        for (int i=0;i<128;i++)
            Translator::CP1251toCP866[i]=(unsigned char)prom[i];
        return;
    }
    if (strlen((char*)mass)!=128)
    {
        cerr<<"setCP1251toCP866: incorrect size of array"<<endl;
        return;
    }
    for (int i=0;i<128;i++)
        Translator::CP1251toCP866[i]=mass[i];
    return;
}

void Translator::fileKOI8toCP866(fstream &file)
{
    cerr<<"KOI8->CP866"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromKOI8toCP866(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

void Translator::fileKOI8toCP1251(fstream &file)
{
    cerr<<"KOI8->CP1251"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromKOI8toCP1251(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

void Translator::fileCP866toCP1251(fstream &file)
{
    cerr<<"CP866->CP1251"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromCP866toCP1251(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

void Translator::fileCP866toKOI8(fstream &file)
{
    cerr<<"CP866->KOI8"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromCP866toKOI8(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

void Translator::fileCP1251toCP866(fstream &file)
{
    cerr<<"CP1251->CP866"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromCP1251toCP866(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

void Translator::fileCP1251toKOI8(fstream &file)
{
    cerr<<"CP1251->KOI8"<<endl;
    if (file.eof())
        file.clear();
    file.seekp(0,ios::beg);
    file.seekg(0,ios::beg);
    char c;
    unsigned char ch;
    while (file)
    {
        file.get(c);
        ch=(unsigned char)c;
        if (128<=(int)ch && 255>=(int)ch)
            ch=Translator::fromCP1251toKOI8(ch);
        c=(char)ch;
        file.seekp(-1,ios::cur);
        file.put(c);
        if (!file) break;
    }
    return;
}

bool Translator::convertFile(char* filename, queue<int> que)
{
    if (que.front()==Analyzer::NONE)
    {
        cerr<<"convertFile: The last value of stack is NONE"<<endl;
        return false;
    }
    if (que.empty())
        cerr<<"convertFile: Queue is empty"<<endl;
        
    fstream file;
    file.open(filename,ios::in | ios::out | ios::binary);
    if (!file)
    {
        cerr<<"convertFile: File not open"<<endl;
        return false;
    }
    while(que.size()>1)
    {
        int from=que.front();
        que.pop();
        int to=que.front();
        que.pop();
        switch (from)
        {
            case Analyzer::CP866:
            {
                switch (to)
                {
                    case Analyzer::CP1251:
                        Translator::fileCP866toCP1251(file);
                        break;
                    case Analyzer::KOI8:
                        Translator::fileCP866toKOI8(file);
                        break;
                    default:
                        cerr<<"convertFile: Stack error"<<endl;
                        return false;
                }
                break;
            }
            case Analyzer::CP1251:
            {
                switch (to)
                {
                    case Analyzer::CP866:
                        Translator::fileCP1251toCP866(file);
                        break;
                    case Analyzer::KOI8:
                        Translator::fileCP1251toKOI8(file);
                        break;
                    default:
                        cerr<<"convertFile: Stack error"<<endl;
                        return false;
                }
                break;
            }
            case Analyzer::KOI8:
            {
                switch (to)
                {
                    case Analyzer::CP866:
                        Translator::fileKOI8toCP866(file);
                        break;
                    case Analyzer::CP1251:
                        Translator::fileKOI8toCP1251(file);
                        break;
                    default:
                        cerr<<"convertFile: Stack error"<<endl;
                        return false;
                }
                break;
            }
            default:
                cerr<<"convertFile: Stack error"<<endl;
                return false;
        }
    }
    file.close();
    return true;
}

unsigned char Translator::convertSymbol(unsigned char ch, queue<int> que)
{
    if (128>(int)ch || 255<(int)ch)
        return ch;
    if (que.empty())
    {
        cerr<<"convertSymbol: Queue is empty"<<endl;
        return ch;
    }
    while(que.size()>1)
    {
        int from=que.front();
        que.pop();
        int to=que.front();
        que.pop();
        switch (from)
        {
            case Analyzer::CP866:
            {
                switch (to)
                {
                    case Analyzer::CP1251:
                        ch=Translator::fromCP866toCP1251(ch);
                        break;
                    case Analyzer::KOI8:
                        ch=Translator::fromCP866toKOI8(ch);
                        break;
                    default:
                        cerr<<"checkGraphicsCP866: Queue's error"<<endl;
                        return (unsigned char)0;
                }
                break;
            }
            case Analyzer::CP1251:
            {
                switch(to)
                {
                    case Analyzer::CP866:
                        ch=Translator::fromCP1251toCP866(ch);
                        break;
                    case Analyzer::KOI8:
                        ch=Translator::fromCP1251toKOI8(ch);
                        break;
                    default:
                        cerr<<"checkGraphicsCP866: Queue's error"<<endl;
                        return (unsigned char)0;
                }
                break;
            }
            case Analyzer::KOI8:
            {
                switch(to)
                {
                    case Analyzer::CP866:
                        ch=Translator::fromKOI8toCP866(ch);
                        break;
                    case Analyzer::CP1251:
                        ch=Translator::fromKOI8toCP1251(ch);
                        break;
                    default:
                        cerr<<"checkGraphicsCP866: Queue's error"<<endl;
                        return (unsigned char)0;
                }
                break;
            }
            default:
                cerr<<"checkGraphicsCP866: Queue's error"<<endl;
                return (unsigned char)0;
        }
    }
    return ch;
}