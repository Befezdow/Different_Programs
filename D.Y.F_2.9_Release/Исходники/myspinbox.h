#ifndef MYSPINBOX_H
#define MYSPINBOX_H

#include <QSpinBox>
#include <QColor>

class MySpinBox:public QSpinBox
{
    Q_OBJECT
public:
    MySpinBox(QWidget* parent=0):QSpinBox(parent) {}
private slots:
    void setRed(const QColor& col)
    {
        this->setValue(col.red());
        emit valueChanged(col.red());
    }
    void setGreen(const QColor& col)
    {
        this->setValue(col.green());
        emit valueChanged(col.green());
    }
    void setBlue(const QColor& col)
    {
        this->setValue(col.blue());
        emit valueChanged(col.blue());
    }
    void setAlpha(const QColor& col)
    {
        this->setValue(col.alpha());
        emit valueChanged(col.alpha());
    }
};

#endif // MYSPINBOX_H
