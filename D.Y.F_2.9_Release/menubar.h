#ifndef MENUBAR_H
#define MENUBAR_H

#include "changesize.h"
#include "paintarea.h"
#include "yesno.h"
#include "settingswidget.h"
#include <QMenuBar>
class QMenu;
class QAction;
class QLabel;
class QApplication;
class QWidget;

class MenuBar:public QMenuBar
{
    Q_OBJECT
    QMenu* file;
    QMenu* edit;
    QAction* info;
    QAction* save;
    QAction* saveas;
    QAction* load;
    QAction* add;
    QAction* change;
    QAction* quit;
    QAction* back;
    QAction* front;
    QAction* settings;
    QLabel* lbl;
    ChangeSize* resizer;
    YesNo* asker;
    SettingsWidget* swgt;
    bool state;
public:
    MenuBar(PaintArea* area,QApplication *app, QWidget* parent=0);
    ~MenuBar();
private slots:
    void askArea();
    void changeState(bool a);
signals:
    void ask();
};

#endif // MENUBAR_H
