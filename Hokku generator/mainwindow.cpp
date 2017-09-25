#include "mainwindow.h"

MainWindow::MainWindow(QString defStr, QWidget *parent):
    QWidget(parent)
{
    button=new QPushButton("Generate");
    lbl=new QLabel(defStr);
    lbl->setAlignment(Qt::AlignCenter);
    lay=new QVBoxLayout;
    lay->addWidget(lbl,0,Qt::AlignCenter);
    lay->addWidget(button,0,Qt::AlignCenter);
    this->setLayout(lay);
    this->setWindowTitle("Dich Generator");
    this->setWindowIcon(QIcon(":/icon.png"));
    connect(button,SIGNAL(clicked(bool)),this,SIGNAL(needHokku()));
}

void MainWindow::setText(QString str)
{
    lbl->setText(str);
}
