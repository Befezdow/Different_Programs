#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QMouseEvent>

class Slider:public QSlider
{
public:
    Slider(Qt::Orientation o=Qt::Horizontal,QWidget *parent = Q_NULLPTR):QSlider(o,parent)
    {
    }
protected:
    void mousePressEvent(QMouseEvent *ev)
    {
        int x=ev->pos().x();
        int width=this->width();
        float otn=(float)x/width;
        int num=static_cast<int>(otn*this->maximum());
        this->setValue(num);
        emit this->sliderMoved(num);
    }
    void mouseMoveEvent(QMouseEvent *ev)
    {
        int x=ev->pos().x();
        int width=this->width();
        float otn=(float)x/width;
        int num=static_cast<int>(otn*this->maximum());
        this->setValue(num);
        emit this->sliderMoved(num);
    }
};

#endif // SLIDER_H
