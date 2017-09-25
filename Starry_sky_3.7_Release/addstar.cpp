#include "addstar.h"
#include <QtWidgets>

AddStar::AddStar(QWidget *parent):QWidget(parent)
{
    lname=new QLabel("&Название звезды:");
    lspkl=new QLabel("&Спектр. класс звезды:");
    lcvet=new QLabel("&Видимый цвет звезды:");
    ltemp=new QLabel("&Температура звезды (в млн. град. Фаренгейта):");
    lmass=new QLabel("&Масса звезды (в экв. масс Солнца):");
    lzvvl=new QLabel("&Звездная величина (в ^m):");
    lrazm=new QLabel("&Размер звезды (в радиусах Солнца):");
    lmname=new QLabel("&Созвездие - родитель:");
    ename=new QLineEdit;
    espkl=new QLineEdit;
    ecvet=new QLineEdit;
    etemp=new QLineEdit;
    emass=new QLineEdit;
    ezvvl=new QLineEdit;
    erazm=new QLineEdit;
    emname=new QLineEdit;
    validator1=new FloatValidator;
    etemp->setValidator(validator1);
    emass->setValidator(validator1);
    ezvvl->setValidator(validator1);
    erazm->setValidator(validator1);
    ename->setMaxLength(30);
    espkl->setMaxLength(30);
    ecvet->setMaxLength(30);
    emname->setMaxLength(30);
    lname->setBuddy(ename);
    lspkl->setBuddy(espkl);
    lcvet->setBuddy(ecvet);
    ltemp->setBuddy(etemp);
    lmass->setBuddy(emass);
    lzvvl->setBuddy(ezvvl);
    lrazm->setBuddy(erazm);
    lmname->setBuddy(emname);
    lay1=new QHBoxLayout;
    lay2=new QHBoxLayout;
    lay3=new QHBoxLayout;
    lay4=new QHBoxLayout;
    lay5=new QHBoxLayout;
    lay6=new QHBoxLayout;
    lay7=new QHBoxLayout;
    lay8=new QHBoxLayout;
    lay1->addWidget(lname);
    lay1->addWidget(ename);
    lay2->addWidget(lspkl);
    lay2->addWidget(espkl);
    lay3->addWidget(lcvet);
    lay3->addWidget(ecvet);
    lay4->addWidget(ltemp);
    lay4->addWidget(etemp);
    lay5->addWidget(lmass);
    lay5->addWidget(emass);
    lay6->addWidget(lzvvl);
    lay6->addWidget(ezvvl);
    lay7->addWidget(lrazm);
    lay7->addWidget(erazm);
    lay8->addWidget(lmname);
    lay8->addWidget(emname);
    button=new QPushButton("Добавить звезду");
    lay=new QVBoxLayout;
    lay->addLayout(lay1);
    lay->addLayout(lay2);
    lay->addLayout(lay3);
    lay->addLayout(lay4);
    lay->addLayout(lay5);
    lay->addLayout(lay6);
    lay->addLayout(lay7);
    lay->addLayout(lay8);
    lay->addWidget(button);
    this->setLayout(lay);
    this->setWindowTitle("Добавление звезды");
    this->setFixedSize(400,265);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
}


AddStar::~AddStar()
{
    QObject::disconnect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
    delete button;
    delete validator1;
    delete lname;
    delete lspkl;
    delete lcvet;
    delete ltemp;
    delete lmass;
    delete lzvvl;
    delete lrazm;
    delete lmname;
    delete ename;
    delete espkl;
    delete ecvet;
    delete etemp;
    delete emass;
    delete ezvvl;
    delete erazm;
    delete emname;
    delete lay1;
    delete lay2;
    delete lay3;
    delete lay4;
    delete lay5;
    delete lay6;
    delete lay7;
    delete lay8;
    delete lay;
}

void AddStar::sendInfo()
{
    star object(ename->text(),espkl->text(),ecvet->text(),
                etemp->text().toFloat(),emass->text().toFloat(),
                ezvvl->text().toFloat(),erazm->text().toFloat(),
                emname->text());
    if (ename->text()=="" || espkl->text()=="" || ecvet->text()=="" ||
        etemp->text()=="" || emass->text()=="" || ezvvl->text()=="" ||
        erazm->text()=="" || emname->text()=="")
    {
        emit error("Необходимо заполнить все поля");
        return;
    }
    emit send(object);
    ename->clear();
    espkl->clear();
    ecvet->clear();
    etemp->clear();
    emass->clear();
    ezvvl->clear();
    erazm->clear();
    emname->clear();
}

void AddStar::setParent(QString str)
{
    emname->setText(str);
}
