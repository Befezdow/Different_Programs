#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

class MainWindow: public QWidget
{
    Q_OBJECT
    QPushButton* button;
    QLabel *lbl;
    QVBoxLayout* lay;
public:
    MainWindow(QString defStr,QWidget* parent=Q_NULLPTR);

public slots:
    void setText(QString str);

signals:
    void needHokku();
};

#endif // MAINWINDOW_H
