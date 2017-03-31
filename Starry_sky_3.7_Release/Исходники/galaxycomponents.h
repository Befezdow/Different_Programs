#ifndef GALAXYCOMPONENTS_H
#define GALAXYCOMPONENTS_H

#include <QString>

class galaxy
{
    QString name; // название галактики
    QString type; // вид галактики
    float diam; // диаметр галактики в световых годах
    float mass; // масса галактики в эквиваленте масс Солнца *10^12
    float quan; // кол-во черной материи в процентах
public:
    galaxy(QString n="", QString t="", float d=0, float m=0, float q=0)
    {
        name=n;
        type=t;
        diam=d;
        mass=m;
        quan=q;
    }

    QString getName() const { return name; }
    QString getType() const { return type; }
    QString getDiam() const { return QString::number(diam); }
    QString getMass() const { return QString::number(mass); }
    QString getQuan() const { return QString::number(quan); }
};

class multistar
{
    QString name; // название созвездия
    QString lnaz; // латинское название
    QString sokr; // сокращение лат. названия
    float plos; // площадь cозвездия в квадратных градусах
    int chzv; // число звезд ярче 6.0^m
    QString gname; //название галактики
public:
    multistar(QString n="", QString l="", QString s="", float p=0, int c=0, QString g="")
    {
        name=n;
        lnaz=l;
        sokr=s;
        plos=p;
        chzv=c;
        gname=g;
    }

    QString getName() const { return name; }
    QString getLnaz() const { return lnaz; }
    QString getSokr() const { return sokr; }
    QString getPlos() const { return QString::number(plos); }
    QString getChzv() const { return QString::number(chzv); }
    QString getGname() const { return gname; }
};

class star
{
    QString name; // название звезды
    QString spkl; // спектральный класс
    QString cvet; // видимый цвет звезды
    float temp; // температура звезды в млн. градусов Фаренгейта
    float mass; // масса звезды в эквиваленте масс Солнца
    float zvvl; // звездная величина ^m
    float razm; // размеры звезды в радиусах солнца
    QString mname; //название созвездия
public:
    star(QString n="", QString s="", QString c="", float t=0, float m=0, float z=0, float r=0, QString mn="")
    {
        name=n;
        spkl=s;
        cvet=c;
        temp=t;
        mass=m;
        zvvl=z;
        razm=r;
        mname=mn;
    }

    QString getName() const { return name; }
    QString getSpkl() const { return spkl; }
    QString getCvet() const { return cvet; }
    QString getTemp() const { return QString::number(temp); }
    QString getMass() const { return QString::number(mass); }
    QString getZvvl() const { return QString::number(zvvl); }
    QString getRazm() const { return QString::number(razm); }
    QString getMname() const { return mname; }
};

class planet
{
    QString name; // название планеты
    float roz; // расстояние от звезды (в млн. км.)
    float pvvo; // период вращения вокруг оси (в земных сутках)
    float rad; // радиус планеты (в км.)
    float srpl; // средняя плотность (в кг/м^3)
    QString sname; //название звезды
public:
    planet(QString n="", float r=0, float p=0, float ra=0, float s=0, QString sn="")
    {
        name=n;
        roz=r;
        pvvo=p;
        rad=ra;
        srpl=s;
        sname=sn;
    }

    QString getName() const { return name; }
    QString getRoz() const { return QString::number(roz); }
    QString getPvvo() const { return QString::number(pvvo); }
    QString getRad() const { return QString::number(rad); }
    QString getSrpl() const { return QString::number(srpl); }
    QString getSname() const { return sname; }
};

#endif // GALAXYCOMPONENTS_H
