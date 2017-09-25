#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
class VideoMenu;
class QPropertyAnimation;
class QSequentialAnimationGroup;

class VideoWidget:public QVideoWidget
{
    Q_OBJECT
    bool menuState;
    bool FSState;
    VideoMenu* menu;
    QMediaPlayer* player;
    QPropertyAnimation* anim1;
    QSequentialAnimationGroup* anim2;
    QString filePath;
    int timerID;

    void loadSettings();
    void saveSettings();
public:
    VideoWidget(QWidget* parent=Q_NULLPTR);
    ~VideoWidget();
signals:
    void activateMenu(bool);
    void sound(bool);
    void durChange(qint64);
    void posChange(qint64);
    void stateChange(QMediaPlayer::State);
    void mediaChange(QMediaPlayer::MediaStatus);
    void volumeChange(int);
private slots:
    void FS(bool a);
    void openFile();
    void setMediaPos(int n);
    void pausePlay();
    void stopPlayer();
    void setFullScr();
    void setSound();
    void setVolume(int i);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // VIDEOWIDGET_H
