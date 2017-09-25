#include "addmultistar.h"
#include <QtWidgets>

AddMultiStar::AddMultiStar(QWidget *parent):QWidget(parent)
{
    lname=new QLabel("&Название созвзедия:");
    llnaz=new QLabel("&Лат. название созвездия:");
    lsokr=new QLabel("&Сокр. лат. название:");
    lplos=new QLabel("&Площадь созвездия (в квадр. град.):");
    lchzv=new QLabel("&Число звезд ярче 6.0^m:");
    lgname=new QLabel ("&Галактика - родитель:");
    ename=new QLineEdit;
    elnaz=new QLineEdit;
    esokr=new QLineEdit;
    eplos=new QLineEdit;
    echzv=new QLineEdit;
    egname=new QLineEdit;
    validator1=new FloatValidator;
    validator2=new QIntValidator;
    eplos->setValidator(validator1);
    echzv->setValidator(validator2);
    ename->setMaxLength(30);
    elnaz->setMaxLength(30);
    esokr->setMaxLength(30);
    egname->setMaxLength(30);
    lname->setBuddy(ename);
    llnaz->setBuddy(elnaz);
    lsokr->setBuddy(esokr);
    lplos->setBuddy(eplos);
    lchzv->setBuddy(echzv);
    lgname->setBuddy(egname);
    lay1=new QHBoxLayout;
    lay2=new QHBoxLayout;
    lay3=new QHBoxLayout;
    lay4=new QHBoxLayout;
    lay5=new QHBoxLayout;
    lay6=new QHBoxLayout;
    lay1->addWidget(lname);
    lay1->addWidget(ename);
    lay2->addWidget(llnaz);
    lay2->addWidget(elnaz);
    lay3->addWidget(lsokr);
    lay3->addWidget(esokr);
    lay4->addWidget(lplos);
    lay4->addWidget(eplos);
    lay5->addWidget(lchzv);
    lay5->addWidget(echzv);
    lay6->addWidget(lgname);
    lay6->addWidget(egname);
    button=new QPushButton("Добавить созвездие");
    lay=new QVBoxLayout;
    lay->addLayout(lay1);
    lay->addLayout(lay2);
    lay->addLayout(lay3);
    lay->addLayout(lay4);
    lay->addLayout(lay5);
    lay->addLayout(lay6);
    lay->addWidget(button);
    this->setLayout(lay);
    this->setWindowTitle("Добавление созвездия");
    this->setFixedSize(400,200);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
}

AddMultiStar::~AddMultiStar()
{
    QObject::disconnect(button,SIGNAL(clicked()),this,SLOT(sendInfo()));
    delete button;
    delete validator1;
    delete validator2;
    delete lname;
    delete llnaz;
    delete lsokr;
    delete lplos;
    delete lchzv;
    delete lgname;
    delete ename;
    delete elnaz;
    delete esokr;
    delete eplos;
    delete echzv;
    delete egname;
    delete lay1;
    delete lay2;
    delete lay3;
    delete lay4;
    delete lay5;
    delete lay6;
    delete lay;
}

void AddMultiStar::sendInfo()
{
    multistar object(ename->text(),elnaz->text(),esokr->text(),
                     eplos->text().toFloat(),echzv->text().toFloat(),
                     egname->text());
    if (ename->text()=="" || elnaz->text()=="" || esokr->text()=="" ||
        eplos->text()=="" || echzv->text()=="" || egname->text()=="")
    {
        emit error("Необходимо заполнить все поля");
        return;
    }
    emit send(object);
    ename->clear();
    elnaz->clear();
    esokr->clear();
    eplos->clear();
    echzv->clear();
    egname->clear();
}

void AddMultiStar::setParent(QString str)
{
    egname->setText(str);
}
