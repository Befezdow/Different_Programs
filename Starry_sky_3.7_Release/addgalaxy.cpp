#include "addgalaxy.h"
#include <QtWidgets>

AddGalaxy::AddGalaxy(QWidget *parent):QWidget(parent)
{
    lname=new QLabel("&Название галактики:");
    ltype=new QLabel("&Тип галактики:");
    ldiam=new QLabel("&Диаметр галактики (в св. годах):");
    lmass=new QLabel("&Масса галактики (в экв. масс Солнца *10^12):");
    lquan=new QLabel("&Кол-во темной материи (в %)");
    ename=new QLineEdit;
    etype=new QLineEdit;
    ediam=new QLineEdit;
    emass=new QLineEdit;
    equan=new QLineEdit;
    validator1=new FloatValidator;
    validator2=new PercentValidator;
    ename->setMaxLength(30);
    etype->setMaxLength(30);
    ediam->setValidator(validator1);
    emass->setValidator(validator1);
    equan->setValidator(validator2);
    lname->setBuddy(ename);
    ltype->setBuddy(etype);
    ldiam->setBuddy(ediam);
    lmass->setBuddy(emass);
    lquan->setBuddy(equan);
    lay1=new QHBoxLayout;
    lay2=new QHBoxLayout;
    lay3=new QHBoxLayout;
    lay4=new QHBoxLayout;
    lay5=new QHBoxLayout;
    lay1->addWidget(lname);
    lay1->addWidget(ename);
    lay2->addWidget(ltype);
    lay2->addWidget(etype);
    lay3->addWidget(ldiam);
    lay3->addWidget(ediam);
    lay4->addWidget(lmass);
    lay4->addWidget(emass);
    lay5->addWidget(lquan);
    lay5->addWidget(equan);
    button=new QPushButton("Добавить галактику");
    lay=new QVBoxLayout;
    lay->addLayout(lay1);
    lay->addLayout(lay2);
    lay->addLayout(lay3);
    lay->addLayout(lay4);
    lay->addLayout(lay5);
    lay->addWidget(button);
    this->setLayout(lay);
    this->setWindowTitle("Добавление галактики");
    this->setFixedSize(400,200);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
}

AddGalaxy::~AddGalaxy()
{
    QObject::disconnect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
    delete button;
    delete validator1;
    delete validator2;
    delete lname;
    delete ltype;
    delete ldiam;
    delete lmass;
    delete lquan;
    delete ename;
    delete etype;
    delete ediam;
    delete emass;
    delete equan;
    delete lay1;
    delete lay2;
    delete lay3;
    delete lay4;
    delete lay5;
    delete lay;
}

void AddGalaxy::sendInfo()
{
    galaxy object(ename->text(),etype->text(),ediam->text().toFloat(),
                  emass->text().toFloat(),equan->text().toFloat());
    if (ename->text()=="" || etype->text()=="" || ediam->text()=="" ||
        emass->text()=="" || equan->text()=="")
    {
        emit error("Необходимо заполнить все поля");
        return;
    }
    emit send(object);
    ename->clear();
    etype->clear();
    ediam->clear();
    emass->clear();
    equan->clear();
}
