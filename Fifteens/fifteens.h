#ifndef FIFTEENS_H
#define FIFTEENS_H

#include <QtWidgets>

class Fifteens: public QWidget
{
    Q_OBJECT
    QGridLayout* lay;
    QPushButton** buttons;
    unsigned char* numbers;
    unsigned char zeroPos;

    unsigned char* win1;
    unsigned char* win2;

    const int fieldWidth;
    const int fieldHeight;

public:
    enum {Up, Down, Left, Right};

    Fifteens(int width,int height,QWidget* parent=Q_NULLPTR);
    ~Fifteens();

    bool move(int direction);
    bool checkWin();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // FIFTEENS_H
