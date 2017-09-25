#include "colorsettings.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QScrollArea>
#include <QPainter>
#include <QFileDialog>
#include <QDir>
#include <QGroupBox>

ColorSettings::ColorSettings(QWidget* parent):QWidget(parent)
{
    state=1;
    penColor=Qt::black;
    brushColor=Qt::color0;
    vlay=new QVBoxLayout;
    hlay=new QHBoxLayout;
    deepSettings=new QPushButton("Расширенные настройки");
    deepSettings->setFocusProxy(this);
    pix=new QPixmap(50,50);
    pix->fill(penColor);
    penLabelName=new QLabel("Цвет 1");
    penLabelName->setAlignment(Qt::AlignHCenter);
    penLabel=new QLabel;
    penLabel->setAlignment(Qt::AlignHCenter);
    penLabel->setPixmap(*pix);
    pix->fill(brushColor);
    brushLabelName=new QLabel("Цвет 2");
    brushLabelName->setAlignment(Qt::AlignHCenter);
    brushLabel=new QLabel;
    brushLabel->setAlignment(Qt::AlignHCenter);
    brushLabel->setPixmap(*pix);
    changeButton=new StateButton;
    changeButton->setFocusProxy(this);
    pal=new Palette;
    use=new Palette;
    tab=new QTabWidget;
    tab->addTab(pal,"Палитра");
    scroll=new QScrollArea;
    scroll->setWidget(use);
    tab->addTab(scroll,"Польз. пал.");
    tab->setTabEnabled(1,false);
    tab->setFixedSize(178,197);
    usePalButton=new QPushButton("Своя палитра");
    noColorButton=new QPushButton("Убрать цвет");
    usePalButton->setFocusProxy(this);
    noColorButton->setFocusProxy(this);
    lay1=new QVBoxLayout;
    lay1->addWidget(penLabel);
    lay1->addWidget(penLabelName);
    lay2=new QVBoxLayout;
    lay2->addWidget(brushLabel);
    lay2->addWidget(brushLabelName);
    hlay=new QHBoxLayout;
    hlay->addLayout(lay1);
    hlay->addWidget(changeButton);
    hlay->addLayout(lay2);
    vlay=new QVBoxLayout;
    vlay->addWidget(deepSettings);
    vlay->addLayout(hlay);
    vlay->addWidget(noColorButton);
    vlay->addWidget(tab);
    vlay->addWidget(usePalButton);
    gb=new QGroupBox("Настройки цвета",this);
    gb->setLayout(vlay);
    grad=new Gradient;
    this->setFixedSize(200,400);
    QObject::connect(changeButton,SIGNAL(click()),this,SLOT(changeState()));
    QObject::connect(pal,SIGNAL(getColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::connect(use,SIGNAL(getColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::connect(changeButton,SIGNAL(click()),pal,SLOT(update()));
    QObject::connect(changeButton,SIGNAL(click()),use,SLOT(update()));
    QObject::connect(noColorButton,SIGNAL(clicked(bool)),this,SLOT(setNoColor()));
    QObject::connect(deepSettings,SIGNAL(clicked(bool)),grad,SLOT(show()));
    QObject::connect(grad,SIGNAL(sendColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::connect(usePalButton,SIGNAL(clicked(bool)),this,SLOT(loadPalette()));
}

ColorSettings::~ColorSettings()
{
    QObject::disconnect(changeButton,SIGNAL(click()),this,SLOT(changeState()));
    QObject::disconnect(pal,SIGNAL(getColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::disconnect(use,SIGNAL(getColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::disconnect(changeButton,SIGNAL(click()),pal,SLOT(update()));
    QObject::disconnect(changeButton,SIGNAL(click()),use,SLOT(update()));
    QObject::disconnect(noColorButton,SIGNAL(clicked(bool)),this,SLOT(setNoColor()));
    QObject::disconnect(deepSettings,SIGNAL(clicked(bool)),grad,SLOT(show()));
    QObject::disconnect(grad,SIGNAL(sendColor(QColor)),this,SLOT(setColor(QColor)));
    QObject::disconnect(usePalButton,SIGNAL(clicked(bool)),this,SLOT(loadPalette()));
    delete deepSettings;
    delete changeButton;
    delete noColorButton;
    delete penLabel;
    delete brushLabel;
    delete penLabelName;
    delete brushLabelName;
    delete pal;
    delete use;
    delete scroll;
    delete tab;
    delete lay1;
    delete lay2;
    delete hlay;
    delete vlay;
    delete pix;
    delete grad;
    delete usePalButton;
}

void ColorSettings::changeState()
{
    state=!state;
}

void ColorSettings::setColor(const QColor& col)
{
    if (state)
    {
        penColor=col;
        pix->fill(penColor);
        penLabel->setPixmap(*pix);
        emit sendColor(true,penColor);
    }
    else
    {
        brushColor=col;
        pix->fill(brushColor);
        brushLabel->setPixmap(*pix);
        emit sendColor(false,brushColor);
    }
}

void ColorSettings::setNoColor()
{
    pix->fill(QColor(0,0,0,0));
    QPainter painter(pix);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Courier",12,20);
    painter.setFont(font);
    painter.drawText(17,20,"No");
    painter.drawText(1,36,"color");
    painter.end();
    if (state)
    {
        penColor=QColor(0,0,0,0);
        penLabel->setPixmap(*pix);
        emit sendColor(true,penColor);
    }
    else
    {
        brushColor=QColor(0,0,0,0);
        brushLabel->setPixmap(*pix);
        emit sendColor(false,brushColor);
    }
}

void ColorSettings::loadPalette()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл",QDir::rootPath(),"PNG (*.png);;JPEG (*.jpg;*jpeg);;GIF (*.gif);;BMP (*.bmp)");
    if(!fileName.isEmpty())
    {
        if (!use->load(fileName))
            return;
        tab->setTabEnabled(1,true);
    }
}
