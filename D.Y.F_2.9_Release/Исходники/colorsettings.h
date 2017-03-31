#ifndef COLORSETTINGS_H
#define COLORSETTINGS_H

#include <QWidget>
#include "palette.h"
#include "statebutton.h"
#include "gradient.h"
class QPushButton;
class QLabel;
class QColor;
class QTabWidget;
class QScrollArea;
class QHBoxLayout;
class QVBoxLayout;
class QPixMap;
class QGroupBox;

class ColorSettings:public QWidget
{
    Q_OBJECT
    QPushButton* deepSettings;
    StateButton* changeButton;
    QPushButton* noColorButton;
    QPushButton* usePalButton;
    QLabel* penLabel;
    QLabel* brushLabel;
    QLabel* penLabelName;
    QLabel* brushLabelName;
    QColor penColor;
    QColor brushColor;
    QTabWidget* tab;
    QScrollArea* scroll;
    Palette* pal;
    Palette* use;
    QVBoxLayout* vlay;
    QHBoxLayout* hlay;
    QVBoxLayout* lay1;
    QVBoxLayout* lay2;
    QPixmap* pix;
    Gradient* grad;
    QGroupBox* gb;
    bool state;
public:
    ColorSettings(QWidget* parent=0);
    ~ColorSettings();
private slots:
    void changeState();
    void setColor(const QColor& col);
    void setNoColor();
    void loadPalette();
signals:
    void sendColor(bool,QColor);
};

#endif // COLORSETTINGS_H
