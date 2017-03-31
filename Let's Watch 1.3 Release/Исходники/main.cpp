#include "videomenu.h"
#include "videowidget.h"
#include "savewidget.h"
#include <QFile>
#include <QVBoxLayout>


int main(int argc, char *argv[])
{
    App a(argc, argv,"Befezdow co.","WatchNLearn");
    QFile file(":/res/style.qss");
    file.open(QFile::ReadOnly);
    QString str=file.readAll();
    a.setStyleSheet(str);

    SaveWidget wgt;
    QPalette pal1;
    pal1.setBrush(QPalette::Background,QColor(231,184,38));
    wgt.setPalette(pal1);

    VideoWidget video;
    QPalette pal2;
    pal2.setBrush(QPalette::Background,QColor(130,212,255));
    video.setPalette(pal2);
    video.setAutoFillBackground(true);

    VideoMenu menu(&video);
    menu.setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *lay=new QVBoxLayout;
    lay->addWidget(&video);
    lay->addWidget(&menu,0,Qt::AlignHCenter | Qt::AlignBottom);
    lay->setMargin(1);
    lay->setSpacing(0);
    wgt.setLayout(lay);

    wgt.show();
    return a.exec();
}
