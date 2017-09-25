#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>

class MySlider:public QSlider
{
    Q_OBJECT
public:
    MySlider(Qt::Orientation orientation=Qt::Vertical,QWidget* parent=0):QSlider(orientation,parent) {}
private slots:
    void init()
    {
        this->setValue(125);
        emit valueChanged(125);
    }
};

#endif // MYSLIDER_H
