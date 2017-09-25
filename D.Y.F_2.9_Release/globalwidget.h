#ifndef GLOBALWIDGET_H
#define GLOBALWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QIcon>
#include "yesno.h"

class GlobalWidget:public QWidget
{
    Q_OBJECT
    YesNo *yn;
    bool state;
    bool saveState;
public:
    GlobalWidget(QWidget* parent=0):QWidget(parent)
    {
        state=false;
        yn=new YesNo;
        QObject::connect(yn,SIGNAL(yes()),this,SIGNAL(save()));
        QObject::connect(yn,SIGNAL(no()),this,SIGNAL(clos()));
        QObject::connect(yn,SIGNAL(yes()),this,SLOT(setTrue()));
        QObject::connect(yn,SIGNAL(no()),this,SLOT(setTrue()));
        QObject::connect(yn,SIGNAL(clos()),this,SLOT(setFalse()));
        QPalette pal;
        pal.setBrush(this->backgroundRole(),QColor(130,212,255));
        this->setPalette(pal);
        this->setWindowTitle("D.Y.F");
        this->setWindowIcon(QIcon(":/resources/main.png"));
    }

    ~GlobalWidget()
    {
        QObject::disconnect(yn,SIGNAL(yes()),this,SIGNAL(save()));
        QObject::disconnect(yn,SIGNAL(no()),this,SIGNAL(clos()));
        QObject::disconnect(yn,SIGNAL(yes()),this,SLOT(setTrue()));
        QObject::disconnect(yn,SIGNAL(no()),this,SLOT(setTrue()));
        QObject::disconnect(yn,SIGNAL(clos()),this,SLOT(setFalse()));
        delete yn;
    }

protected:
    void closeEvent(QCloseEvent* pe)
    {
        emit ask();
        if (saveState)
        {
            yn->show();
        if (state)
            pe->accept();
        else
            pe->ignore();
        }
        else
            pe->accept();
    }

signals:
    void save();
    void clos();
private slots:
    void setTrue()
    {
        state=true;
    }
    void setFalse()
    {
        state=false;
    }
    void changeState(bool a)
    {
        saveState=a;
    }
signals:
    void ask();
};

#endif // GLOBALWIDGET_H
