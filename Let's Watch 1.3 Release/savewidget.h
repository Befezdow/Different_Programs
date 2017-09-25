#ifndef SAVEWIDGET_H
#define SAVEWIDGET_H

#include "app.h"
#include <QDesktopWidget>
#include <QIcon>

class SaveWidget:public QWidget
{
    void saveSettings()
    {
        QSettings* settings=App::theApp()->settings();
        settings->beginGroup("/GlobalWidget");
        settings->setValue("/Position",this->pos());
        settings->setValue("/Size",this->size());
        settings->endGroup();
    }

    void loadSettings()
    {
        QSettings* settings=App::theApp()->settings();
        settings->beginGroup("/GlobalWidget");
        QPoint point(qApp->desktop()->screenGeometry().size().width()/4,qApp->desktop()->screenGeometry().size().height()/4);
        this->move(settings->value("/Position",point).toPoint());
        this->resize(settings->value("/Size",QSize(500,500)).toSize());
        settings->endGroup();
    }

public:
    SaveWidget(QWidget* parent=Q_NULLPTR):QWidget(parent)
    {
        this->setWindowTitle("Let's Watch");
        this->setWindowIcon(QIcon(":/res/main.png"));
        this->loadSettings();
    }
    ~SaveWidget()
    {
        this->saveSettings();
    }
};

#endif // SAVEWIDGET_H
