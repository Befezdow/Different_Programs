#ifndef VIDEOMENU_H
#define VIDEOMENU_H

#include <QWidget>
#include <QMediaPlayer>
class Slider;
class VideoWidget;
class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class VideoMenu: public QWidget
{
    Q_OBJECT
    QPushButton* openButton;
    QPushButton* playButton;
    QPushButton* stopButton;
    QPushButton* FSButton;
    QPushButton* soundButton;
    Slider* volume;
    Slider* position;
    QLabel* currentTime;
    QLabel* remainTime;
    QHBoxLayout* hlay;
    QVBoxLayout* vlay;

    QString msecToString(qint64 n);
public:
    VideoMenu(VideoWidget* video=Q_NULLPTR, QWidget* parent=Q_NULLPTR);
private slots:
    void enableButton(bool b);
    void setDuration(qint64 n);
    void setPos(qint64 n);
    void reset(QMediaPlayer::MediaStatus status);
    void statusChanged(QMediaPlayer::State state);
    void soundChanged(bool a);
};

#endif // VIDEOMENU_H
