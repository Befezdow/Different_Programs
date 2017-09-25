#ifndef STATEBUTTON_H
#define STATEBUTTON_H

#include <QWidget>
class QPushButton;
class QStateMachine;
class QState;
class QSignalTransition;
class QPropertyAnimation;
class QMouseEvent;

class StateButton:public QWidget
{
    Q_OBJECT
    QPushButton* button;
    QStateMachine* sm;
    QState* on;
    QState* off;
    QSignalTransition* transOn1;
    QSignalTransition* transOff1;
    QPropertyAnimation* anim;
public:
    StateButton(QWidget* parent=0);
    ~StateButton();
protected:
    void mouseReleaseEvent(QMouseEvent*);
signals:
    void click();
};

#endif // STATEBUTTON_H
