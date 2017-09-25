#include "sky.h"

QTextStream& operator<<(QTextStream& stream,Sky& data)
{
    QStandardItem* item;
    QStandardItem* item1;
    QStandardItem* item2;
    QStandardItem *item3;
    int i,j,m,l,p;
    stream<<(QString)"Галактики:\n";
    for (i=0;i<data.model->rowCount();i++)
    {
        for(j=0;j<data.model->columnCount();j++)
        {
            item=data.model->item(i,j);
            QString str=item->data(Qt::DisplayRole).toString();
            stream<<str;
            if (j!=4) stream<<'\t';
        }
    }
    stream<<'\n';
    stream<<(QString)"Созвездия:\n";
    for (i=0;i<data.model->rowCount();i++)
    {
        item=data.model->item(i);
        if (item->hasChildren())
        {
            for (j=1;j<item->rowCount();j++)
            {
                for (m=0;m<item->columnCount();m++)
                {
                    item1=item->child(j,m);
                    QString str=item1->data(Qt::DisplayRole).toString();
                    stream<<str;
                    if (m!=5) stream<<'\t';
                }
            }
        }
    }
    stream<<'\n';
    stream<<(QString)"Звезды:\n";
    for (i=0;i<data.model->rowCount();i++)
    {
        item=data.model->item(i);
        if (item->hasChildren())
        {
            for (j=1;j<item->rowCount();j++)
            {
                item1=item->child(j);
                if (item1->hasChildren())
                {
                    for (m=1;m<item1->rowCount();m++)
                    {
                        for (l=0;l<item1->columnCount();l++)
                        {
                            item2=item1->child(m,l);
                            QString str=item2->data(Qt::DisplayRole).toString();
                            stream<<str;
                            if (l!=7) stream<<'\t';
                        }
                    }
                }
            }
        }
    }
    stream<<'\n';
    stream<<(QString)"Планеты:\n";
    for (i=0;i<data.model->rowCount();i++)
    {
        item=data.model->item(i);
        if (item->hasChildren())
        {
            for (j=1;j<item->rowCount();j++)
            {
                item1=item->child(j);
                if (item1->hasChildren())
                {
                    for (m=1;m<item1->rowCount();m++)
                    {
                        item2=item1->child(m);
                        if (item2->hasChildren())
                        {
                            for (l=1;l<item2->rowCount();l++)
                            {
                                for (p=0;p<item2->columnCount();p++)
                                {
                                    item3=item2->child(l,p);
                                    QString str=item3->data(Qt::DisplayRole).toString();
                                    stream<<str;
                                    if (p!=5) stream<<'\t';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return stream;
}
