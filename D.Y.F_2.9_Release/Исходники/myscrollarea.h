#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QWidget>
#include <QPoint>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

class MyScrollArea:public QScrollArea
{
    Q_OBJECT
    int dx,dy;
public:
    MyScrollArea(QWidget* parent=0):QScrollArea(parent)
    {
        this->horizontalScrollBar()->setRange(0,10000);
        this->verticalScrollBar()->setRange(0,10000);
        QPalette pal;
        pal.setBrush(this->backgroundRole(),QBrush(Qt::gray));
        this->setPalette(pal);
    }
protected:
    void wheelEvent(QWheelEvent*) {}
private slots:
    void scrollArea(int a,int b)
    {
            int gdx=this->horizontalScrollBar()->value();
            gdx=gdx+a;
            int gdy=this->verticalScrollBar()->value();
            gdy=gdy+b;
            if (gdx>10000)
                gdx=10000;
            if (gdx<0)
                gdx=0;
            if (gdy>10000)
                gdy=10000;
            if (gdy<0)
                gdy=0;
            this->horizontalScrollBar()->setValue(gdx);
            this->verticalScrollBar()->setValue(gdy);
    }
};

#endif // MYSCROLLAREA_H
