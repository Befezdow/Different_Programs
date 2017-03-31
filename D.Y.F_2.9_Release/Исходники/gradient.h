#ifndef GRADIENT_H
#define GRADIENT_H

#include <QWidget>
#include "palette.h"
#include "bonuspalette.h"
#include "myslider.h"
#include "myspinbox.h"
class QColor;
class QLabel;
class QPushButton;
class QPixmap;
class QHBoxLayout;
class QVBoxLayout;

class Gradient:public QWidget
{
    Q_OBJECT
    Palette* pal;
    BonusPalette* linePal;
    MySlider* slider;
    QColor curColor;
    QLabel* redLabel;
    QLabel* greenLabel;
    QLabel* blueLabel;
    QLabel* alphaLabel;
    MySpinBox* redSpin;
    MySpinBox* greenSpin;
    MySpinBox* blueSpin;
    MySpinBox* alphaSpin;
    QPushButton* accept;
    QPushButton* cancel;
    QLabel* colorLabel;
    QLabel* colorLabelName;
    QPixmap* pix;
    QVBoxLayout* globalLay;
    QHBoxLayout* lay1;
    QHBoxLayout* lay2;
    QHBoxLayout* lay3;
    QVBoxLayout* miniLay1;
    QVBoxLayout* miniLay2;
    QVBoxLayout* miniLay3;
    QVBoxLayout* miniLay4;
    QVBoxLayout* miniLay5;
public:
    Gradient(QWidget* parent=0);
    ~Gradient();
private slots:
    void setRed(int a);
    void setGreen(int a);
    void setBlue(int a);
    void setAlpha(int a);
    void ok();
signals:
    void sendColor(QColor);
};

#endif // GRADIENT_H
