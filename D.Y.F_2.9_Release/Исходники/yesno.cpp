#include "yesno.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

YesNo::YesNo(QWidget* parent):QWidget(parent)
{
    pb1=new QPushButton(QIcon(":/resources/yes"),"Да");
    pb1->setFixedSize(85,40);
    pb2=new QPushButton(QIcon(":/resources/no"),"Нет");
    pb2->setFixedSize(85,40);
    pb3=new QPushButton(QIcon(":/resources/cancel"),"Отмена");
    lbl=new QLabel("Сохранить холст перед выходом?");
    lay1=new QHBoxLayout;
    lay2=new QVBoxLayout;
    this->setWindowTitle("Внимание");
    lay2->addWidget(lbl);
    lay1->addWidget(pb1);
    lay1->addWidget(pb2);
    lay2->addLayout(lay1);
    lay2->addWidget(pb3);
    this->setLayout(lay2);
    QObject::connect(pb2,SIGNAL(clicked(bool)),this,SIGNAL(no()));
    QObject::connect(pb1,SIGNAL(clicked(bool)),this,SIGNAL(yes()));
    QObject::connect(pb3,SIGNAL(clicked(bool)),this,SIGNAL(clos()));
    QObject::connect(pb3,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::connect(pb1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::connect(pb2,SIGNAL(clicked(bool)),this,SLOT(hide()));
    this->setFixedSize(200,130);
    QPalette pal;
    pal.setBrush(this->backgroundRole(),QColor(157,255,108));
    this->setPalette(pal);
}
YesNo::~YesNo()
{
    QObject::disconnect(pb2,SIGNAL(clicked(bool)),this,SIGNAL(no()));
    QObject::disconnect(pb1,SIGNAL(clicked(bool)),this,SIGNAL(yes()));
    QObject::disconnect(pb3,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::disconnect(pb1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::disconnect(pb2,SIGNAL(clicked(bool)),this,SLOT(hide()));
    delete pb1;
    delete pb2;
    delete pb3;
    delete lbl;
    delete lay1;
    delete lay2;
}
