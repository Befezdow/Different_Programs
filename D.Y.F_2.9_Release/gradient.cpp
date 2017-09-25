#include "gradient.h"
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

Gradient::Gradient(QWidget* parent):QWidget(parent)
{
    curColor=Qt::gray;
    QImage image(250,250,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    QLinearGradient gradient(0,0,250,0);
    gradient.setColorAt(0,Qt::red);
    gradient.setColorAt(0.16667,Qt::yellow);
    gradient.setColorAt(0.33334,Qt::green);
    gradient.setColorAt(0.5,Qt::cyan);
    gradient.setColorAt(0.66667,Qt::blue);
    gradient.setColorAt(0.83334,Qt::magenta);
    gradient.setColorAt(1,Qt::red);
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,250,250);
    QLinearGradient grad(0,0,0,250);
    grad.setColorAt(0,QColor(0,0,0,0));
    grad.setColorAt(0.6,QColor(0,0,0,0));
    grad.setColorAt(1,Qt::gray);
    painter.setBrush(grad);
    painter.drawRect(0,0,250,250);
    painter.end();
    pal=new Palette(image);
    linePal=new BonusPalette;
    redLabel=new QLabel("&Красный:");
    redLabel->setAlignment(Qt::AlignCenter);
    greenLabel=new QLabel("&Зеленый:");
    greenLabel->setAlignment(Qt::AlignCenter);
    blueLabel=new QLabel("&Синий:");
    blueLabel->setAlignment(Qt::AlignCenter);
    alphaLabel=new QLabel("&Прозрачность:");
    alphaLabel->setAlignment(Qt::AlignCenter);
    redSpin=new MySpinBox;
    redSpin->setAlignment(Qt::AlignCenter);
    greenSpin=new MySpinBox;;
    greenSpin->setAlignment(Qt::AlignCenter);
    blueSpin=new MySpinBox;
    blueSpin->setAlignment(Qt::AlignCenter);
    alphaSpin=new MySpinBox;
    alphaSpin->setAlignment(Qt::AlignCenter);
    redSpin->setMaximum(255);
    redSpin->setMinimum(0);
    greenSpin->setMaximum(255);
    greenSpin->setMinimum(0);
    blueSpin->setMaximum(255);
    blueSpin->setMinimum(0);
    alphaSpin->setMaximum(255);
    alphaSpin->setMinimum(0);
    redLabel->setBuddy(redSpin);
    greenLabel->setBuddy(greenSpin);
    blueLabel->setBuddy(blueSpin);
    alphaLabel->setBuddy(alphaSpin);
    slider=new MySlider;
    slider->setTickPosition(QSlider::TicksLeft);
    slider->setMaximum(250);
    slider->setMinimum(1);
    slider->setFixedSize(20,255);
    pix=new QPixmap(50,50);
    colorLabel=new QLabel;
    colorLabel->setAlignment(Qt::AlignCenter);
    colorLabelName=new QLabel("Цвет");
    colorLabelName->setAlignment(Qt::AlignCenter);
    cancel=new QPushButton("Отмена");
    accept=new QPushButton("Принять");
    globalLay=new QVBoxLayout;
    lay1=new QHBoxLayout;
    lay2=new QHBoxLayout;
    lay3=new QHBoxLayout;
    miniLay1=new QVBoxLayout;
    miniLay2=new QVBoxLayout;
    miniLay3=new QVBoxLayout;
    miniLay4=new QVBoxLayout;
    miniLay5=new QVBoxLayout;
    lay1->addWidget(pal);
    lay1->addWidget(linePal);
    lay1->addWidget(slider);
    miniLay1->addWidget(colorLabel);
    miniLay1->addWidget(colorLabelName);
    miniLay2->addWidget(redLabel);
    miniLay2->addWidget(greenLabel);
    miniLay3->addWidget(redSpin);
    miniLay3->addSpacing(8);
    miniLay3->addWidget(greenSpin);
    miniLay4->addWidget(blueLabel);
    miniLay4->addWidget(alphaLabel);
    miniLay5->addWidget(blueSpin);
    miniLay5->addSpacing(8);
    miniLay5->addWidget(alphaSpin);
    lay2->addLayout(miniLay1);
    lay2->addLayout(miniLay2);
    lay2->addLayout(miniLay3);
    lay2->addLayout(miniLay4);
    lay2->addLayout(miniLay5);
    lay3->addWidget(cancel);
    lay3->addWidget(accept);
    globalLay->addLayout(lay1);
    globalLay->addLayout(lay2);
    globalLay->addLayout(lay3);
    this->setLayout(globalLay);
    this->setFixedSize(380,380);
    QObject::connect(pal,SIGNAL(getColor(QColor)),linePal,SLOT(changeColor(QColor)));
    QObject::connect(pal,SIGNAL(getColor(QColor)),slider,SLOT(init()));
    QObject::connect(slider,SIGNAL(valueChanged(int)),linePal,SLOT(cacheSlider(int)));
    QObject::connect(linePal,SIGNAL(getColor(QColor)),redSpin,SLOT(setRed(QColor)));
    QObject::connect(linePal,SIGNAL(getColor(QColor)),greenSpin,SLOT(setGreen(QColor)));
    QObject::connect(linePal,SIGNAL(getColor(QColor)),blueSpin,SLOT(setBlue(QColor)));
    QObject::connect(linePal,SIGNAL(getColor(QColor)),alphaSpin,SLOT(setAlpha(QColor)));
    QObject::connect(redSpin,SIGNAL(valueChanged(int)),this,SLOT(setRed(int)));
    QObject::connect(greenSpin,SIGNAL(valueChanged(int)),this,SLOT(setGreen(int)));
    QObject::connect(blueSpin,SIGNAL(valueChanged(int)),this,SLOT(setBlue(int)));
    QObject::connect(alphaSpin,SIGNAL(valueChanged(int)),this,SLOT(setAlpha(int)));
    QObject::connect(cancel,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::connect(accept,SIGNAL(clicked(bool)),this,SLOT(ok()));
    pal->getColor(Qt::gray);
    QPalette pallette;
    pallette.setBrush(this->backgroundRole(),QColor(157,255,108));
    this->setPalette(pallette);
    this->setWindowTitle("Настройка цвета");
}

Gradient::~Gradient()
{
    QObject::disconnect(pal,SIGNAL(getColor(QColor)),linePal,SLOT(changeColor(QColor)));
    QObject::disconnect(pal,SIGNAL(getColor(QColor)),slider,SLOT(init()));
    QObject::disconnect(slider,SIGNAL(valueChanged(int)),linePal,SLOT(cacheSlider(int)));
    QObject::disconnect(linePal,SIGNAL(getColor(QColor)),redSpin,SLOT(setRed(QColor)));
    QObject::disconnect(linePal,SIGNAL(getColor(QColor)),greenSpin,SLOT(setGreen(QColor)));
    QObject::disconnect(linePal,SIGNAL(getColor(QColor)),blueSpin,SLOT(setBlue(QColor)));
    QObject::disconnect(linePal,SIGNAL(getColor(QColor)),alphaSpin,SLOT(setAlpha(QColor)));
    QObject::disconnect(redSpin,SIGNAL(valueChanged(int)),this,SLOT(setRed(int)));
    QObject::disconnect(greenSpin,SIGNAL(valueChanged(int)),this,SLOT(setGreen(int)));
    QObject::disconnect(blueSpin,SIGNAL(valueChanged(int)),this,SLOT(setBlue(int)));
    QObject::disconnect(alphaSpin,SIGNAL(valueChanged(int)),this,SLOT(setAlpha(int)));
    QObject::disconnect(cancel,SIGNAL(clicked(bool)),this,SLOT(hide()));
    QObject::disconnect(accept,SIGNAL(clicked(bool)),this,SLOT(ok()));
    delete pal;
    delete linePal;
    delete slider;
    delete redLabel;
    delete greenLabel;
    delete blueLabel;
    delete alphaLabel;
    delete redSpin;
    delete greenSpin;
    delete blueSpin;
    delete alphaSpin;
    delete accept;
    delete cancel;
    delete colorLabel;
    delete colorLabelName;
    delete pix;
    delete miniLay1;
    delete miniLay2;
    delete miniLay3;
    delete miniLay4;
    delete miniLay5;
    delete lay1;
    delete lay2;
    delete lay3;
    delete globalLay;
}

void Gradient::setRed(int a)
{
    curColor.setRed(a);
    pix->fill(curColor);
    colorLabel->setPixmap(*pix);
}

void Gradient::setGreen(int a)
{
    curColor.setGreen(a);
    pix->fill(curColor);
    colorLabel->setPixmap(*pix);
}

void Gradient::setBlue(int a)
{
    curColor.setBlue(a);
    pix->fill(curColor);
    colorLabel->setPixmap(*pix);
}

void Gradient::setAlpha(int a)
{
    curColor.setAlpha(a);
    pix->fill(curColor);
    colorLabel->setPixmap(*pix);
}

void Gradient::ok()
{
    emit sendColor(curColor);
    this->hide();
}
