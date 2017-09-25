#ifndef ADDCOOMPONENT_H
#define ADDCOOMPONENT_H

#include "galaxycomponents.h"
#include "percentvalidator.h"
#include "floatvalidator.h"
#include <QWidget>
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;

class AddGalaxy:public QWidget
{
    Q_OBJECT
    QLabel *lname;
    QLabel *ltype;
    QLabel *ldiam;
    QLabel *lmass;
    QLabel *lquan;
    QLineEdit *ename;
    QLineEdit *etype;
    QLineEdit *ediam;
    QLineEdit *emass;
    QLineEdit *equan;
    QVBoxLayout *lay;
    QHBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;
    QHBoxLayout *lay4;
    QHBoxLayout *lay5;
    QPushButton *button;
    FloatValidator *validator1;
    PercentValidator *validator2;
public:
    AddGalaxy(QWidget *parent=0);
    ~AddGalaxy();
private slots:
    void sendInfo();
signals:
    void send(galaxy&);
    void error(QString);
};

#endif // ADDCOOMPONENT_H
