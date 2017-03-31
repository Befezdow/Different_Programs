#include "find.h"
#include <QtWidgets>


Find::Find(QWidget *parent):QWidget(parent)
{
    lbl=new QLabel("&Название объекта:");
    QFont font = lbl->font();
    font.setPointSize(10);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter);
    edit=new QLineEdit;
    edit->setMaxLength(30);
    button=new QPushButton("Искать");
    lay=new QVBoxLayout;
    lay->addWidget(lbl);
    lay->addWidget(edit);
    lbl->setBuddy(edit);
    lay->addWidget(button);
    this->setLayout(lay);
    this->setWindowTitle("Поиск объекта");
    this->setFixedSize(200,100);
    QObject::connect(button,SIGNAL(clicked(bool)),this,SLOT(sendName()));
}
Find::~Find()
{
    QObject::disconnect(button,SIGNAL(clicked(bool)),this,SLOT(sendName()));
    delete lay;
    delete button;
    delete edit;
    delete lbl;
}

void Find::sendName()
{
    emit send(edit->text());
    this->hide();
}
