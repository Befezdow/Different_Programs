#include "loaddata.h"

LoadData::LoadData(QWidget *parent):QWidget(parent)
{
    model=new QFileSystemModel;
    view=new QTreeView;
    button=new QPushButton("Ок");
    edit=new QLineEdit;
    model->setRootPath(QDir::rootPath());
    view->setModel(model);
    lay1=new QVBoxLayout;
    lay2=new QHBoxLayout;
    lbl=new QLabel("Выберите файл для загрузки");
    QFont font = lbl->font();
    font.setPointSize(10);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter);
    lay2->addWidget(edit);
    lay2->addWidget(button);
    lay1->addWidget(lbl);
    lay1->addWidget(view);
    lay1->addLayout(lay2);
    this->setLayout(lay1);
    QObject::connect(button,SIGNAL(clicked(bool)),this,SLOT(sendPath()));
    QObject::connect(view,SIGNAL(clicked(QModelIndex)),this,SLOT(setEditLine(QModelIndex)));
    this->setFixedSize(600,400);
    view->setColumnWidth(0,250);
    this->setWindowTitle("Загрузка из файла");
}
LoadData::~LoadData()
{
    QObject::disconnect(button,SIGNAL(clicked(bool)),this,SLOT(sendPath()));
    QObject::disconnect(view,SIGNAL(clicked(QModelIndex)),this,SLOT(setEditLine(QModelIndex)));
    delete model;
    delete view;
    delete button;
    delete edit;
    delete lay1;
    delete lay2;
    delete lbl;
}
void LoadData::setEditLine(QModelIndex index)
{
    QString str=model->filePath(index);
    edit->setText(str);
}

void LoadData::sendPath()
{
    QString str=edit->text();
    QString test="";
    for (int i=str.size()-4;i<str.size();i++)
        test+=str[i];
    if (test==".txt")
    {
        emit send(str);
        this->hide();
    }
    else emit error("Некорректный формат файла.\nПожалуйста, выберите другой.");
}
