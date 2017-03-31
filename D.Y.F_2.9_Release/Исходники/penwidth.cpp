#include "penwidth.h"
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

PenWidth::PenWidth(QWidget* parent):QWidget(parent)
{
    pw=new QLabel("&Толщина:");
    pl=new QLabel("&Тип линии:");
    lw=new QLabel("&Толщина:");
    pspb=new QSpinBox;
    pspb->setAlignment(Qt::AlignLeft);
    pspb->setMinimum(1);
    pspb->setMaximum(50);
    pspb->setValue(6);
    lspb=new QSpinBox;
    lspb->setAlignment(Qt::AlignLeft);
    lspb->setAlignment(Qt::AlignTop);
    lspb->setMinimum(1);
    lspb->setMaximum(50);
    lspb->setValue(10);
    pcmb=new QComboBox;
    pw->setBuddy(pspb);
    pl->setBuddy(pcmb);
    lw->setBuddy(lspb);
    QStringList list;
    list<<"Сплошная"<<"Штриховая"<<"Пунктирная";
    list<<"Штрихпунктирная"<<"Штрих-ная с 2 точками";
    pcmb->addItems(list);
    hlay1=new QHBoxLayout;
    hlay2=new QHBoxLayout;
    lay=new QHBoxLayout;
    hlay1->addWidget(pw);
    hlay1->addWidget(pspb);
    hlay1->addWidget(pl);
    hlay1->addWidget(pcmb);
    hlay2->addWidget(lw);
    hlay2->addWidget(lspb);
    gb1=new QGroupBox("Карандаш");
    gb2=new QGroupBox("Ластик");
    gb1->setLayout(hlay1);
    gb2->setLayout(hlay2);
    lay->addWidget(gb1);
    lay->addWidget(gb2);
    this->setLayout(lay);
    this->setFixedWidth(490);
    QObject::connect(pspb,SIGNAL(valueChanged(int)),this,SIGNAL(getPenWidth(int)));
    QObject::connect(lspb,SIGNAL(valueChanged(int)),this,SIGNAL(getLasWidth(int)));
    QObject::connect(pcmb,SIGNAL(currentIndexChanged(int)),this,SIGNAL(getLine(int)));
}

PenWidth::~PenWidth()
{
    QObject::disconnect(pspb,SIGNAL(valueChanged(int)),this,SIGNAL(getPenWidth(int)));
    QObject::disconnect(lspb,SIGNAL(valueChanged(int)),this,SIGNAL(getLasWidth(int)));
    QObject::disconnect(pcmb,SIGNAL(currentIndexChanged(int)),this,SIGNAL(getLine(int)));
    delete pw;
    delete pl;
    delete lw;
    delete pspb;
    delete lspb;
    delete pcmb;
    delete hlay1;
    delete hlay2;
    delete lay;
}
