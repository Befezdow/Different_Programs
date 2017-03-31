#include "statebutton.h"
#include <QStateMachine>
#include <QState>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>

StateButton::StateButton(QWidget* parent):QWidget(parent)
{
    QPalette pal;
    pal.setColor(this->backgroundRole(),Qt::gray);
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    this->setFixedSize(60,20);
    sm=new QStateMachine;
    on=new QState(sm);
    off=new QState(sm);
    button=new QPushButton(this);
    button->setFixedSize(30,20);
    on->assignProperty(button,"pos",QPoint(0,0));
    off->assignProperty(button,"pos",QPoint(30,0));
    transOn1=on->addTransition(this,SIGNAL(click()),off);
    transOff1=off->addTransition(this,SIGNAL(click()),on);
    anim=new QPropertyAnimation(button,"pos");
    transOn1->addAnimation(anim);
    transOff1->addAnimation(anim);
    sm->setInitialState(on);
    sm->start();
    QObject::connect(button,SIGNAL(clicked(bool)),this,SIGNAL(click()));
}

StateButton::~StateButton()
{
    QObject::disconnect(button,SIGNAL(clicked(bool)),this,SIGNAL(click()));
    delete anim;
    delete button;
    delete transOn1;
    delete transOff1;
    delete on;
    delete off;
    delete sm;
}

void StateButton::mouseReleaseEvent(QMouseEvent*)
{
    emit click();
}
