#ifndef LOADDATA_H
#define LOADDATA_H

#include <QtWidgets>

class LoadData:public QWidget
{
    Q_OBJECT
    QFileSystemModel *model;
    QTreeView *view;
    QPushButton *button;
    QLineEdit *edit;
    QVBoxLayout *lay1;
    QHBoxLayout *lay2;
    QLabel *lbl;
public:
    LoadData(QWidget *parent=0);
    ~LoadData();
private slots:
    void setEditLine(QModelIndex index);
    void sendPath();
signals:
    void send(QString);
    void error(QString);
};

#endif // LOADDATA_H
