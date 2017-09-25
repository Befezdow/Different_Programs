#include "bonuspalette.h"
#include <QPainter>

BonusPalette::BonusPalette(QWidget* parent):QWidget(parent)
{
    image=new QImage(10,250,QImage::Format_ARGB32_Premultiplied);
    this->setFixedSize(image->size());
    QLinearGradient gradient(0,0,0,250);
    gradient.setColorAt(0,Qt::white);
    gradient.setColorAt(1,Qt::black);
    QPainter painter(image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawRect(0,0,10,250);
    painter.end();
}

BonusPalette::~BonusPalette()
{
    delete image;
}

void BonusPalette::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image);
}

void BonusPalette::changeColor(QColor col)
{
    QLinearGradient gradient(0,0,0,250);
    gradient.setColorAt(0,Qt::white);
    gradient.setColorAt(0.05,Qt::white);
    gradient.setColorAt(0.5,col);
    gradient.setColorAt(0.95,Qt::black);
    gradient.setColorAt(1,Qt::black);
    QPainter painter(image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawRect(0,0,10,250);
    painter.end();
    this->update();
}

void BonusPalette::cacheSlider(int num)
{
    QColor col=image->pixel(5,250-num);
    emit getColor(col);
}
