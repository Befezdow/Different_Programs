#ifndef FIND_H
#define FIND_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QPushButton;
class QVBoxLayout;

class Find:public QWidget
{
    Q_OBJECT
    QLabel *lbl;
    QLineEdit *edit;
    QPushButton* button;
    QVBoxLayout *lay;
public:
    Find(QWidget *parent=0);
    ~Find();
private slots:
    void sendName();
signals:
    void send(QString);
};

#endif // FIND_H
