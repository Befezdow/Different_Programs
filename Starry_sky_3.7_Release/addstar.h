#ifndef ADDSTAR_H
#define ADDSTAR_H

#include "galaxycomponents.h"
#include "floatvalidator.h"
#include <QWidget>
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;


class AddStar:public QWidget
{
    Q_OBJECT
    QLabel *lname;
    QLabel *lspkl;
    QLabel *lcvet;
    QLabel *ltemp;
    QLabel *lmass;
    QLabel *lzvvl;
    QLabel *lrazm;
    QLabel *lmname;
    QLineEdit *ename;
    QLineEdit *espkl;
    QLineEdit *ecvet;
    QLineEdit *etemp;
    QLineEdit *emass;
    QLineEdit *ezvvl;
    QLineEdit *erazm;
    QLineEdit *emname;
    QVBoxLayout *lay;
    QHBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;
    QHBoxLayout *lay4;
    QHBoxLayout *lay5;
    QHBoxLayout *lay6;
    QHBoxLayout *lay7;
    QHBoxLayout *lay8;
    QPushButton *button;
    FloatValidator *validator1;

public:
    AddStar(QWidget *parent=0);
    ~AddStar();
private slots:
    void sendInfo();
public slots:
    void setParent(QString str);
signals:
    void send(star&);
    void error(QString);
};


#endif // ADDSTAR_H
