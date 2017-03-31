#include "sky.h"

QTextStream& operator>>(QTextStream& stream,Sky& data)
{
    QString str,s;
    QStringList list;
    QStandardItem* item;
    int check;
    str=stream.readLine(255);
    if (str!="Галактики:")
    {
        emit data.error("Ошибка формата файла.\nВыберите корректный файл");
        return stream;
    }
    while (1)
    {
        str=stream.readLine(255);
        if (str!="Созвездия:")
        {
            list=str.split('\t');
            check=data.model->rowCount();
            for(int i=0;i<list.size();i++)
            {
                item=new QStandardItem(list.value(i));
                item->setEditable(true);
                data.model->setItem(check,i,item);
            }
        }
        else break;
    }
    while (1)
    {
        str=stream.readLine(255);
        if (str!="Звезды:")
        {
            list=str.split('\t');
            QList<QStandardItem*> parent_list=data.model->findItems(list.back(),Qt::MatchExactly | Qt::MatchRecursive);
            if (parent_list.isEmpty())
            {
                emit data.error("Фатальная ошибка.\nСбой иерархии БД.\nПолучение данных приостановлено.");
                return stream;
            }
            QStandardItem* parent=parent_list.front();
            if (!parent->hasChildren())
            {
                QStandardItem* back=new QStandardItem("Назад");
                back->setEditable(false);
                parent->setChild(0,0,back);
            }
            check=parent->rowCount();
            for (int i=0;i<list.size();i++)
            {
                item=new QStandardItem(list.value(i));
                item->setEditable(true);
                parent->setChild(check,i,item);
            }
        }
        else break;
    }
    while (1)
    {
        str=stream.readLine(255);
        if (str!="Планеты:")
        {
            list=str.split('\t');
            QList<QStandardItem*> parent_list=data.model->findItems(list.back(),Qt::MatchExactly | Qt::MatchRecursive);
            if (parent_list.isEmpty())
            {
                emit data.error("Фатальная ошибка.\nСбой иерархии БД.\nПолучение данных приостановлено.");
                return stream;
            }
            QStandardItem* parent=parent_list.front();
            if (!parent->hasChildren())
            {
                QStandardItem* back=new QStandardItem("Назад");
                back->setEditable(false);
                parent->setChild(0,0,back);
            }
            check=parent->rowCount();
            for (int i=0;i<list.size();i++)
            {
                item=new QStandardItem(list.value(i));
                item->setEditable(true);
                parent->setChild(check,i,item);
            }
        }
        else break;
    }
    while (1)
    {
        str=stream.readLine(255);
        if (!str.isNull())
        {
            list=str.split('\t');
            QList<QStandardItem*> parent_list=data.model->findItems(list.back(),Qt::MatchExactly | Qt::MatchRecursive);
            if (parent_list.isEmpty())
            {
                emit data.error("Фатальная ошибка.\nСбой иерархии БД.\nПолучение данных приостановлено.");
                return stream;
            }
            QStandardItem* parent=parent_list.front();
            if (!parent->hasChildren())
            {
                QStandardItem* back=new QStandardItem("Назад");
                back->setEditable(false);
                parent->setChild(0,0,back);
            }
            check=parent->rowCount();
            for (int i=0;i<list.size();i++)
            {
                item=new QStandardItem(list.value(i));
                item->setEditable(true);
                parent->setChild(check,i,item);
            }
        }
        else break;
    }
    return stream;
}
