#ifndef PENWIDTH_H
#define PENWIDTH_H

#include <QWidget>
class QLabel;
class QSpinBox;
class QComboBox;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;

class PenWidth:public QWidget
{
    Q_OBJECT
    QLabel* pw;
    QLabel* pl;
    QLabel* lw;
    QSpinBox* pspb;
    QSpinBox* lspb;
    QComboBox* pcmb;
    QHBoxLayout* hlay1;
    QHBoxLayout* hlay2;
    QHBoxLayout* lay;
    QGroupBox* gb1;
    QGroupBox* gb2;
public:
    PenWidth(QWidget* parent=0);
    ~PenWidth();
signals:
    void getPenWidth(int);
    void getLasWidth(int);
    void getLine(int);
};

#endif // PENWIDTH_H
