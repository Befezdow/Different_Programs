#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include "sky.h"
#include "addgalaxy.h"
#include "addmultistar.h"
#include "addstar.h"
#include "addplanet.h"
#include "find.h"
#include "savedata.h"
#include "loaddata.h"
class QMenu;
class QAction;
class QLabel;
class QString;


class MenuBar:public QMenuBar
{
    Q_OBJECT
    QMenu* base;
    QMenu* file;
    QAction* info;
    QMenu* add;
    QAction* find;
    QAction* addGalaxy;
    QAction* addMultiStar;
    QAction* addStar;
    QAction* addPlanet;
    QAction* save;
    QAction* load;
    QAction* quit;
    AddGalaxy* wgt1;
    AddMultiStar* wgt2;
    AddStar* wgt3;
    AddPlanet* wgt4;
    Find *wgt5;
    QLabel* lbl;
    SaveData *wgt6;
    LoadData *wgt7;

public:
    MenuBar(Sky* model,QApplication *app, QWidget* parent=0);
    ~MenuBar();
signals:
    void error(QString);
};

#endif // MENUBAR_H
