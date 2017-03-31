#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QWidget>
#include "floatvalidator.h"
class QStyleOptionViewItem;
class QModelIndex;

class TableDelegate:public QItemDelegate
{
public:
    QWidget *createEditor(QWidget *parent,
        const QStyleOptionViewItem &/* option */,
        const QModelIndex &index) const
    {
        QLineEdit *editor = new QLineEdit(parent);
        if (index.parent().parent().parent().isValid()) //планета
        {
            if (index.column()>0 && index.column()<5)
                editor->setValidator(new FloatValidator(editor));
            else editor->setMaxLength(30);
            return editor;
        }
        if (index.parent().parent().isValid()) //звезда
        {
            if (index.column()>2 && index.column()<7)
                editor->setValidator(new FloatValidator(editor));
            else editor->setMaxLength(30);
            return editor;
        }
        if (index.parent().isValid()) //созвездие
        {
            if (index.column()==3)
                editor->setValidator(new FloatValidator(editor));
            if (index.column()==4)
                editor->setValidator(new QIntValidator(editor));
            else editor->setMaxLength(30);
            return editor;
        }
        if (index.column()>1 && index.column()<5)
            editor->setValidator(new FloatValidator(editor));
        else editor->setMaxLength(30);
        return editor;
    }
};

#endif // TABLEDELEGATE_H
