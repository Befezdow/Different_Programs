#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QtWidgets>

class MyDelegate:public QStyledItemDelegate
{
public:
    MyDelegate(QObject* obj=0):QStyledItemDelegate(obj) {}
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
    const QModelIndex& index) const
    {
        if (option.state & QStyle::State_Selected)
        {
            QRect rect=option.rect;
            painter->setBrush(Qt::gray);
            painter->setPen(Qt::NoPen);
            painter->setClipRect(rect.left()-3,rect.top()-3,rect.right()-3,rect.bottom()-3);
            painter->drawRect(rect);
        }
        QStyledItemDelegate::paint(painter,option,index);
    }
};

#endif // MYDELEGATE_H
