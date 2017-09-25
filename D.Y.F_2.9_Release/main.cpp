#include "paintarea.h"
#include "colorsettings.h"
#include "toolpanel.h"
#include "myscrollarea.h"
#include "menubar.h"
#include "penwidth.h"
#include "globalwidget.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlobalWidget* window=new GlobalWidget;
    MyScrollArea* scroll=new MyScrollArea;
    PaintArea* area=new PaintArea;
    scroll->setWidget(area);
    scroll->resize(500,500);
    ColorSettings* settings=new ColorSettings;
    ToolPanel* tool=new ToolPanel;
    MenuBar* menu=new MenuBar(area,&a);
    PenWidth* pw=new PenWidth;
    menu->setFocusProxy(area);
    tool->setFocusProxy(area);
    settings->setFocusProxy(area);
    pw->setFocusProxy(area);
    QObject::connect(tool,SIGNAL(SendNum(int)),area,SLOT(changeTool(int)));
    QObject::connect(settings,SIGNAL(sendColor(bool,QColor)),area,SLOT(changeColor(bool,QColor)));
    QObject::connect(area,SIGNAL(sendColor(QColor)),settings,SLOT(setColor(QColor)));
    QObject::connect(area,SIGNAL(getScroll(int,int)),scroll,SLOT(scrollArea(int,int)));
    QObject::connect(pw,SIGNAL(getPenWidth(int)),area,SLOT(changePenWidth(int)));
    QObject::connect(pw,SIGNAL(getLasWidth(int)),area,SLOT(changeLasWidth(int)));
    QObject::connect(pw,SIGNAL(getLine(int)),area,SLOT(changeLine(int)));
    QObject::connect(window,SIGNAL(ask()),area,SLOT(dif()));
    QObject::connect(area,SIGNAL(getDif(bool)),window,SLOT(changeState(bool)));
    QObject::connect(window,SIGNAL(save()),area,SLOT(save()));
    QObject::connect(window,SIGNAL(save()),&a,SLOT(quit()));
    QObject::connect(window,SIGNAL(clos()),&a,SLOT(quit()));
    QVBoxLayout* lay1=new QVBoxLayout;
    QVBoxLayout* lay2=new QVBoxLayout;
    QHBoxLayout* lay3=new QHBoxLayout;
    lay1->addWidget(tool);
    lay1->addWidget(settings);
    lay1->setAlignment(tool,Qt::AlignTop | Qt::AlignHCenter);
    lay1->setAlignment(settings,Qt::AlignHCenter);
    lay1->addStretch(1);
    lay2->addWidget(pw);
    lay2->addWidget(scroll);
    lay3->addLayout(lay1);
    lay3->addLayout(lay2);
    lay3->setMenuBar(menu);
    window->setLayout(lay3);
    window->show();
    return a.exec();
}
