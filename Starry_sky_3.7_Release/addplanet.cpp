#include "addplanet.h"
#include <QtWidgets>

AddPlanet::AddPlanet(QWidget *parent):QWidget(parent)
{
    lname=new QLabel("&Название планеты:");
    lroz=new QLabel("&Расст. от звезды (в млн. км.):");
    lpvvo=new QLabel("&Период вращ. вокруг оси (в земных сутках):");
    lrad=new QLabel("&Радиус планеты (в км.):");
    lsrpl=new QLabel("&Средняя плотность (в кг/м^3):");
    lsname=new QLabel("&Звезда - родитель:");
    ename=new QLineEdit;
    eroz=new QLineEdit;
    epvvo=new QLineEdit;
    erad=new QLineEdit;
    esrpl=new QLineEdit;
    esname=new QLineEdit;
    validator1=new FloatValidator;
    eroz->setValidator(validator1);
    epvvo->setValidator(validator1);
    erad->setValidator(validator1);
    esrpl->setValidator(validator1);
    ename->setMaxLength(30);
    esname->setMaxLength(30);
    lname->setBuddy(ename);
    lroz->setBuddy(eroz);
    lpvvo->setBuddy(epvvo);
    lrad->setBuddy(erad);
    lsrpl->setBuddy(esrpl);
    lsname->setBuddy(esname);
    lay1=new QHBoxLayout;
    lay2=new QHBoxLayout;
    lay3=new QHBoxLayout;
    lay4=new QHBoxLayout;
    lay5=new QHBoxLayout;
    lay6=new QHBoxLayout;
    lay1->addWidget(lname);
    lay1->addWidget(ename);
    lay2->addWidget(lroz);
    lay2->addWidget(eroz);
    lay3->addWidget(lpvvo);
    lay3->addWidget(epvvo);
    lay4->addWidget(lrad);
    lay4->addWidget(erad);
    lay5->addWidget(lsrpl);
    lay5->addWidget(esrpl);
    lay6->addWidget(lsname);
    lay6->addWidget(esname);
    button=new QPushButton("Добавить планету");
    lay=new QVBoxLayout;
    lay->addLayout(lay1);
    lay->addLayout(lay2);
    lay->addLayout(lay3);
    lay->addLayout(lay4);
    lay->addLayout(lay5);
    lay->addLayout(lay6);
    lay->addWidget(button);
    this->setLayout(lay);
    this->setWindowTitle("Добавление планеты");
    this->setFixedSize(400,200);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
}

AddPlanet::~AddPlanet()
{
    QObject::disconnect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
    delete button;
    delete validator1;
    delete lname;
    delete lroz;
    delete lpvvo;
    delete lrad;
    delete lsrpl;
    delete lsname;
    delete ename;
    delete eroz;
    delete epvvo;
    delete erad;
    delete esrpl;
    delete esname;
    delete lay1;
    delete lay2;
    delete lay3;
    delete lay4;
    delete lay5;
    delete lay6;
    delete lay;
}

void AddPlanet::sendInfo()
{
    planet object(ename->text(),eroz->text().toFloat(),epvvo->text().toFloat(),
                  erad->text().toFloat(),esrpl->text().toFloat(),esname->text());
    if (ename->text()=="" || eroz->text()=="" || epvvo->text()=="" ||
        erad->text()=="" || esrpl->text()=="" || esname->text()=="")
    {
        emit error("Необходимо заполнить все поля");
        return;
    }
    emit send(object);
    ename->clear();
    eroz->clear();
    epvvo->clear();
    erad->clear();
    esrpl->clear();
    esname->clear();
}

void AddPlanet::setParent(QString str)
{
    esname->setText(str);
}
