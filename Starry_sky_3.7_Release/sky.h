#ifndef SKY_H
#define SKY_H

#include <QtWidgets>
#include "galaxycomponents.h"
#include "tabledelegate.h"
#include "addgalaxy.h"
#include "addmultistar.h"
#include "addstar.h"
#include "addplanet.h"

class Sky:public QTableView
{
    Q_OBJECT
    QMenu *menu;
    QStandardItemModel *model;
    TableDelegate *delegate;
    AddGalaxy *addGal;
    AddMultiStar *addMul;
    AddStar *addSta;
    AddPlanet *addPla;
    QModelIndex indexForMenu;
    void setPlanetHeader();
    void setStarHeader();
    void setMultiStarHeader();
    void setGalaxyHeader();
public:
    Sky(QWidget *widget=0, QObject *parent=0);
    ~Sky();
    friend QTextStream& operator<<(QTextStream& stream,Sky& data);
    friend QTextStream& operator>>(QTextStream& stream,Sky& data);
private slots:
    void addGalaxy(galaxy &ob);
    void addMultiStar(multistar &ob);
    void addStar(star &ob);
    void addPlanet(planet &ob);
    void find(QString);
    void slide(const QModelIndex &index);
    void menuActivated(QAction* act);
    void save(QString file_name);
    void load(QString file_name);
protected:
    void contextMenuEvent(QContextMenuEvent* pe);
    void keyPressEvent(QKeyEvent *pe);
signals:
    void error(QString);
};

#endif // SKY_H
