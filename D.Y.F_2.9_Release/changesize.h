#ifndef CHANGESIZE_H
#define CHANGESIZE_H

#include <QWidget>
class QSpinBox;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class ChangeSize:public QWidget
{
    Q_OBJECT
    QSpinBox* spb1;
    QSpinBox* spb2;
    QPushButton* ok;
    QPushButton* cancel;
    QLabel* lbl1;
    QLabel* lbl2;
    QVBoxLayout* lay1;
    QVBoxLayout* lay2;
    QHBoxLayout* lay3;
    QHBoxLayout* lay4;
    QVBoxLayout* lay;
public:
    ChangeSize(QWidget* parent=0);
    ~ChangeSize();
private slots:
    void send();
signals:
    void sendSize(QSize);
};

#endif // CHANGESIZE_H
