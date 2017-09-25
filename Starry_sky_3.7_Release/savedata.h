#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <QtWidgets>

class SaveData:public QWidget
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
    SaveData(QWidget *parent=0);
    ~SaveData();
private slots:
    void setEditLine(QModelIndex index);
    void sendPath();
signals:
    void send(QString);
};

#endif // SAVEDATA_H
