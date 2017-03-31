#include "sky.h"


Sky::Sky(QWidget *widget,QObject *parent): QTableView(widget)
{
    menu=new QMenu(this);
    menu->addAction("Изменить");
    menu->addAction("Удалить");
    menu->addAction("Добавить сюда объект");
    connect(menu,SIGNAL(triggered(QAction*)),
            this,SLOT(menuActivated(QAction*)));
    model=new QStandardItemModel(parent);
    this->setModel(model);
    model->insertColumns(0,5);
    QList<QString> header;
    header<<"Название"<<"Вид"<<"Диаметр в св.годах";
    header<<"Масса галактики"<<"Кол-во ЧМ";
    model->setHorizontalHeaderLabels(header);
    verticalHeader()->hide();
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
    this->setColumnWidth(2,150);
    this->setColumnWidth(3,150);
    this->setColumnWidth(4,150);
    QObject::connect(this,SIGNAL(doubleClicked(QModelIndex)),
                     this,SLOT(slide(QModelIndex)));
    resize(523,300);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    delegate=new TableDelegate;
    this->setItemDelegate(delegate);
    this->setSortingEnabled(true);
    addGal=new AddGalaxy;
    addMul=new AddMultiStar;
    addSta=new AddStar;
    addPla=new AddPlanet;
    QObject::connect(addGal,SIGNAL(send(galaxy&)),this,SLOT(addGalaxy(galaxy&)));
    QObject::connect(addMul,SIGNAL(send(multistar&)),this,SLOT(addMultiStar(multistar&)));
    QObject::connect(addSta,SIGNAL(send(star&)),this,SLOT(addStar(star&)));
    QObject::connect(addPla,SIGNAL(send(planet&)),this,SLOT(addPlanet(planet&)));
    QObject::connect(addGal,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(addMul,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(addSta,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::connect(addPla,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
}

Sky::~Sky()
{
    QObject::disconnect(addGal,SIGNAL(send(galaxy&)),this,SLOT(addGalaxy(galaxy&)));
    QObject::disconnect(addMul,SIGNAL(send(multistar&)),this,SLOT(addMultiStar(multistar&)));
    QObject::disconnect(addSta,SIGNAL(send(star&)),this,SLOT(addStar(star&)));
    QObject::disconnect(addPla,SIGNAL(send(planet&)),this,SLOT(addPlanet(planet&)));
    QObject::disconnect(addGal,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(addMul,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(addSta,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    QObject::disconnect(addPla,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
    delete menu;
    delete model;
    delete delegate;
    delete addGal;
    delete addMul;
    delete addSta;
    delete addPla;
}

void Sky::addGalaxy(galaxy &ob)
{
    QList<QStandardItem*> proverka=model->findItems(ob.getName(),Qt::MatchExactly);
    if (!proverka.isEmpty())
    {
        emit error("Объект с таким названием\nуже существует");
        return;
    }
    QList<QString> list;
    list<<ob.getName();
    list<<ob.getType();
    list<<ob.getDiam();
    list<<ob.getMass();
    list<<ob.getQuan();
    int check=model->rowCount();
    for (int i=0;i<list.length();i++)
    {
        QStandardItem *item=new QStandardItem(list.value(i));
        item->setEditable(true);
        model->setItem(check,i,item);
    }
}

void Sky::addMultiStar(multistar &ob)
{
    QList<QStandardItem*> proverka=model->findItems(ob.getName(),Qt::MatchExactly);
    if (!proverka.isEmpty())
    {
        emit error("Объект с таким названием\nуже существует");
        return;
    }
    QList<QString> list;
    list<<ob.getName();
    list<<ob.getLnaz();
    list<<ob.getSokr();
    list<<ob.getPlos();
    list<<ob.getChzv();
    list<<ob.getGname();
    QList<QStandardItem*> list1=model->findItems(ob.getGname(),Qt::MatchExactly);
    if (!list1.isEmpty())
    {
        QStandardItem *item=list1.front();
        int check=item->rowCount();
        if (check==0)
        {
           QStandardItem *back=new QStandardItem("Назад");
           back->setEditable(false);
           item->setChild(0,0,back);
           check++;
        }
        for (int i=0;i<list.length();i++)
        {
            QStandardItem *child=new QStandardItem(list.value(i));
            child->setEditable(true);
            item->setChild(check,i,child);
        }
    }
    else emit error("Галактика-родитель не найдена");
}

void Sky::addStar(star &ob)
{
    QList<QStandardItem*> proverka=model->findItems(ob.getName(),Qt::MatchExactly);
    if (!proverka.isEmpty())
    {
        emit error("Объект с таким названием\nуже существует");
        return;
    }
    QList<QString> list;
    list<<ob.getName();
    list<<ob.getSpkl();
    list<<ob.getCvet();
    list<<ob.getTemp();
    list<<ob.getMass();
    list<<ob.getZvvl();
    list<<ob.getRazm();
    list<<ob.getMname();
    QList<QStandardItem*> list1=model->findItems(ob.getMname(),Qt::MatchExactly | Qt::MatchRecursive);
    if (!list1.isEmpty())
    {
        QStandardItem *item=list1.front();
        int check=item->rowCount();
        if (check==0)
        {
           QStandardItem *back=new QStandardItem("Назад");
           back->setEditable(true);
           item->setChild(0,0,back);
           check++;
        }
        for (int i=0;i<list.length();i++)
        {
            QStandardItem *child=new QStandardItem(list.value(i));
            child->setEditable(true);
            item->setChild(check,i,child);
        }
    }
    else emit error("Созвездие-родитель не найдено");
}

void Sky::addPlanet(planet &ob)
{
    QList<QStandardItem*> proverka=model->findItems(ob.getName(),Qt::MatchExactly | Qt::MatchRecursive);
    if (!proverka.isEmpty())
    {
        emit error("Объект с таким названием\nуже существует");
        return;
    }
    QList<QString> list;
    list<<ob.getName();
    list<<ob.getRoz();
    list<<ob.getPvvo();
    list<<ob.getRad();
    list<<ob.getSrpl();
    list<<ob.getSname();
    QList<QStandardItem*> list1=model->findItems(ob.getSname(),Qt::MatchExactly | Qt::MatchRecursive);
    if (!list1.isEmpty())
    {
        QStandardItem *item=list1.front();
        int check=item->rowCount();
        if (check==0)
        {
           QStandardItem *back=new QStandardItem("Назад");
           back->setEditable(false);
           item->setChild(0,0,back);
           check++;
        }
        for (int i=0;i<list.length();i++)
        {
            QStandardItem *child=new QStandardItem(list.value(i));
            child->setEditable(false);
            item->setChild(check,i,child);
        }
    }
    else emit error("Звезда-родитель не найдена");
}

void Sky::setPlanetHeader()
{
    QList<QString> header;
    header<<"Название"<<"Расст. от звезды";
    header<<"Период вращ."<<"Радиус"<<"Ср. плотность"<<"Звезда";
    model->setHorizontalHeaderLabels(header);
    model->setColumnCount(6);
    this->setColumnWidth(0,100);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,100);
    this->setColumnWidth(3,100);
    this->setColumnWidth(4,100);
    this->setColumnWidth(5,100);
}

void Sky::setStarHeader()
{
    QList<QString> header;
    header<<"Название"<<"Спектр. класс"<<"Цвет";
    header<<"Температура"<<"Масса"<<"Звездн. величина"<<"Размер"<<"Созвездие";
    model->setHorizontalHeaderLabels(header);
    model->setColumnCount(8);
    this->setColumnWidth(0,100);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,100);
    this->setColumnWidth(3,100);
    this->setColumnWidth(4,100);
    this->setColumnWidth(5,120);
    this->setColumnWidth(6,100);
    this->setColumnWidth(7,100);
}

void Sky::setMultiStarHeader()
{
    QList<QString> header;
    header<<"Название"<<"Лат. название";
    header<<"Сокр. лат. назв."<<"Площадь"<<"ЧЗ ярче 6.0^m"<<"Галактика";
    model->setHorizontalHeaderLabels(header);
    model->setColumnCount(6);
    this->setColumnWidth(0,100);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,100);
    this->setColumnWidth(3,100);
    this->setColumnWidth(4,100);
    this->setColumnWidth(5,100);
}

void Sky::setGalaxyHeader()
{
    QList<QString> header;
    header<<"Название"<<"Вид"<<"Диаметр в св.годах";
    header<<"Масса галактики"<<"Кол-во ЧМ";
    model->setHorizontalHeaderLabels(header);
    model->setColumnCount(5);
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,150);
    this->setColumnWidth(2,150);
    this->setColumnWidth(3,150);
    this->setColumnWidth(4,150);
}

void Sky::slide(const QModelIndex &index)
{
    QList<QString> header;
    if (index.data().toString()=="Назад")
    {
        setRootIndex(index.parent().parent());
        if (index.parent().parent().parent().isValid())
        {
            setStarHeader();
            return;
        }
        if (index.parent().parent().isValid())
        {
            setMultiStarHeader();
            return;
        }
        if (index.parent().isValid())
        {
            setGalaxyHeader();
            return;
        }
    }
    if (index.child(0,0).isValid())
    {
        setRootIndex(index);
        if (index.parent().parent().isValid())
        {
            setPlanetHeader();
            return;
        }
        if (index.parent().isValid())
        {
            setStarHeader();
            return;
        }
        setMultiStarHeader();
    }
}

void Sky::find(QString str)
{
    QList<QStandardItem*> list=model->findItems(str,Qt::MatchExactly | Qt::MatchRecursive);
    if (!list.isEmpty())
    {
        QModelIndex index=list.front()->index();
        setRootIndex(index.parent());
        setCurrentIndex(index);
        if (index.parent().parent().parent().isValid())
        {
            setPlanetHeader();
            return;
        }
        if (index.parent().parent().isValid())
        {
            setStarHeader();
            model->setColumnCount(8);
            return;
        }
        if (index.parent().isValid())
        {
            setMultiStarHeader();
            return;
        }
        setGalaxyHeader();
        return;
    }
    else emit error("Объект не найден");
}

void Sky::menuActivated(QAction* act)
{
     QString str=act->text();
     if (str=="Удалить")
     {
         QModelIndex index=indexForMenu;
         model->removeRow(index.row(),index.parent());
     }
     if (str=="Изменить")
         edit(indexForMenu);
     if (str=="Добавить сюда объект")
     {
         QModelIndex index=indexForMenu;
             if (index.parent().parent().parent().isValid())
             {
                 addPla->setParent(index.parent().data().toString());
                 addPla->show();
                 return;
             }
             if (index.parent().parent().isValid())
             {
                 addSta->setParent(index.parent().data().toString());
                 addSta->show();
                 return;
             }
             if (index.parent().isValid())
             {
                 addMul->setParent(index.parent().data().toString());
                 addMul->show();
                 return;
             }
             addGal->show();
             return;
     }

}


void Sky::contextMenuEvent(QContextMenuEvent* pe)
{
    indexForMenu=this->indexAt(pe->pos());
    if (indexForMenu.isValid())
        menu->exec(pe->globalPos());
}

void Sky::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Delete)
    {
        QModelIndex index=currentIndex();
        model->removeRow(index.row(),index.parent());
    }
    if (pe->key() == Qt::Key_End)
    {
        edit(currentIndex());
    }
    if (pe->key() == Qt::Key_PageDown)
    {
        QModelIndex index=currentIndex();
        if (index.column()==0)
        {
            if (index.parent().parent().parent().isValid())
            {
                addPla->setParent(index.parent().data().toString());
                addPla->show();
                return;
            }
            if (index.parent().parent().isValid())
            {
                addSta->setParent(index.parent().data().toString());
                addSta->show();
                return;
            }
            if (index.parent().isValid())
            {
                addMul->setParent(index.parent().data().toString());
                addMul->show();
                return;
            }
            addGal->show();
            return;
        }
    }
}

void Sky::save(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<*this;
    file.close();
}

void Sky::load(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    in>>*this;
    file.close();
}
