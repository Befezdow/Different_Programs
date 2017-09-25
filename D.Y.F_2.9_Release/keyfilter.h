#ifndef KEYFILTER_H
#define KEYFILTER_H

#include <QObject>
#include <QKeyEvent>

class KeyFilter:public QObject
{
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event)
    {
        if (static_cast<QKeyEvent*>(event)->key()==Qt::Key_Z)
    }
};

#endif // KEYFILTER_H
