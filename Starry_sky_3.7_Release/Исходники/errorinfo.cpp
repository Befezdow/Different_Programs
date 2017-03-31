#include "errorinfo.h"
#include <QtWidgets>

ErrorInfo::ErrorInfo(QWidget* parent):QWidget(parent)
{
    lbl=new QLabel;
    button=new QPushButton("Ок");
    lay=new QVBoxLayout;
    lay->addWidget(lbl);
    lay->addWidget(button);
    this->setLayout(lay);
    QObject::connect(button,SIGNAL(clicked(bool)),this,SLOT(hide()));
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    QFont font = lbl->font();
    font.setPointSize(10);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setFixedSize(250,100);
    this->setWindowTitle("Ошибка");
}
ErrorInfo::~ErrorInfo()
{
    QObject::disconnect(button,SIGNAL(clicked(bool)),this,SLOT(show()));
    delete lbl;
    delete button;
    delete lay;
}
void ErrorInfo::getError(QString str)
{
    lbl->setText(str);
    this->show();
}
