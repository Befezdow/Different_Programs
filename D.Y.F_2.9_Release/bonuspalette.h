#ifndef BONUSPALETTE_H
#define BONUSPALETTE_H

#include <QWidget>
class QImage;
class QColor;
class QPaintEvent;

class BonusPalette:public QWidget
{
    Q_OBJECT
    QImage* image;
public:
    BonusPalette(QWidget* parent=0);
    ~BonusPalette();
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void changeColor(QColor col);
    void cacheSlider(int num);
signals:
    void getColor(QColor);
};

#endif // BONUSPALETTE_H
