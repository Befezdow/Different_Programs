#include <queue>

#pragma once
class Analyzer
{
    static unsigned char mostCP866[6];
    static unsigned char mostCP1251[6];
    static unsigned char mostKOI8[6];

    public:
    enum {KOI8=0,CP866,CP1251,NONE};
    
    static void setMostCP866(int e=165, int a=160, int o=174,
                             int y=168, int t=226, int n=173);
                             
    static void setMostCP1251(int e=229, int a=224, int o=238,
                              int y=232, int t=242, int n=237);
                              
    static void setMostKOI8(int e=197, int a=193, int o=207,
                            int y=201, int t=212, int n=206);
                            
    static void getMostKOI8(unsigned char &e, unsigned char &a, unsigned char &o,
                            unsigned char &y, unsigned char &t, unsigned char &n);
                            
    static void getMostCP1251(unsigned char &e, unsigned char &a, unsigned char &o,
                              unsigned char &y, unsigned char &t, unsigned char &n);
                              
    static void getMostCP866(unsigned char &e, unsigned char &a, unsigned char &o,
                             unsigned char &y, unsigned char &t, unsigned char &n);
    
    static int analyze(char* filename); //return encoding in enum
    
    static bool getMostChars(char* filename, unsigned char &firstChar, unsigned char &secondChar, unsigned char &thirdChar,
                             unsigned char &fourthChar, unsigned char &fifthChar, unsigned char &sixthChar); //return true, if no errors, else false
                             
    static std::queue<int> getQueueConversions(char* filename);
    
    static bool hasGraphicsCP866(char* filename,std::queue<int> que);
    static bool hasGraphicsCP1251(char* filename,std::queue<int> que);
    static bool hasGraphicsKOI8(char* filename,std::queue<int> que);
};