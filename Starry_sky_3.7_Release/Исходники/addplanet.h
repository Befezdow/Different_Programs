#ifndef ADDPLANET_H
#define ADDPLANET_H

#include "galaxycomponents.h"
#include "floatvalidator.h"
#include <QWidget>
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;


class AddPlanet:public QWidget
{
    Q_OBJECT
    QLabel *lname;
    QLabel *lroz;
    QLabel *lpvvo;
    QLabel *lrad;
    QLabel *lsrpl;
    QLabel *lsname;
    QLineEdit *ename;
    QLineEdit *eroz;
    QLineEdit *epvvo;
    QLineEdit *erad;
    QLineEdit *esrpl;
    QLineEdit *esname;
    QVBoxLayout *lay;
    QHBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;
    QHBoxLayout *lay4;
    QHBoxLayout *lay5;
    QHBoxLayout *lay6;
    QPushButton *button;
    FloatValidator *validator1;
public:
    AddPlanet(QWidget *parent=0);
    ~AddPlanet();
private slots:
    void sendInfo();
public slots:
    void setParent(QString str);
signals:
    void send(planet&);
    void error(QString);
};

#endif // ADDPLANET_H
