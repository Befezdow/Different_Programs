#include <QApplication>
#include "sky.h"
#include "menubar.h"
#include "errorinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sky *data=new Sky;
    MenuBar *menu=new MenuBar(data,&a);
    ErrorInfo *err=new ErrorInfo;
    QObject::connect(data,SIGNAL(error(QString)),err,SLOT(getError(QString)));
    QObject::connect(menu,SIGNAL(error(QString)),err,SLOT(getError(QString)));
    QVBoxLayout *lay=new QVBoxLayout;
    lay->setMargin(0);
    lay->addWidget(menu);
    lay->addWidget(data);
    QWidget *wgt=new QWidget;
    wgt->setLayout(lay);
    wgt->resize(752,500);
    wgt->setWindowTitle("БД звездного неба");
    wgt->show();
    return a.exec();
}
