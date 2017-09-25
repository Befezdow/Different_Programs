#include "generator.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir=QDir::currentPath();
    if (!dir.cd("Dictionaries"))
    {
        QMessageBox::critical(Q_NULLPTR,"Error","Dictories don't exist",QMessageBox::Ok);
        qApp->exit(1);
    }

    QVector<QString> dict;
    dict.push_back(dir.absoluteFilePath("templates.txt"));
    dict.push_back(dir.absoluteFilePath("he.txt"));
    dict.push_back(dir.absoluteFilePath("she.txt"));
    dict.push_back(dir.absoluteFilePath("they.txt"));
    dict.push_back(dir.absoluteFilePath("whatHe.txt"));
    dict.push_back(dir.absoluteFilePath("whatShe.txt"));
    dict.push_back(dir.absoluteFilePath("whatThey.txt"));
    dict.push_back(dir.absoluteFilePath("does.txt"));
    dict.push_back(dir.absoluteFilePath("do.txt"));
    dict.push_back(dir.absoluteFilePath("didHe.txt"));
    dict.push_back(dir.absoluteFilePath("didShe.txt"));
    dict.push_back(dir.absoluteFilePath("didThey.txt"));
    dict.push_back(dir.absoluteFilePath("how.txt"));
    dict.push_back(dir.absoluteFilePath("where.txt"));

    Generator* generator=new Generator;
    generator->loadDictionaries(dict);

    QString hokku;
    try
    {
        hokku=generator->generate();
    }
    catch (QString str)
    {
        QMessageBox::critical(Q_NULLPTR,"Error",str,QMessageBox::Ok);
        qApp->exit(1);
    }

    MainWindow* window=new MainWindow(hokku);

    QObject::connect(generator,SIGNAL(takeHokku(QString)),window,SLOT(setText(QString)));
    QObject::connect(window,SIGNAL(needHokku()),generator,SLOT(generateHokku()));

    window->show();

    return a.exec();
}
