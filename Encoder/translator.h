#include <fstream>
#include <queue>

#pragma once
class Translator
{
    private:
    static unsigned char KOI8toCP866[128];
    static unsigned char KOI8toCP1251[128];
    static unsigned char CP866toKOI8[128];
    static unsigned char CP866toCP1251[128];
    static unsigned char CP1251toKOI8[128];
    static unsigned char CP1251toCP866[128];
    
    public:
    static unsigned char fromKOI8toCP866(unsigned char c);
    static unsigned char fromKOI8toCP1251(unsigned char c);
    static unsigned char fromCP866toKOI8(unsigned char c);
    static unsigned char fromCP866toCP1251(unsigned char c);
    static unsigned char fromCP1251toKOI8(unsigned char c);
    static unsigned char fromCP1251toCP866(unsigned char c);
    
    static void setKOI8toCP866(unsigned char* mass);
    static void setKOI8toCP1251(unsigned char* mass);
    static void setCP866toKOI8(unsigned char* mass);
    static void setCP866toCP1251(unsigned char* mass);
    static void setCP1251toKOI8(unsigned char* mass);
    static void setCP1251toCP866(unsigned char* mass);
    
    static void fileKOI8toCP866(std::fstream &file);
    static void fileKOI8toCP1251(std::fstream &file);
    static void fileCP866toKOI8(std::fstream &file);
    static void fileCP866toCP1251(std::fstream &file);
    static void fileCP1251toKOI8(std::fstream &file);
    static void fileCP1251toCP866(std::fstream &file);
    
    static bool convertFile(char* filename, std::queue<int> que);
    static unsigned char convertSymbol(unsigned char ch, std::queue<int> que);
};