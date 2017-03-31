#include "analyzer.h"
#include "translator.h"
#include <queue>

#pragma once
class Item
{
    std::queue<int> conversions;
    int level;
    unsigned char first;
    unsigned char second;
    unsigned char third;
    unsigned char fourth;
    unsigned char fifth;
    unsigned char sixth;
public:
    Item(unsigned char f,unsigned char s,unsigned char t,
         unsigned char fo,unsigned char fi,unsigned char si);
    Item();
    Item(const Item &ob);
    
    void convertFromCP866toCP1251();
    void convertFromCP866toKOI8();
    void convertFromCP1251toCP866();
    void convertFromCP1251toKOI8();
    void convertFromKOI8toCP866();
    void convertFromKOI8toCP1251();
        
    std::queue<int> getConversions() const { return conversions; }
    int getLevel() const { return level; }
    int getLastConversion() const { if (conversions.empty()) return -1; else return conversions.back(); }
    
    int compareWithCP866();
    int compareWithCP1251();
    int compareWithKOI8();
};