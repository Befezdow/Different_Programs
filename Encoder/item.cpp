#include "item.h"
#include <iostream>

using namespace std;

Item::Item(unsigned char f,unsigned char s,unsigned char t,
           unsigned char fo,unsigned char fi,unsigned char si)
{
    while (!conversions.empty())
        conversions.pop();
    level=0;
    first=f;
    second=s;
    third=t;
    fourth=fo;
    fifth=fi;
    sixth=si;
}
    
Item::Item()
{
    while (!conversions.empty())
        conversions.pop();
    first=(unsigned char)0;
    second=(unsigned char)0;
    third=(unsigned char)0;
    fourth=(unsigned char)0;
    fifth=(unsigned char)0;
    sixth=(unsigned char)0;
    level=0;
}
    
Item::Item(const Item &ob)
{
    first=ob.first;
    second=ob.second;
    third=ob.third;
    fourth=ob.fourth;
    fifth=ob.fifth;
    sixth=ob.sixth;
    level=ob.level;
    conversions=ob.conversions;
}
    
void Item::convertFromCP866toCP1251()
{
    first=Translator::fromCP866toCP1251(first);
    second=Translator::fromCP866toCP1251(second);
    third=Translator::fromCP866toCP1251(third);
    fourth=Translator::fromCP866toCP1251(fourth);
    fifth=Translator::fromCP866toCP1251(fifth);
    sixth=Translator::fromCP866toCP1251(sixth);
    conversions.push(Analyzer::CP866);
    conversions.push(Analyzer::CP1251);
    level++;
    return;
}

void Item::convertFromCP866toKOI8()
{
    first=Translator::fromCP866toKOI8(first);
    second=Translator::fromCP866toKOI8(second);
    third=Translator::fromCP866toKOI8(third);
    fourth=Translator::fromCP866toKOI8(fourth);
    fifth=Translator::fromCP866toKOI8(fifth);
    sixth=Translator::fromCP866toKOI8(sixth);
    conversions.push(Analyzer::CP866);
    conversions.push(Analyzer::KOI8);
    level++;
    return;
}

void Item::convertFromCP1251toCP866()
{
    first=Translator::fromCP1251toCP866(first);
    second=Translator::fromCP1251toCP866(second);
    third=Translator::fromCP1251toCP866(third);
    fourth=Translator::fromCP1251toCP866(fourth);
    fifth=Translator::fromCP1251toCP866(fifth);
    sixth=Translator::fromCP1251toCP866(sixth);
    conversions.push(Analyzer::CP1251);
    conversions.push(Analyzer::CP866);
    level++;
    return;
}
void Item::convertFromCP1251toKOI8()
{
    first=Translator::fromCP1251toKOI8(first);
    second=Translator::fromCP1251toKOI8(second);
    third=Translator::fromCP1251toKOI8(third);
    fourth=Translator::fromCP1251toKOI8(fourth);
    fifth=Translator::fromCP1251toKOI8(fifth);
    sixth=Translator::fromCP1251toKOI8(sixth);
    conversions.push(Analyzer::CP1251);
    conversions.push(Analyzer::KOI8);
    level++;
    return;
}

void Item::convertFromKOI8toCP866()
{
    first=Translator::fromKOI8toCP866(first);
    second=Translator::fromKOI8toCP866(second);
    third=Translator::fromKOI8toCP866(third);
    fourth=Translator::fromKOI8toCP866(fourth);
    fifth=Translator::fromKOI8toCP866(fifth);
    sixth=Translator::fromKOI8toCP866(sixth);
    conversions.push(Analyzer::KOI8);
    conversions.push(Analyzer::CP866);
    level++;
    return;
}
void Item::convertFromKOI8toCP1251()
{
    first=Translator::fromKOI8toCP1251(first);
    second=Translator::fromKOI8toCP1251(second);
    third=Translator::fromKOI8toCP1251(third);
    fourth=Translator::fromKOI8toCP1251(fourth);
    fifth=Translator::fromKOI8toCP1251(fifth);
    sixth=Translator::fromKOI8toCP1251(sixth);
    conversions.push(Analyzer::KOI8);
    conversions.push(Analyzer::CP1251);
    level++;
    return;
}

    
int Item::compareWithCP866()
{
    unsigned char f,s,t,fo,fi,si;
    Analyzer::getMostCP866(f,s,t,fo,fi,si);
    int i=0;
    if (first==f || first==s || first==t || first==fo || first==fi || first==si)
        i++;
    if (second==f || second==s || second==t || second==fo || second==fi || second==si)
        i++;
    if (third==f || third==s || third==t || third==fo || third==fi || third==si)
        i++;
    if (fourth==f || fourth==s || fourth==t || fourth==fo || fourth==fi || fourth==si)
        i++;
    if (fifth==f || fifth==s || fifth==t || fifth==fo || fifth==fi || fifth==si)
        i++;
    if (sixth==f || sixth==s || sixth==t || sixth==fo || sixth==fi || sixth==si)
        i++;
    return i;
}

int Item::compareWithCP1251()
{
    unsigned char f,s,t,fo,fi,si;
    Analyzer::getMostCP1251(f,s,t,fo,fi,si);
    int i=0;
    if (first==f || first==s || first==t || first==fo || first==fi || first==si)
        i++;
    if (second==f || second==s || second==t || second==fo || second==fi || second==si)
        i++;
    if (third==f || third==s || third==t || third==fo || third==fi || third==si)
        i++;
    if (fourth==f || fourth==s || fourth==t || fourth==fo || fourth==fi || fourth==si)
        i++;
    if (fifth==f || fifth==s || fifth==t || fifth==fo || fifth==fi || fifth==si)
        i++;
    if (sixth==f || sixth==s || sixth==t || sixth==fo || sixth==fi || sixth==si)
        i++;
    return i;
}

int Item::compareWithKOI8()
{
    unsigned char f,s,t,fo,fi,si;
    Analyzer::getMostKOI8(f,s,t,fo,fi,si);
    int i=0;
    if (first==f || first==s || first==t || first==fo || first==fi || first==si)
        i++;
    if (second==f || second==s || second==t || second==fo || second==fi || second==si)
        i++;
    if (third==f || third==s || third==t || third==fo || third==fi || third==si)
        i++;
    if (fourth==f || fourth==s || fourth==t || fourth==fo || fourth==fi || fourth==si)
        i++;
    if (fifth==f || fifth==s || fifth==t || fifth==fo || fifth==fi || fifth==si)
        i++;
    if (sixth==f || sixth==s || sixth==t || sixth==fo || sixth==fi || sixth==si)
        i++;
    return i;
}