#ifndef ADDMULTISTAR_H
#define ADDMULTISTAR_H

#include "galaxycomponents.h"
#include "floatvalidator.h"
#include <QWidget>
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;
class QIntValidator;


class AddMultiStar:public QWidget
{
    Q_OBJECT
    QLabel *lname;
    QLabel *llnaz;
    QLabel *lsokr;
    QLabel *lplos;
    QLabel *lchzv;
    QLabel *lgname;
    QLineEdit *ename;
    QLineEdit *elnaz;
    QLineEdit *esokr;
    QLineEdit *eplos;
    QLineEdit *echzv;
    QLineEdit *egname;
    QVBoxLayout *lay;
    QHBoxLayout *lay1;
    QHBoxLayout *lay2;
    QHBoxLayout *lay3;
    QHBoxLayout *lay4;
    QHBoxLayout *lay5;
    QHBoxLayout *lay6;
    QPushButton *button;
    FloatValidator *validator1;
    QIntValidator *validator2;
public:
    AddMultiStar(QWidget *parent=0);
    ~AddMultiStar();
private slots:
    void sendInfo();
public slots:
    void setParent(QString str);
signals:
    void send(multistar&);
    void error(QString);
};


#endif // ADDMULTISTAR_H
