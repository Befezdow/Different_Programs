#ifndef YESNO_H
#define YESNO_H

#include <QWidget>
class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class YesNo:public QWidget
{
    Q_OBJECT
    QPushButton* pb1;
    QPushButton* pb2;
    QPushButton* pb3;
    QLabel* lbl;
    QHBoxLayout* lay1;
    QVBoxLayout* lay2;
public:
    YesNo(QWidget* parent=0);
    ~YesNo();
signals:
    void yes();
    void no();
    void clos();
};

#endif // YESNO_H
