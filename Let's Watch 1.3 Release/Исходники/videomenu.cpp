#include "videomenu.h"
#include "videowidget.h"
#include "app.h"
#include "slider.h"
#include <QTime>
#include <QPushButton>
#include <QStyle>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

QString VideoMenu::msecToString(qint64 n)
{
    int hours = n/(60*60*1000);
    int minutes = (n%(60*60*1000))/(60*1000);
    int seconds = (n%(60*1000))/1000;
    return QTime(hours,minutes,seconds).toString("hh:mm:ss");
}

VideoMenu::VideoMenu(VideoWidget* video,QWidget* parent):QWidget(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    openButton=new QPushButton;
    openButton->setIcon(QIcon(":/res/open.png"));
    openButton->setFixedSize(30,30);
    playButton=new QPushButton;
    playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPause));
    playButton->setFixedSize(40,40);
    stopButton=new QPushButton;
    stopButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setFixedSize(30,30);
    FSButton=new QPushButton;
    FSButton->setIcon(QIcon(":/res/fullscreen.png"));
    FSButton->setFixedSize(30,30);
    soundButton=new QPushButton;
    soundButton->setIcon(QIcon(":/res/sound.png"));
    soundButton->setFixedSize(30,30);
    volume=new Slider(Qt::Horizontal);
    volume->setRange(0,100);
    volume->setValue(App::theApp()->settings()->value("/VideoWidget/Volume",50).toInt());
    volume->setFixedWidth(70);
    position=new Slider(Qt::Horizontal);
    currentTime=new QLabel("MADE BY");
    remainTime=new QLabel("BEFEZDOW");
    hlay=new QHBoxLayout;
    vlay=new QVBoxLayout;
    hlay->addWidget(currentTime,0,Qt::AlignLeft);
    hlay->addSpacing(10);
    hlay->addWidget(openButton,0,Qt::AlignRight);
    hlay->addWidget(FSButton,0,Qt::AlignRight);
    hlay->addWidget(stopButton,0,Qt::AlignRight);
    hlay->addWidget(playButton,0,Qt::AlignHCenter);
    hlay->addWidget(soundButton,0,Qt::AlignLeft);
    hlay->addWidget(volume,0,Qt::AlignLeft);
    hlay->addSpacing(10);
    hlay->addWidget(remainTime,0,Qt::AlignRight);
    vlay->addWidget(position);
    vlay->addLayout(hlay);
    this->setLayout(vlay);
    playButton->setEnabled(false);
    stopButton->setEnabled(false);
    if (video)
    {
        connect(video,SIGNAL(activateMenu(bool)),this,SLOT(enableButton(bool)));
        connect(playButton,SIGNAL(clicked(bool)),video,SLOT(pausePlay()));
        connect(FSButton,SIGNAL(clicked(bool)),video,SLOT(setFullScr()));
        connect(openButton,SIGNAL(clicked(bool)),video,SLOT(openFile()));
        connect(stopButton,SIGNAL(clicked(bool)),video,SLOT(stopPlayer()));
        connect(soundButton,SIGNAL(clicked(bool)),video,SLOT(setSound()));
        connect(volume,SIGNAL(valueChanged(int)),video,SLOT(setVolume(int)));
        connect(position,SIGNAL(sliderMoved(int)),video,SLOT(setMediaPos(int)));
        connect(video,SIGNAL(sound(bool)),this,SLOT(soundChanged(bool)));
        connect(video,SIGNAL(durChange(qint64)),this,SLOT(setDuration(qint64)));
        connect(video,SIGNAL(posChange(qint64)),this,SLOT(setPos(qint64)));
        connect(video,SIGNAL(stateChange(QMediaPlayer::State)),this,SLOT(statusChanged(QMediaPlayer::State)));
        connect(video,SIGNAL(mediaChange(QMediaPlayer::MediaStatus)),this,SLOT(reset(QMediaPlayer::MediaStatus)));
        connect(video,SIGNAL(volumeChange(int)),this->volume,SLOT(setValue(int)));
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(435,87);
    FSButton->setFocusPolicy(Qt::NoFocus);
    openButton->setFocusPolicy(Qt::NoFocus);
    volume->setFocusPolicy(Qt::NoFocus);
    position->setFocusPolicy(Qt::NoFocus);
    playButton->setFocusPolicy(Qt::NoFocus);
    stopButton->setFocusPolicy(Qt::NoFocus);
    soundButton->setFocusPolicy(Qt::NoFocus);
    QFont font=currentTime->font();
    font.setPointSize(13);
    font.setFamily("Digital-7");
    currentTime->setFont(font);
    remainTime->setFont(font);
    QPalette pal;
    pal.setBrush(QPalette::Background,QColor(231,184,38));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
}

void VideoMenu::enableButton(bool b)
{
    playButton->setEnabled(b);
    stopButton->setEnabled(b);
}

void VideoMenu::setDuration(qint64 n)
{
    position->setRange(0,n);
    currentTime->setText(this->msecToString(0));
    remainTime->setText(this->msecToString(n));
}

void VideoMenu::setPos(qint64 n)
{
    position->setValue(n);
    int max=position->maximum();
    currentTime->setText(this->msecToString(n));
    remainTime->setText(this->msecToString(max-n));
}

void VideoMenu::reset(QMediaPlayer::MediaStatus status)
{
    if (status==QMediaPlayer::EndOfMedia)
    {
        currentTime->setText(msecToString(0));
        remainTime->setText(msecToString(position->maximum()));
        position->setValue(0);
    }
}

void VideoMenu::statusChanged(QMediaPlayer::State state)
{
    switch (state)
    {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoMenu::soundChanged(bool a)
{
    if (a)
        this->soundButton->setIcon(QIcon(":/res/soundoff.png"));
    else
        this->soundButton->setIcon(QIcon(":/res/sound.png"));
}
