#ifndef ERRORINFO_H
#define ERRORINFO_H

#include <QObject>
#include <QWidget>
class QLabel;
class QVBoxLayout;
class QPushButton;
class QString;

class ErrorInfo:public QWidget
{
    Q_OBJECT
    QLabel* lbl;
    QPushButton *button;
    QVBoxLayout *lay;
public:
    ErrorInfo(QWidget* parent=0);
    ~ErrorInfo();
private slots:
    void getError(QString str);
};

#endif // ERRORINFO_H
