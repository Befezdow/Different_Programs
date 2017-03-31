#include "changesize.h"
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

ChangeSize::ChangeSize(QWidget* parent):QWidget(parent)
{
    lbl1=new QLabel("&Ширина в пикселях:");
    lbl2=new QLabel("&Высота в пикселях:");
    spb1=new QSpinBox;
    spb2=new QSpinBox;
    ok=new QPushButton("Принять");
    cancel=new QPushButton("Отменить");
    spb1->setMinimum(1);
    spb2->setMinimum(1);
    spb1->setMaximum(3000);
    spb2->setMaximum(3000);
    spb1->setValue(500);
    spb2->setValue(500);
    lay1=new QVBoxLayout;
    lay2=new QVBoxLayout;
    lay3=new QHBoxLayout;
    lay4=new QHBoxLayout;
    lay=new QVBoxLayout;
    lay1->addWidget(lbl1);
    lay1->addWidget(lbl2);
    lay2->addWidget(spb1);
    lay2->addWidget(spb2);
    lay3->addLayout(lay1);
    lay3->addLayout(lay2);
    lay4->addWidget(cancel);
    lay4->addWidget(ok);
    lay->addLayout(lay3);
    lay->addLayout(lay4);
    this->setLayout(lay);
    lbl1->setBuddy(spb1);
    lbl2->setBuddy(spb2);
    this->setFixedSize(this->minimumSize());
    QObject::connect(ok,SIGNAL(clicked(bool)),this,SLOT(send()));
    QObject::connect(cancel,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QPalette pal;
    pal.setBrush(this->backgroundRole(),QColor(157,255,108));
    this->setPalette(pal);
    this->setWindowTitle("Размер холста");
}
ChangeSize::~ChangeSize()
{
    QObject::disconnect(ok,SIGNAL(clicked(bool)),this,SLOT(send()));
    QObject::disconnect(cancel,SIGNAL(clicked(bool)),this,SLOT(hide()));
    delete spb1;
    delete spb2;
    delete ok;
    delete cancel;
    delete lbl1;
    delete lbl2;
    delete lay1;
    delete lay2;
    delete lay3;
    delete lay4;
    delete lay;
}

void ChangeSize::send()
{
    QSize s=QSize(spb1->value(),spb2->value());
    emit sendSize(s);
    this->hide();
}
