#include "savedata.h"

SaveData::SaveData(QWidget *parent):QWidget(parent)
{
    model=new QFileSystemModel;
    view=new QTreeView;
    button=new QPushButton("Ок");
    edit=new QLineEdit;
    model->setRootPath(QDir::rootPath());
    view->setModel(model);
    lay1=new QVBoxLayout;
    lay2=new QHBoxLayout;
    lbl=new QLabel("Выберите путь сохранения");
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
    this->setWindowTitle("Сохранение в файл");
}
SaveData::~SaveData()
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
void SaveData::setEditLine(QModelIndex index)
{
    QString str;
    if (model->isDir(index))
        str=model->filePath(index);
    else str=model->filePath(index.parent());
    if (str[str.size()-1]!='/')
        str+="/file_data.txt";
    else str+="file_data.txt";
    edit->setText(str);
}

void SaveData::sendPath()
{
        emit send(edit->text());
        this->hide();
}
