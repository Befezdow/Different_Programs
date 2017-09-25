#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
class QImage;
class QString;
class QMouseEvent;
class QEvent;
class QPaintEvent;
class QColor;
class QPoint;

class Palette:public QWidget
{
    Q_OBJECT
    QImage *image;
    QImage cache;
    void drawCursor(const QPoint& point);
public:
    Palette(QString str=":/resources/palette.png",QWidget* parent=0);
    Palette(QImage& img,QWidget* parent=0);
    ~Palette();
    bool load(QString str);
protected:
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent*);
signals:
    void getColor(QColor);
};

#endif // PALETTE_H
