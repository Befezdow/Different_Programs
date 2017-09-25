#ifndef PAINT_H
#define PAINT_H

#include "myscrollarea.h"
#include <QWidget>
#include <QList>
#include <QStack>
#include <QPen>
class QImage;
class QPoint;
class QRect;
class QBrush;
class QString;
class QColor;
class QPaintEvent;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class QSize;

class PaintArea:public QWidget
{
    Q_OBJECT
    QImage *image;
    //cachedata
    QList<QPoint> pointList;
    QPoint beg;
    QPoint tl;
    QPoint br;
    QRect rect;
    QRect clearRect;
    QImage cache;
    QImage globalCache;
    QImage rotCache;
    QImage copyCache;
    QRect rotRect;
    int state;
    int rotState;
    int rotDelta;
    int scaleState;
    int quadState;
    unsigned short int mouseState;
    bool saveState;
    QPoint stScroll;
    QImage exitCache;
    QCursor cacheCursor;
    //end
    enum tool{ram=0,penc,las,pip,zal,rec,tri,ell,fiv,sta,lom,pol};
    tool tec;
    tool curShape;
    QPen curPen;
    QPen curLas;
    QBrush curBrush;
    QString path;
    QStack<QImage> backup;
    int curBackCache;
    int fillSens;
    bool anti;
public:
    PaintArea(QWidget *parent=0);
    ~PaintArea();
private:
    void fill(const QColor &color, const QPoint &point);
    void drawRect(const QPoint& point,const Qt::KeyboardModifiers& mod);
    void drawTria(const QPoint& point,const Qt::KeyboardModifiers& mod);
    void drawStar(const QPoint& point,const Qt::KeyboardModifiers& mod);
    void drawFive(const QPoint& point,const Qt::KeyboardModifiers& mod);
    void drawElli(const QPoint& point,const Qt::KeyboardModifiers& mod);
    void drawCurve(const QPoint& point);
    void clearCurve(const QPoint& point);
    void drawFrame(const QPoint& point);
    void colorFromPoint(const QPoint& point);
    void drawLom();
    void drawPoly(const QPoint& point);
    void scaleFrame(const QPoint& point);
    void moveFrame(const QPoint& point);
    void rotateFrame(int delta);
    void initFrame(const QPoint& point);
    void initScale(const QPoint& point);
    void initRotate();
    void resetFrame(const QPoint& point);
    void endScale();
    void inBackup(QImage &img);
protected:
    void paintEvent(QPaintEvent* pe);
    void mousePressEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
private slots:
    void backupNext();
    void backupPrev();
    void changeTool(int num);
    void changeColor(bool s,QColor col);
    void changePenWidth(int i);
    void changeLasWidth(int i);
    void changeLine(int i);
    void setImage();
    void addImage();
    void resizeSheet(QSize s);
    void saveas();
    void save();
    void dif();
    void getAnti();
    void getFillSens(int s);
signals:
    void getDif(bool);
    void sendColor(QColor);
    void sizeChanged(QSize);
    void getScroll(int dx,int dy);
};

#endif // PAINT_H
