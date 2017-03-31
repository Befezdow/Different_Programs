#ifndef FILTER_H
#define FILTER_H

#include <QtWidgets>

class Filter : public QObject {
protected:
    bool eventFilter (QObject* obj , QEvent* pe)
    {
        if (pe->type() == QEvent::ContextMenu)
        {
           QTableView *view=dynamic_cast<QTableView*>(obj);
           view->setCurrentIndex(QModelIndex());
        }
        return false;
    }
public:
    Filter (QObject* pobj = 0): QObject (pobj ) {}
};

#endif // FILTER_H
