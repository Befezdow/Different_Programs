#include "menubar.h"

MenuBar::MenuBar(Sky* model,QApplication *app, QWidget* parent):QMenuBar(parent)
{
    base=new QMenu("База");
    file=new QMenu("Файл");
    this->addMenu(base);
    this->addMenu(file);
    this->addSeparator();
    info=addAction("О программе");
    add=new QMenu("Добавить");
    base->addMenu(add);
    addGalaxy=add->addAction("Галактику");
    addMultiStar=add->addAction("Созвездие");
    addStar=add->addAction("Звезду");
    addPlanet=add->addAction("Планету");
    find=base->addAction("Найти объект");
    base->addSeparator();
    quit=base->addAction("Выход");
    save=file->addAction("Сохранить в файл");
    load=file->addAction("Загрузить из файла");
    wgt1=new AddGalaxy;
    wgt2=new AddMultiStar;
    wgt3=new AddStar;
    wgt4=new AddPlanet;
    wgt5=new Find;
    wgt6=new SaveData;
    wgt7=new LoadData;
    lbl=new QLabel("Это самопальная версия БД звездного неба и,\n"
                   "к тому же, мой первый проект на QT. @Befezdow\n"
                   "HotKeys:\n Delete - удалить строку\n End - редактировать\n"
                   "Page Down - Добавить объект к текущ. родителю");
    QFont font = lbl->font();
    font.setPointSize(10);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lbl->setFixedSize(QSize(400,150));
    lbl->setWindowTitle("О программе");
    QObject::connect(addGalaxy,SIGNAL(triggered(bool)),wgt1,SLOT(show()));
    QObject::connect(addMultiStar,SIGNAL(triggered(bool)),wgt2,SLOT(show()));
    QObject::connect(addStar,SIGNAL(triggered(bool)),wgt3,SLOT(show()));
    QObject::connect(addPlanet,SIGNAL(triggered(bool)),wgt4,SLOT(show()));
    QObject::connect(quit,SIGNAL(triggered(bool)),app,SLOT(quit()));
    QObject::connect(find,SIGNAL(triggered(bool)),wgt5,SLOT(show()));
    QObject::connect(info,SIGNAL(triggered(bool)),lbl,SLOT(show()));
    QObject::connect(save,SIGNAL(triggered(bool)),wgt6,SLOT(show()));
    QObject::connect(load,SIGNAL(triggered(bool)),wgt7,SLOT(show()));
    QObject::connect(wgt1,SIGNAL(send(galaxy&)),model,SLOT(addGalaxy(galaxy&)));
    QObject::connect(wgt2,SIGNAL(send(multistar&)),model,SLOT(addMultiStar(multistar&)));
    QObject::connect(wgt3,SIGNAL(send(star&)),model,SLOT(addStar(star&)));
    QObject::connect(wgt4,SIGNAL(send(planet&)),model,SLOT(addPlanet(planet&)));
    QObject::connect(wgt5,SIGNAL(send(QString)),model,SLOT(find(QString)));
    QObject::connect(wgt6,SIGNAL(send(QString)),model,SLOT(save(QString)));
    QObject::connect(wgt7,SIGNAL(send(QString)),model,SLOT(load(QString)));
    QObject::connect(wgt1,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(wgt2,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(wgt3,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(wgt4,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(wgt7,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
}
MenuBar::~MenuBar()
{
    QObject::disconnect(wgt1,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(wgt2,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(wgt3,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(wgt4,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(wgt7,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(addGalaxy,SIGNAL(triggered(bool)),wgt1,SLOT(show()));
    QObject::disconnect(addMultiStar,SIGNAL(triggered(bool)),wgt2,SLOT(show()));
    QObject::disconnect(addStar,SIGNAL(triggered(bool)),wgt3,SLOT(show()));
    QObject::disconnect(addPlanet,SIGNAL(triggered(bool)),wgt4,SLOT(show()));
    QObject::disconnect(find,SIGNAL(triggered(bool)),wgt5,SLOT(show()));
    QObject::disconnect(info,SIGNAL(triggered(bool)),lbl,SLOT(show()));
    QObject::disconnect(save,SIGNAL(triggered(bool)),wgt6,SLOT(show()));
    QObject::disconnect(load,SIGNAL(triggered(bool)),wgt7,SLOT(show()));
    delete base;
    delete file;
    delete info;
    delete add;
    delete find;
    delete addGalaxy;
    delete addMultiStar;
    delete addStar;
    delete addPlanet;
    delete save;
    delete load;
    delete quit;
    delete wgt1;
    delete wgt2;
    delete wgt3;
    delete wgt4;
    delete wgt5;
    delete lbl;
    delete wgt6;
    delete wgt7;
}
