#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <QtWidgets>

class MouseFilter : public QObject
{
protected:
    virtual bool eventFilter(QObject*, QEvent*)
    {
        if (pe->type() == QEvent::ContextMenu)

        return true;
    }

public:
    MouseFilter(QObject* pobj = 0): QObject(pobj) {}

};
#endif // MOUSEFILTER_H
