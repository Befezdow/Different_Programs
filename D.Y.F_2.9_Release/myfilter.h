#ifndef MYFILTER_H
#define MYFILTER_H

#include <QtWidgets>

class MyFilter:public QObject
{
protected:
    bool eventFilter(QObject *watched, QEvent *event)
    {
        if (event->type()==QEvent::Wheel)
            return true;
        else
            return false;
    }
};

#endif // MYFILTER_H
