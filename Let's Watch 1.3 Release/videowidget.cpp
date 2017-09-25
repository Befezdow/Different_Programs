#include "videowidget.h"
#include "videomenu.h"
#include "app.h"
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QList>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

VideoWidget::VideoWidget(QWidget* parent):QVideoWidget(parent)
{
    player=new QMediaPlayer;
    player->setVideoOutput(this);
    menu=new VideoMenu(this);
    FSState=false;
    connect(this,SIGNAL(fullScreenChanged(bool)),SLOT(FS(bool)));
    connect(player,SIGNAL(mutedChanged(bool)),this,SIGNAL(sound(bool)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SIGNAL(durChange(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SIGNAL(posChange(qint64)));
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SIGNAL(stateChange(QMediaPlayer::State)));
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SIGNAL(mediaChange(QMediaPlayer::MediaStatus)));
    connect(player,SIGNAL(volumeChanged(int)),this,SIGNAL(volumeChange(int)));
    this->setMinimumSize(402,300);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    int x=QApplication::desktop()->screenGeometry().width()/2-menu->width()/2;
    int y=QApplication::desktop()->screenGeometry().height()-menu->height();
    anim1=new QPropertyAnimation(menu,"pos");
    anim1->setDuration(100);
    anim1->setStartValue(QPoint(x,y+menu->height()));
    anim1->setEndValue(QPoint(x,y));
    anim1->setEasingCurve(QEasingCurve::OutQuad);
    anim2=new QSequentialAnimationGroup;
    QPropertyAnimation* anim21=new QPropertyAnimation(menu,"pos");
    anim21->setDuration(100);
    anim21->setStartValue(QPoint(x,y));
    anim21->setEndValue(QPoint(x,y+menu->height()));
    anim21->setEasingCurve(QEasingCurve::OutQuad);
    QPropertyAnimation* anim22=new QPropertyAnimation(menu,"visible");
    anim22->setDuration(1);
    anim22->setEndValue(false);
    anim2->addAnimation(anim21);
    anim2->addAnimation(anim22);
    this->loadSettings();
    this->setFocusPolicy(Qt::StrongFocus);
    menu->setFocusPolicy(Qt::NoFocus);
    this->setAcceptDrops(true);
    timerID=QObject::startTimer(300000);
}

VideoWidget::~VideoWidget()
{
    this->saveSettings();
    delete menu;
    delete player;
    delete anim1;
    delete anim2;
}

void VideoWidget::saveSettings()
{
    QSettings* settings=App::theApp()->settings();
    settings->beginGroup("/VideoWidget");
    settings->setValue("/Volume",this->player->volume());
    if (!filePath.isEmpty())
        settings->setValue("/FilePath",this->filePath);
    settings->endGroup();
}

void VideoWidget::loadSettings()
{
    QSettings* settings=App::theApp()->settings();
    settings->beginGroup("/VideoWidget");
    this->setVolume(settings->value("/Volume",50).toInt());
    filePath=settings->value("/FilePath",QString()).toString();
    settings->endGroup();
}

void VideoWidget::stopPlayer()
{
    player->stop();
}

void VideoWidget::setFullScr()
{
    bool a=this->isFullScreen();
    this->setFullScreen(!a);
}

void VideoWidget::setSound()
{
    bool a=player->isMuted();
    player->setMuted(!a);
}

void VideoWidget::setVolume(int i)
{
    player->setVolume(i);
}

void VideoWidget::FS(bool a)
{
    FSState=a;
    this->setMouseTracking(a);
    if (a)
        menu->show();
    else
        menu->hide();
}

void VideoWidget::openFile()
{
    QString path;
    if (filePath.isEmpty())
        path=QDir::rootPath();
    else
        path=filePath;
    QString fileName=QFileDialog::getOpenFileName(this,"Открыть файл",path,"AVI (*.avi);;MKV (*.mkv);;MP4 (*.mp4)");
    if (!fileName.isNull())
        filePath=fileName.left(fileName.lastIndexOf("/"));
    if (!fileName.isEmpty() && !fileName.isNull())
    {
        if (player->state()==QMediaPlayer::PlayingState)
            player->stop();
        if (player->currentMedia().isNull())
            emit activateMenu(true);
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->play();
    }
}

void VideoWidget::setMediaPos(int n)
{
    player->setPosition(n);
}

void VideoWidget::pausePlay()
{
    switch (player->state())
    {
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    default:
        player->play();
        break;
    }
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (FSState && !menuState)
    {
        int x=QApplication::desktop()->screenGeometry().width()/2-menu->width()/2;
        int y=QApplication::desktop()->screenGeometry().height()-menu->height();
        QRect rect(QPoint(x,y),menu->rect().size());
        if (rect.contains(event->pos()))
        {
            menu->show();
            anim1->start();
            menuState=true;
        }
    }
    if (FSState && menuState)
    {
        int x=QApplication::desktop()->screenGeometry().width()/2-menu->width()/2;
        int y=QApplication::desktop()->screenGeometry().height()-menu->height();
        QRect rect(QPoint(x,y),menu->rect().size());
        if (!rect.contains(event->pos()))
        {
            anim2->start();
            menuState=false;
        }
    }
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent*)
{
    this->setFullScr();
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Space)
        this->pausePlay();
    if (event->key()==Qt::Key_Up)
        this->setVolume(this->player->volume()+5);
    if (event->key()==Qt::Key_Down)
        this->setVolume(this->player->volume()-5);
    if (event->key()==Qt::Key_Left)
        this->setMediaPos(this->player->position()-5000);
    if (event->key()==Qt::Key_Right)
        this->setMediaPos(this->player->position()+5000);
    QVideoWidget::keyPressEvent(event);
}

void VideoWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        int i=0;
        bool q=false;
        QList<QUrl> list=event->mimeData()->urls();
        while (i<list.size())
        {
            QString str=list.at(i).toString();
            str=str.right(3).toLower();
            if (str=="avi" || str=="mp4" || str=="mkv")
            {
                q=true;
                break;
            }
            i++;
        }
        if (q)
            event->acceptProposedAction();
    }
}

void VideoWidget::dropEvent(QDropEvent *event)
{
    QList<QUrl> list=event->mimeData()->urls();
    if (!list.isEmpty())
    {
        int i=0;
        QString str;
        QUrl url;
        while (i<list.size())
        {
            url=list.at(i);
            str=url.toString();
            QString s=str.right(3).toLower();
            if (s=="avi" || s=="mp4" || s=="mkv")
                break;
            i++;
        }
        str=str.left(str.lastIndexOf("/"));
        str.remove(0,8);
        filePath=str;
        if (player->state()==QMediaPlayer::PlayingState)
            player->stop();
        if (player->currentMedia().isNull())
            emit activateMenu(true);
        player->setMedia(url);
        player->play();
    }
}

void VideoWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId()==timerID)
    {
        if (FSState && (this->player->state()==QMediaPlayer::PlayingState))
        {
            QPoint point=QCursor::pos();
            QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,point,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
            QApplication::sendEvent(this,press);
            QMouseEvent* release=new QMouseEvent(QEvent::MouseButtonRelease,point,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
            QApplication::sendEvent(this,release);
        }
    }
}
