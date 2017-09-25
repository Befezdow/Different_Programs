#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class SettingsWidget:public QWidget
{
    Q_OBJECT
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl;
    QCheckBox* chb;
    QSpinBox* spb;
    QHBoxLayout* lay1;
    QHBoxLayout* lay2;
    QVBoxLayout* lay;
    QPushButton* pb;
public:
    SettingsWidget(QWidget* parent=0):QWidget(parent)
    {
        lbl1=new QLabel("Сглаживание:");
        lbl2=new QLabel("Чувствительность заливки:");
        chb=new QCheckBox;
        chb->setCheckState(Qt::Unchecked);
        spb=new QSpinBox;
        spb->setMinimum(0);
        spb->setMaximum(255);
        spb->setValue(0);
        lbl=new QLabel("Функция сглаживания добаляет пиксели по краям линии,\n"
                       " делая ее более плавной. Однако она немного конфликтует\n"
                       " с заливкой, поэтому её рекомендуется использовать для\n"
                       "рисовки уже на готовом фоне.\n"
                       "Чувствительность заливки определяет диапазон цветов,\n"
                       "которые должны быть заменены. Чем больше значение,\n"
                       "тем шире диапазон.");
        QFont font = lbl->font();
        font.setPointSize(10);
        lbl->setFont(font);
        font.setPointSize(12);
        lbl1->setFont(font);
        lbl2->setFont(font);
        lbl->setAlignment(Qt::AlignCenter);
        lay1=new QHBoxLayout;
        lay2=new QHBoxLayout;
        lay=new QVBoxLayout;
        pb=new QPushButton("OK");
        lay1->addWidget(lbl1);
        lay1->addWidget(chb);
        lay1->setAlignment(Qt::AlignHCenter);
        lay2->addWidget(lbl2);
        lay2->addWidget(spb);
        lay2->setAlignment(Qt::AlignHCenter);
        lay->addLayout(lay1);
        lay->addLayout(lay2);
        lay->addWidget(lbl);
        lay->addWidget(pb);
        lay->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->setLayout(lay);
        QPalette pal;
        pal.setBrush(this->backgroundRole(),QColor(157,255,108));
        this->setPalette(pal);
        this->setFixedSize(this->minimumSize());
        this->setWindowTitle("Параметры");
        QObject::connect(chb,SIGNAL(clicked(bool)),this,SIGNAL(getAnti()));
        QObject::connect(spb,SIGNAL(valueChanged(int)),this,SIGNAL(getFill(int)));
        QObject::connect(pb,SIGNAL(clicked(bool)),this,SLOT(hide()));
    }
    ~SettingsWidget()
    {
        QObject::disconnect(chb,SIGNAL(clicked(bool)),this,SIGNAL(getAnti()));
        QObject::disconnect(spb,SIGNAL(valueChanged(int)),this,SIGNAL(getFill(int)));
        delete lbl1;
        delete lbl2;
        delete lbl;
        delete chb;
        delete spb;
        delete lay1;
        delete lay2;
        delete lay;
    }

signals:
    void getAnti();
    void getFill(int);
};

#endif // SETTINGSWIDGET_H
