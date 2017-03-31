#include "palette.h"
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QtGlobal>

void Palette::drawCursor(const QPoint& point)
{
    QPainter painter(image);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(QPoint(point.x()-7,point.y()-2),QPoint(QPoint(point.x()-5,point.y()-1))));
    painter.drawRect(QRect(QPoint(point.x()-2,point.y()-7),QPoint(QPoint(point.x()-1,point.y()-5))));
    painter.drawRect(QRect(QPoint(point.x()+2,point.y()-2),QPoint(QPoint(point.x()+4,point.y()-1))));
    painter.drawRect(QRect(QPoint(point.x()-2,point.y()+2),QPoint(QPoint(point.x()-1,point.y()+4))));
    painter.setPen(Qt::white);
    painter.drawLine(QPoint(point.x()-6,point.y()-1),QPoint(point.x()-5,point.y()-1));
    painter.drawLine(QPoint(point.x()-1,point.y()-6),QPoint(point.x()-1,point.y()-5));
    painter.drawLine(QPoint(point.x()+3,point.y()-1),QPoint(point.x()+4,point.y()-1));
    painter.drawLine(QPoint(point.x()-1,point.y()+3),QPoint(point.x()-1,point.y()+4));
    painter.end();
    this->update();
}

Palette::Palette(QString str,QWidget* parent):QWidget(parent)
{
    image=new QImage(str);
    if (image->isNull())
    {
        QMessageBox::critical(this,"Ошибка 32", "Критическая ошибка, свяжитесь с разработчиком");
        qFatal("Ошибка конструктора класса Palette, не удалось открыть изображение.");
    }
    this->setFixedSize(image->size());
    cache=*image;
}

Palette::Palette(QImage& img,QWidget* parent):QWidget(parent)
{
    image=new QImage(img);
    this->setFixedSize(image->size());
    cache=*image;
}

Palette::~Palette()
{
    delete image;
}

bool Palette::load(QString str)
{
    QImage c;
    if (!c.load(str))
    {
        QMessageBox::critical(this,"Ошибка", "Невозможно открыть изображение");
        return false;
    }
    delete image;
    image=new QImage(c.size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(image);
    painter.drawImage(0,0,c);
    this->setFixedSize(image->size());
    cache=*image;
    return true;
}

void Palette::mousePressEvent(QMouseEvent* pe)
{
    if (pe->button()==Qt::LeftButton)
    {
        *image=cache;
        this->update();
        QColor col=this->image->pixel(pe->pos());
        this->drawCursor(pe->pos());
        emit getColor(col);
    }
}

void Palette::mouseMoveEvent(QMouseEvent* pe)
{
    if (pe->buttons() & Qt::LeftButton)
    {
        if (image->rect().contains(pe->pos()))
        {
            *image=cache;
            this->update();
            QColor col=this->image->pixel(pe->pos());
            this->drawCursor(pe->pos());
            emit getColor(col);
        }
    }
}

void Palette::leaveEvent(QEvent*)
{
    *image=cache;
}

void Palette::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image);
}
