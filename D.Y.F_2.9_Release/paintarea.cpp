#include "paintarea.h"
#include "myscrollarea.h"
#include <QPainter>
#include <QString>
#include <QQueue>
#include <QFileDialog>
#include <QDir>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QCursor>

PaintArea::PaintArea(QWidget *parent):QWidget(parent)
{
    this->setMinimumSize(1,1);
    this->resize(500,500);
    image=new QImage(500,500,QImage::Format_ARGB32_Premultiplied);
    image->fill(Qt::white);
    QPainter painter(image);
    QImage img("/home/befezdow/Изображения/Krabik.jpg");
    painter.drawImage(50,50,img);
    painter.end();
    saveState=false;
    state=1;
    rotState=1;
    rotDelta=0;
    tec=ram;
    mouseState=0;
    curBackCache=-1;
    curPen=QPen(Qt::black,6,Qt::SolidLine);
    curPen.setCapStyle(Qt::RoundCap);
    curLas=QPen(Qt::white,10,Qt::SolidLine);
    curLas.setCapStyle(Qt::RoundCap);
    curBrush=QBrush(Qt::white);
    this->inBackup(*image);
    exitCache=*image;
    anti=false;
    fillSens=0;
    this->setCursor(QCursor(QPixmap(":/resources/kursor.png")));
    cacheCursor=this->cursor();
}

PaintArea::~PaintArea()
{
    delete image;
}

void PaintArea::dif()
{
    this->resetFrame(QPoint(0,0));
    if (exitCache==*image)
        emit getDif(false);
    else
        emit getDif(true);
}

void PaintArea::getAnti()
{
    anti=!anti;
}

void PaintArea::getFillSens(int s)
{
    fillSens=s;
}

void PaintArea::changeTool(int num)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.drawImage(rect,cache);
    painter.end();
    if (!rect.isEmpty())
        this->inBackup(*image);
    cache=QImage();
    this->update();
    state=1;
    rotState=1;
    rotDelta=0;
    beg=QPoint(0,0);
    globalCache=*image;
    rect=QRect();
    tec=curShape;
    rotCache=QImage();
    rotRect=QRect();
    saveState=false;
    tec=static_cast<tool>(num);
}

void PaintArea::changeColor(bool s,QColor col)
{
    if (s)
    {
        if (col==QColor(0,0,0,0))
            curPen=QPen(Qt::NoPen);
        else
        {
            curPen=QPen(col,curPen.width(),Qt::SolidLine);
            curPen.setCapStyle(Qt::RoundCap);
            curPen.setJoinStyle(Qt::RoundJoin);
        }
    }
    else
    {
        if (col==QColor(0,0,0,0))
            curBrush=QBrush(Qt::NoBrush);
        else
            curBrush=QBrush(col);
    }
}

void PaintArea::changePenWidth(int i)
{
    curPen.setWidth(i);
}

void PaintArea::changeLasWidth(int i)
{
    curLas.setWidth(i);
}

void PaintArea::changeLine(int i)
{
    switch (i)
    {
    case 0:
        curPen.setStyle(Qt::SolidLine);
        break;
    case 1:
        curPen.setStyle(Qt::DashLine);
        break;
    case 2:
        curPen.setStyle(Qt::DotLine);
        break;
    case 3:
        curPen.setStyle(Qt::DashDotLine);
        break;
    case 4:
        curPen.setStyle(Qt::DashDotDotLine);
        break;
    default:
        return;
    }
}

void PaintArea::setImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл",QDir::rootPath(),"PNG (*.png);;JPEG (*.jpg;*jpeg);;GIF (*.gif);;BMP (*.bmp)");
    if(!fileName.isEmpty())
    {
        QImage img;
        if (!img.load(fileName))
        {
            QMessageBox::critical(this,"Ошибка", "Невозможно открыть изображение");
            return;
        }
        delete image;
        image=new QImage(img.size(),QImage::Format_ARGB32_Premultiplied);
        QPainter painter(image);
        painter.drawImage(0,0,img);
        this->resize(image->size());
        state=1;
        rotState=1;
        rotDelta=0;
        emit sizeChanged(image->size());
        path=fileName;
        this->update();
        exitCache=*image;
        this->inBackup(*image);
        globalCache=*image;
    }
}

void PaintArea::addImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл",QDir::rootPath(),"PNG (*.png);;JPEG (*.jpg;*jpeg);;GIF (*.gif);;BMP (*.bmp)");
    if(!fileName.isEmpty())
    {
        this->resetFrame(QPoint(0,0));
        if (!cache.load(fileName))
        {
            QMessageBox::critical(this,"Ошибка", "Невозможно открыть изображение");
            return;
        }
        rect=QRect(0,0,cache.width(),cache.height());
        beg=QPoint(0,0);
        globalCache=*image;
        QPainter painter(image);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        painter.drawImage(rect.topLeft(),cache);
        painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
        painter.end();
        state=2;
        tec=ram;
        this->update();
    }
}

void PaintArea::resizeSheet(QSize s)
{
    this->resize(s);
    QImage* img=new QImage(s,QImage::Format_ARGB32_Premultiplied);
    img->fill(Qt::white);
    QPainter painter(img);
    painter.drawImage(0,0,*image);
    painter.end();
    delete image;
    image=img;
    QImage globalImg(s,QImage::Format_ARGB32_Premultiplied);
    globalImg.fill(Qt::white);
    painter.begin(&globalImg);
    painter.drawImage(0,0,globalCache);
    painter.end();
    globalCache=globalImg;
    this->update();
    emit sizeChanged(image->size());
}
void PaintArea::saveas()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл",QDir::rootPath(),"PNG (*.png);;JPEG (*.jpg;*jpeg);;BMP (*.bmp)");
    if (!fileName.isEmpty())
    {
        this->resetFrame(QPoint(0,0));
        if (!image->save(fileName))
        {
            QMessageBox::critical(this,"Ошибка", "Не удалось сохранить изображение");
            return;
        }
        exitCache=*image;
    }
}

void PaintArea::save()
{
    if (path.isEmpty())
        this->saveas();
    else
    {
        this->resetFrame(QPoint(0,0));
        if (!image->save(path))
        {
            QMessageBox::critical(this,"Ошибка", "Не удалось сохранить изображение");
            return;
        }
        exitCache=*image;
    }
}

void PaintArea::inBackup(QImage &img)
{
    if (backup.size()>=10)
        backup.pop_front();
    if (backup.size()-1>curBackCache && curBackCache!=-1)
    {
        while (backup.size()-1!=curBackCache)
            backup.pop();
    }
    curBackCache=-1;
    backup.push(img);
}

void PaintArea::backupNext()
{
    if (backup.isEmpty() || curBackCache==backup.size()-1 || curBackCache==-1)
        return;
    curBackCache++;
    globalCache=backup.at(curBackCache);
    *image=globalCache;
    rect=QRect();
    cache=QImage();
    this->update();
}

void PaintArea::backupPrev()
{
    if (backup.size()==1 || curBackCache==0)
        return;
    if (curBackCache==-1)
        curBackCache=backup.size()-2;
    else
        curBackCache--;
    globalCache=backup.at(curBackCache);
    *image=globalCache;
    rect=QRect();
    cache=QImage();
    this->update();
}

void PaintArea::fill(const QColor& color, const QPoint& point)
{
    int i=fillSens;
    QRgb penColor=color.rgba();
    QRgb zamColor=image->pixel(point);
    if (penColor==zamColor)
        return;
    cacheCursor=this->cursor();
    this->setCursor(Qt::WaitCursor);
    this->inBackup(globalCache);//в список отмены
    image->setPixel(point,penColor);
    QPoint* start=new QPoint(point);
    QQueue<QPoint*> que;
    que.enqueue(start);
    QPoint cachePos;
    QRgb cacheColor;
    QPoint* p;
    while (!que.isEmpty())
    {
        p=que.dequeue();
        cachePos=QPoint(p->x(),p->y()-1);
        if (image->rect().contains(cachePos))
        {
            cacheColor=image->pixel(cachePos);
            if (qRed(cacheColor)<=qRed(zamColor)+i && qRed(cacheColor)>=qRed(zamColor)-i
                    && qGreen(cacheColor)<=qGreen(zamColor)+i && qGreen(cacheColor)>=qGreen(zamColor)-i
                    && qBlue(cacheColor)<=qBlue(zamColor)+i && qBlue(cacheColor)>=qBlue(zamColor)-i
                    && qAlpha(cacheColor)<=qAlpha(zamColor)+i && qAlpha(cacheColor)>=qAlpha(zamColor)-i
                    && cacheColor!=penColor)
            {
                image->setPixel(cachePos,penColor);
                que.enqueue(new QPoint(cachePos));

            }
        }
        cachePos=QPoint(p->x()+1,p->y());
        if (image->rect().contains(cachePos))
        {
            cacheColor=image->pixel(cachePos);
            if (qRed(cacheColor)<=qRed(zamColor)+i && qRed(cacheColor)>=qRed(zamColor)-i
                    && qGreen(cacheColor)<=qGreen(zamColor)+i && qGreen(cacheColor)>=qGreen(zamColor)-i
                    && qBlue(cacheColor)<=qBlue(zamColor)+i && qBlue(cacheColor)>=qBlue(zamColor)-i
                    && qAlpha(cacheColor)<=qAlpha(zamColor)+i && qAlpha(cacheColor)>=qAlpha(zamColor)-i
                    && cacheColor!=penColor)
            {
                image->setPixel(cachePos,penColor);
                que.enqueue(new QPoint(cachePos));
            }
        }
        cachePos=QPoint(p->x(),p->y()+1);
        if (image->rect().contains(cachePos))
        {
            cacheColor=image->pixel(cachePos);
            if (qRed(cacheColor)<=qRed(zamColor)+i && qRed(cacheColor)>=qRed(zamColor)-i
                    && qGreen(cacheColor)<=qGreen(zamColor)+i && qGreen(cacheColor)>=qGreen(zamColor)-i
                    && qBlue(cacheColor)<=qBlue(zamColor)+i && qBlue(cacheColor)>=qBlue(zamColor)-i
                    && qAlpha(cacheColor)<=qAlpha(zamColor)+i && qAlpha(cacheColor)>=qAlpha(zamColor)-i
                    && cacheColor!=penColor)
            {
                image->setPixel(cachePos,penColor);
                que.enqueue(new QPoint(cachePos));
            }
        }
        cachePos=QPoint(p->x()-1,p->y());
        if (image->rect().contains(cachePos))
        {
            cacheColor=image->pixel(cachePos);
            if (qRed(cacheColor)<=qRed(zamColor)+i && qRed(cacheColor)>=qRed(zamColor)-i
                    && qGreen(cacheColor)<=qGreen(zamColor)+i && qGreen(cacheColor)>=qGreen(zamColor)-i
                    && qBlue(cacheColor)<=qBlue(zamColor)+i && qBlue(cacheColor)>=qBlue(zamColor)-i
                    && qAlpha(cacheColor)<=qAlpha(zamColor)+i && qAlpha(cacheColor)>=qAlpha(zamColor)-i
                    && cacheColor!=penColor)
            {
                image->setPixel(cachePos,penColor);
                que.enqueue(new QPoint(cachePos));
            }
        }
        delete p;
    }
    globalCache=*image;
    this->setCursor(cacheCursor);
    this->update();
}

void PaintArea::drawCurve(const QPoint &point)
{
    QPainter painter(image);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.drawLine(beg,point);
    painter.end();
    beg=point;
    globalCache=*image;
    this->update();
}

void PaintArea::clearCurve(const QPoint &point)
{
    QPainter painter(image);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curLas);
    painter.drawLine(beg,point);
    painter.end();
    beg=point;
    globalCache=*image;
    this->update();
}

void PaintArea::drawFrame(const QPoint &point)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            rect=QRect(beg,point);
            clearRect=QRect(beg,point);
        }
        else
        {
            rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
            clearRect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
            clearRect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
        }
        else
        {
            rect=QRect(point,beg);
            clearRect=QRect(point,beg);
        }
    }
    cache=image->copy(rect);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::scaleFrame(const QPoint& point)
{
    if (cache.isNull())
        return;
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    QPoint ch=point-beg;
    br=br+ch;
    if (br.x()>=tl.x())
    {
        if (br.y()>=tl.y())
        {
            rect=QRect(tl,br);
            scaleState=1;
            painter.drawImage(rect,cache);
        }
        else
        {
            rect=QRect(QPoint(tl.x(),br.y()),QPoint(br.x(),tl.y()));
            painter.drawImage(rect,cache.mirrored());
            scaleState=2;
        }
    }
    else
    {
        if (br.y()>=tl.y())
        {
            rect=QRect(QPoint(br.x(),tl.y()),QPoint(tl.x(),br.y()));
            scaleState=3;
            painter.drawImage(rect,cache.mirrored(true,false));
        }
        else
        {
            rect=QRect(br,tl);
            painter.drawImage(rect,cache.mirrored(true));
            scaleState=4;
        }
    }
    beg=point;
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::initFrame(const QPoint &point)
{
    beg=point;
    globalCache=*image;
}

void PaintArea::resetFrame(const QPoint& point)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.drawImage(rect,cache);
    painter.end();
    cache=QImage();
    this->update();
    state=1;
    rotState=1;
    rotDelta=0;
    beg=point;
    globalCache=*image;
    rect=QRect();
    tec=curShape;
    rotCache=QImage();
    rotRect=QRect();
    saveState=false;
}

void PaintArea::initScale(const QPoint& point)
{
    if (globalCache.isNull())
        return;
    beg=point;
    tl=rect.topLeft();
    br=rect.bottomRight();
    rotDelta=0;
}

void PaintArea::moveFrame(const QPoint& point)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    QPoint p=point-beg;
    painter.drawImage(QRect(rect.topLeft()+p,rect.size()),cache);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawRect(QRect(rect.topLeft()+p,QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
    rect=QRect(rect.topLeft()+p,rect.size());
    beg=beg+p;
}

void PaintArea::endScale()
{
    if (cache.isNull())
        return;
    switch (scaleState)
    {
    case 1:
        break;
    case 2:
        cache=cache.mirrored();
        break;
    case 3:
        cache=cache.mirrored(true,false);
        break;
    case 4:
        cache=cache.mirrored(true);
    default:
        break;
    }
    cache=cache.scaled(rect.size());
    if (rotState==2)
    {
        int rad=0;
        int crad;
        for (int i=0;i<cache.width();i++)
        {
            for (int j=0;j<cache.height();j++)
            {
                QRgb r=cache.pixel(i,j);
                QColor rgb;
                rgb.setRgba(r);
                if (rgb.alpha()==0)
                    continue;
                else
                {
                    crad=sqrt(pow(i-cache.rect().center().x(),2)+pow(j-cache.rect().center().y(),2));
                    if (rad<crad)
                        rad=crad;
                }
            }
        }
        rotRect.setSize(QSize(rad*2,rad*2));
        rotRect.moveCenter(rect.center());
        rotCache=cache;
    }
}

void PaintArea::initRotate()
{
    if (cache.isNull())
        return;
    int rad=sqrt(pow(rect.height()/2,2)+pow(rect.width()/2,2));
    rotRect=QRect(rect.x()-(rad*2-rect.width())/2,rect.y()-(rad*2-rect.height())/2,rad*2,rad*2);
    rotCache=cache;
    beg=rotRect.topLeft();
    rotState=2;
}

void PaintArea::rotateFrame(int delta)
{
    if (rotRect.isNull())
        return;
    QImage img(rotRect.size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter;
    painter.begin(&img);
    painter.save();
    img.fill(QColor(0,0,0,0));
    painter.translate(img.rect().center());
    if (delta>=0)
        rotDelta-=5;
    else
        rotDelta+=5;
    painter.rotate(rotDelta);
    painter.drawImage(-rotCache.width()/2,-rotCache.height()/2,rotCache);
    cache=img;
    painter.restore();
    painter.save();
    QImage i=globalCache.copy(QRect(beg,rotRect.size()));
    painter.drawImage(0,0,i);
    painter.translate(img.rect().center());
    painter.rotate(rotDelta);
    painter.drawImage(-rotCache.width()/2,-rotCache.height()/2,rotCache);
    painter.restore();
    painter.end();
    painter.begin(image);
    painter.drawImage(0,0,globalCache);
    painter.drawImage(beg,img);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawRect(QRect(beg.x(),beg.y(),img.size().width()-1,img.size().height()-1));
    painter.end();
    rect=QRect(beg,img.size());
    this->update();
}

void PaintArea::drawRect(const QPoint &point,const Qt::KeyboardModifiers& mod)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.end();
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<point.y()-beg.y())
                    rect=QRect(beg,QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(beg,QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(beg,point);
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<beg.y()-point.y())
                    rect=QRect(QPoint(beg.x(),beg.y()-point.x()+beg.x()),QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(QPoint(beg.x(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<point.y()-beg.y())
                    rect=QRect(QPoint(point.x(),beg.y()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-point.y()+beg.y(),beg.y()),QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<beg.y()-point.y())
                    rect=QRect(QPoint(point.x(),beg.y()-beg.x()+point.x()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-beg.y()+point.y(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(point,beg);
        }
    }
    if (rect.width()==0 && rect.height()==0)
        return;
    cache=image->copy(rect);
    cache.fill(QColor(0,0,0,0));
    painter.begin(&cache);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    painter.drawRect(curPen.width()/2,curPen.width()/2,rect.width()-curPen.width(),rect.height()-curPen.width());
    painter.end();
    painter.begin(image);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawImage(rect.topLeft(),cache);
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::drawElli(const QPoint &point,const Qt::KeyboardModifiers& mod)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.end();
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<point.y()-beg.y())
                    rect=QRect(beg,QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(beg,QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(beg,point);
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<beg.y()-point.y())
                    rect=QRect(QPoint(beg.x(),beg.y()-point.x()+beg.x()),QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(QPoint(beg.x(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<point.y()-beg.y())
                    rect=QRect(QPoint(point.x(),beg.y()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-point.y()+beg.y(),beg.y()),QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<beg.y()-point.y())
                    rect=QRect(QPoint(point.x(),beg.y()-beg.x()+point.x()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-beg.y()+point.y(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(point,beg);
        }
    }
    if (rect.width()==0 && rect.height()==0)
        return;
    cache=image->copy(rect);
    cache.fill(QColor(0,0,0,0));
    painter.begin(&cache);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    painter.drawEllipse(curPen.width()/2,curPen.width()/2,rect.width()-curPen.width(),rect.height()-curPen.width());
    painter.end();
    painter.begin(image);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawImage(rect.topLeft(),cache);
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::drawTria(const QPoint &point,const Qt::KeyboardModifiers& mod)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.end();
    int quarter=0;
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<=point.y()-beg.y())
                    rect=QRect(beg,QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(beg,QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(beg,point);
            quarter=1;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<=beg.y()-point.y())
                    rect=QRect(QPoint(beg.x(),beg.y()-point.x()+beg.x()),QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(QPoint(beg.x(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
            quarter=2;
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<=point.y()-beg.y())
                    rect=QRect(QPoint(point.x(),beg.y()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-point.y()+beg.y(),beg.y()),QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
            quarter=3;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<=beg.y()-point.y())
                    rect=QRect(QPoint(point.x(),beg.y()-beg.x()+point.x()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-beg.y()+point.y(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(point,beg);
            quarter=4;
        }
    }
    if (rect.width()==0 && rect.height()==0)
        return;
    cache=image->copy(rect);
    cache.fill(QColor(0,0,0,0));
    painter.begin(&cache);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    QPolygon polygon;
    if (mod & Qt::ControlModifier)
    {
        if (quarter==1)
        {
            polygon<<cache.rect().bottomLeft()+QPoint(curPen.width()/2,-curPen.width()/2);
            polygon<<cache.rect().topLeft()+QPoint(curPen.width()/2,curPen.width()/2);
            polygon<<cache.rect().topRight()+QPoint(-curPen.width()/2,curPen.width()/2);
        }
        if (quarter==2)
        {
            polygon<<cache.rect().topLeft()+QPoint(curPen.width()/2,curPen.width()/2);
            polygon<<cache.rect().bottomLeft()+QPoint(curPen.width()/2,-curPen.width()/2);
            polygon<<cache.rect().bottomRight()+QPoint(-curPen.width()/2,-curPen.width()/2);
        }
        if (quarter==3)
        {
            polygon<<cache.rect().topLeft()+QPoint(curPen.width()/2,curPen.width()/2);
            polygon<<cache.rect().topRight()+QPoint(-curPen.width()/2,curPen.width()/2);
            polygon<<cache.rect().bottomRight()+QPoint(-curPen.width()/2,-curPen.width()/2);
        }
        if (quarter==4)
        {
            polygon<<cache.rect().bottomLeft()+QPoint(curPen.width()/2,-curPen.width()/2);
            polygon<<cache.rect().bottomRight()+QPoint(-curPen.width()/2,-curPen.width()/2);
            polygon<<cache.rect().topRight()+QPoint(-curPen.width()/2,curPen.width()/2);
        }
    }
    else
    {
        if (quarter==1 || quarter==3)
        {
            polygon<<cache.rect().bottomLeft()+QPoint(curPen.width()/2,-curPen.width()/2);
            polygon<<QPoint(cache.rect().width()/2,0)+QPoint(0,curPen.width()/2);
            polygon<<cache.rect().bottomRight()+QPoint(-curPen.width()/2,-curPen.width()/2);
        }
        else
        {
            polygon<<cache.rect().topLeft()+QPoint(curPen.width()/2,curPen.width()/2);
            polygon<<cache.rect().topRight()+QPoint(-curPen.width()/2,curPen.width()/2);
            polygon<<QPoint(cache.rect().width()/2,cache.rect().height())-QPoint(0,curPen.width()/2);
        }

    }
    painter.drawPolygon(polygon);
    painter.end();
    painter.begin(image);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawImage(rect.topLeft(),cache);
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::drawStar(const QPoint &point, const Qt::KeyboardModifiers &mod)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.end();
    int quarter=0;
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<point.y()-beg.y())
                    rect=QRect(beg,QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(beg,QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(beg,point);
            quarter=1;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<beg.y()-point.y())
                    rect=QRect(QPoint(beg.x(),beg.y()-point.x()+beg.x()),QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(QPoint(beg.x(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
            quarter=2;
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<point.y()-beg.y())
                    rect=QRect(QPoint(point.x(),beg.y()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-point.y()+beg.y(),beg.y()),QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
            quarter=3;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<beg.y()-point.y())
                    rect=QRect(QPoint(point.x(),beg.y()-beg.x()+point.x()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-beg.y()+point.y(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(point,beg);
            quarter=4;
        }
    }
    if (rect.width()==0 && rect.height()==0)
        return;
    cache=image->copy(rect);
    cache.fill(QColor(0,0,0,0));
    painter.begin(&cache);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    QPoint center=cache.rect().center();
    QPolygon polygon;
    if (quarter==1 || quarter==3)
    {
        polygon<<QPoint(center.x(),cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.3426,cache.rect().height()*0.333);
        polygon<<QPoint(curPen.width()/2,cache.rect().height()*0.382);
        polygon<<QPoint(cache.rect().width()*0.25,cache.rect().height()*0.637);
        polygon<<QPoint(cache.rect().width()*0.194,cache.rect().height()-curPen.width()/2);
        polygon<<QPoint(cache.rect().center().x(),cache.rect().height()*0.8333);
        polygon<<QPoint(cache.rect().width()*0.805,cache.rect().height()-curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.75,cache.rect().height()*0.637);
        polygon<<QPoint(cache.rect().width()-curPen.width()/2,cache.rect().height()*0.382);
        polygon<<QPoint(cache.rect().width()*0.657,cache.rect().height()*0.333);
    }
    else
    {
        polygon<<QPoint(center.x(),cache.rect().bottom()-curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.3426,cache.rect().height()*0.667);
        polygon<<QPoint(curPen.width()/2,cache.rect().height()*0.618);
        polygon<<QPoint(cache.rect().width()*0.25,cache.rect().height()*0.363);
        polygon<<QPoint(cache.rect().width()*0.194,cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(cache.rect().center().x(),cache.rect().height()*0.1667);
        polygon<<QPoint(cache.rect().width()*0.805,cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.75,cache.rect().height()*0.363);
        polygon<<QPoint(cache.rect().width()-curPen.width()/2,cache.rect().height()*0.618);
        polygon<<QPoint(cache.rect().width()*0.657,cache.rect().height()*0.667);
    }
    painter.drawPolygon(polygon);
    painter.end();
    painter.begin(image);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawImage(rect.topLeft(),cache);
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::drawFive(const QPoint& point, const Qt::KeyboardModifiers &mod)
{
    QPainter painter(image);
    painter.drawImage(0,0,globalCache);
    painter.end();
    int quarter=0;
    if (point.x()>=beg.x())
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<point.y()-beg.y())
                    rect=QRect(beg,QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(beg,QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(beg,point);
            quarter=1;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (point.x()-beg.x()<beg.y()-point.y())
                    rect=QRect(QPoint(beg.x(),beg.y()-point.x()+beg.x()),QSize(point.x()-beg.x(),point.x()-beg.x()));
                else
                    rect=QRect(QPoint(beg.x(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(QPoint(beg.x(),point.y()),QPoint(point.x(),beg.y()));
            quarter=2;
        }
    }
    else
    {
        if (point.y()>=beg.y())
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<point.y()-beg.y())
                    rect=QRect(QPoint(point.x(),beg.y()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-point.y()+beg.y(),beg.y()),QSize(point.y()-beg.y(),point.y()-beg.y()));
            }
            else
                rect=QRect(QPoint(point.x(),beg.y()),QPoint(beg.x(),point.y()));
            quarter=3;
        }
        else
        {
            if (mod & Qt::ShiftModifier)
            {
                if (beg.x()-point.x()<beg.y()-point.y())
                    rect=QRect(QPoint(point.x(),beg.y()-beg.x()+point.x()),QSize(beg.x()-point.x(),beg.x()-point.x()));
                else
                    rect=QRect(QPoint(beg.x()-beg.y()+point.y(),point.y()),QSize(beg.y()-point.y(),beg.y()-point.y()));
            }
            else
                rect=QRect(point,beg);
            quarter=4;
        }
    }
    if (rect.width()==0 && rect.height()==0)
        return;
    cache=image->copy(rect);
    cache.fill(QColor(0,0,0,0));
    painter.begin(&cache);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    QPoint center=cache.rect().center();
    QPolygon polygon;
    if (quarter==1 || quarter==3)
    {
        polygon<<QPoint(center.x(),cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(curPen.width()/2,cache.rect().height()*0.382);
        polygon<<QPoint(cache.rect().width()*0.194,cache.rect().height()-curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.805,cache.rect().height()-curPen.width()/2);
        polygon<<QPoint(cache.rect().width()-curPen.width()/2,cache.rect().height()*0.382);
    }
    else
    {
        polygon<<QPoint(center.x(),cache.rect().bottom()-curPen.width()/2);
        polygon<<QPoint(curPen.width()/2,cache.rect().height()*0.618);
        polygon<<QPoint(cache.rect().width()*0.194,cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(cache.rect().width()*0.805,cache.rect().top()+curPen.width()/2);
        polygon<<QPoint(cache.rect().width()-curPen.width()/2,cache.rect().height()*0.618);
    }
    painter.drawPolygon(polygon);
    painter.end();
    painter.begin(image);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    painter.drawImage(rect.topLeft(),cache);
    painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
    painter.end();
    this->update();
}

void PaintArea::colorFromPoint(const QPoint &point)
{
    QColor col=this->image->pixel(point);
    emit sendColor(col);
}

void PaintArea::drawLom()
{
    QPainter painter(image);
    if (anti)
        painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(curPen);
    painter.drawImage(0,0,globalCache);
    for(int i=0;i<pointList.size()-1;i++)
        painter.drawLine(pointList[i],pointList[i+1]);
    painter.end();
    globalCache=*image;
    this->update();
}

void PaintArea::mousePressEvent(QMouseEvent *pe)
{
    if (pe->button()==Qt::LeftButton && mouseState==0)
        mouseState=1;
    if (pe->button()==Qt::RightButton && mouseState==0)
        mouseState=2;
    this->setFocus();
    if (mouseState==0 && pe->button()==Qt::MiddleButton)
    {
        stScroll=pe->globalPos();
        cacheCursor=this->cursor();
        this->setCursor(Qt::ClosedHandCursor);
    }
    if (tec==zal)
    {
        if (pe->button()==Qt::LeftButton)
        {
            this->fill(curPen.color(),pe->pos());
            curShape=zal;
        }
    }
    if (tec==ram)
    {
        if (pe->button()==Qt::LeftButton && mouseState==1)
        {
            if (state==1)
            {
                beg=pe->pos();
                globalCache=*image;
                curShape=tec;
            }
            else
            {
                if (rect.contains(pe->pos()))
                {
                    beg=pe->pos();
                    cacheCursor=this->cursor();
                    this->setCursor(Qt::SizeAllCursor);
                }
                else
                {
                    this->resetFrame(pe->pos());
                    if (curShape==rec || curShape==tri || curShape==ell || curShape==fiv || curShape==sta)
                    {
                        globalCache=*image;
                        this->inBackup(globalCache);
                    }
                }
            }
        }
        if (pe->button()==Qt::RightButton && mouseState==2)
        {
            if (state==2)
            {
                this->initScale(pe->pos());
                cacheCursor=this->cursor();
                this->setCursor(QCursor(QPixmap(":/resources/scale.png")));
            }
        }
    }
    if ((tec==rec || tec==tri || tec==ell || tec==fiv || tec==sta) && mouseState==1 && pe->button()==Qt::LeftButton)
    {
        beg=pe->pos();
        globalCache=*image;
        curShape=tec;
    }
    if (tec==penc)
    {
        if (pe->button()==Qt::LeftButton)
        {
            QPainter painter(image);
            painter.setPen(curPen);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            painter.drawPoint(pe->pos());
            painter.end();
            beg=pe->pos();
            this->update();
        }
    }
    if (tec==las)
    {
        if (pe->button()==Qt::LeftButton)
        {
            QPainter painter(image);
            painter.setPen(curLas);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            painter.drawPoint(pe->pos());
            painter.end();
            beg=pe->pos();
            this->update();
        }
    }
    if (tec==pip)
    {
        if (pe->button()==Qt::LeftButton)
            this->colorFromPoint(pe->pos());
    }
    if (tec==lom)
    {
        if (pe->button()==Qt::LeftButton)
        {
            if (pointList.isEmpty())
                this->inBackup(globalCache);//в список отмены
            pointList<<pe->pos();
            this->drawLom();
            this->setMouseTracking(true);
        }
        if (pe->button()==Qt::RightButton && !(pe->buttons() & Qt::LeftButton))
        {
            QPainter painter(image);
            painter.drawImage(0,0,globalCache);
            painter.end();
            pointList.clear();
            this->setMouseTracking(false);
            this->update();
        }
    }
    if (tec==pol)
    {
        if (pe->button()==Qt::LeftButton)
        {
            *image=globalCache;
            if (pointList.isEmpty())
                this->inBackup(globalCache);//в список отмены
            pointList<<pe->pos();
            QPainter painter(image);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::NoPen);
            painter.setBrush(curBrush);
            QPolygon p;
            for (int i=0;i<pointList.size();i++)
                p<<pointList[i];
            painter.drawPolygon(p);
            painter.end();
            globalCache=*image;
            this->drawLom();
            this->setMouseTracking(true);
        }
        if (pe->button()==Qt::RightButton && !(pe->buttons() & Qt::LeftButton))
        {
            QPainter painter(image);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            painter.drawImage(0,0,globalCache);
            painter.setPen(curPen);
            painter.drawLine(pointList.front(),pointList.back());
            painter.end();
            pointList.clear();
            globalCache=*image;
            this->setMouseTracking(false);
            this->update();
        }
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *pe)
{
    if (pe->buttons()==Qt::MiddleButton)
    {
        int a=stScroll.x()-pe->globalPos().x();
        int b=stScroll.y()-pe->globalPos().y();
        a=a*1778/QApplication::desktop()->width();
        b=b*1000/QApplication::desktop()->height();
        emit getScroll(a,b);
        stScroll=pe->globalPos();
    }
    if (tec==ram)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            if (state==1)
                this->drawFrame(pe->pos());
            else
            {
                if (!saveState && curShape==ram)
                {
                    QImage i=globalCache;
                    QPainter painter(&i);
                    painter.drawImage(rect,cache);
                    painter.end();
                    this->inBackup(i);
                    saveState=true;
                }
                this->moveFrame(pe->pos());
            }
        }
        if (pe->buttons() & Qt::RightButton && mouseState==2)
        {
            if (state==2)
            {
                if (!saveState && curShape==ram)
                {
                    QImage i=globalCache;
                    QPainter painter(&i);
                    painter.drawImage(rect,cache);
                    painter.end();
                    this->inBackup(i);
                    saveState=true;
                }
                this->scaleFrame(pe->pos());
            }
        }
    }
    if (tec==rec)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            this->drawRect(pe->pos(),pe->modifiers());
        }
    }
    if (tec==ell)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            this->drawElli(pe->pos(),pe->modifiers());
        }
    }
    if (tec==tri)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            this->drawTria(pe->pos(),pe->modifiers());
        }
    }
    if (tec==sta)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            this->drawStar(pe->pos(),pe->modifiers());
        }
    }
    if (tec==fiv)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
        {
            this->drawFive(pe->pos(),pe->modifiers());
        }
    }
    if (tec==penc)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
            this->drawCurve(pe->pos());
    }
    if (tec==las)
    {
        if (pe->buttons() & Qt::LeftButton && mouseState==1)
            this->clearCurve(pe->pos());
    }
    if (tec==lom)
    {
        if (pe->buttons()!=Qt::RightButton)
        {
            QPainter painter(image);
            QPen pen(curPen);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            QColor col=pen.color();
            col.setAlpha(pen.color().alpha()/2);
            pen.setColor(col);
            painter.setPen(pen);
            painter.drawImage(0,0,globalCache);
            painter.drawLine(pointList.back(),pe->pos());
            painter.end();
            this->update();
        }
    }
    if (tec==pol)
    {
        if (pe->buttons()!=Qt::RightButton)
        {
            QPainter painter(image);
            painter.drawImage(0,0,globalCache);
            QPen pen(curPen);
            if (anti)
                painter.setRenderHint(QPainter::Antialiasing);
            QColor col=pen.color();
            col.setAlpha(pen.color().alpha()/2);
            pen.setColor(col);
            QBrush brush(curBrush);
            col=brush.color();
            col.setAlpha(brush.color().alpha()/2);
            brush.setColor(col);
            painter.setBrush(brush);
            painter.setPen(Qt::NoPen);
            QPolygon p;
            p<<pointList.front()<<pointList.back()<<pe->pos();
            painter.drawPolygon(p);
            painter.setPen(pen);
            painter.drawLine(pointList.back(),pe->pos());
            painter.drawLine(pointList.front(),pe->pos());
            painter.end();
            this->update();
        }
    }
    if (tec==pip)
    {
        if (pe->buttons()==Qt::LeftButton)
            this->colorFromPoint(pe->pos());
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *pe)
{
    if (pe->button()==Qt::LeftButton && mouseState==1)
        mouseState=0;
    if (pe->button()==Qt::RightButton && mouseState==2)
        mouseState=0;
    if (pe->button()==Qt::MiddleButton)
    {
        this->setCursor(cacheCursor);
    }
    if (tec==ram)
    {
        if (pe->button()==Qt::LeftButton)
        {
            if (state==1)
            {
                QPainter painter(&globalCache);
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::white);
                painter.drawRect(rect);
                painter.end();
                state=2;
            }
            if (state==2)
            {
                rotRect.moveTopLeft(rect.topLeft());
                this->setCursor(cacheCursor);
            }
        }
        if (pe->button()==Qt::RightButton)
        {
            this->endScale();
            this->setCursor(cacheCursor);
        }
    }
    if (tec!=zal && tec!=ram && tec!=penc && tec!=las && tec!=pip && tec!=lom && tec!=pol)
    {
        if (pe->button()==Qt::LeftButton)
        {
            tec=ram;
            state=2;
        }
    }
    if (tec==penc || tec==las)
    {
        this->inBackup(globalCache);//в список отмены
    }
}

void PaintArea::wheelEvent(QWheelEvent *pe)
{
    if (tec==ram)
    {
        if ((pe->buttons() & Qt::LeftButton) || (pe->buttons() & Qt::RightButton))
            return;
        if (!saveState && curShape==ram)
        {
            QImage i=globalCache;
            QPainter painter(&i);
            painter.drawImage(rect,cache);
            painter.end();
            this->inBackup(i);
            saveState=true;
        }
        if (rotState==1)
            this->initRotate();
        else
            beg=rotRect.topLeft();
        this->rotateFrame(pe->delta());
    }
}

void PaintArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image);
    painter.end();
}

void PaintArea::keyPressEvent(QKeyEvent* pe)
{
    if (state==2 && tec==ram)
    {
        if (pe->key()==Qt::Key_C && pe->modifiers()==Qt::ControlModifier)
        {
            copyCache=cache;
        }
        if (pe->key()==Qt::Key_V && pe->modifiers()==Qt::ControlModifier)
        {
            if (copyCache.isNull())
                return;
            this->inBackup(globalCache);//в список отмены
            this->resetFrame(QPoint(0,0));
            curShape=tec;
            *image=globalCache;
            clearRect=QRect();
            rect=copyCache.rect();
            rect.moveTopLeft(QPoint(0,0));
            cache=copyCache;
            QPainter painter(image);
            painter.drawImage(rect.topLeft(),cache);
            painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
            painter.drawRect(QRect(rect.topLeft(),QSize(rect.width()-1,rect.height()-1)));
            painter.end();
            tec=ram;
            state=2;
            this->update();
        }
        if (pe->key()==Qt::Key_Delete)
        {
            *image=globalCache;
            rect=QRect();
            cache=QImage();
            this->update();
            this->inBackup(*image);
        }
    }
    if (pe->key()==Qt::Key_Z && pe->modifiers()==Qt::ControlModifier)
    {
        this->backupPrev();
    }
    if (pe->key()==Qt::Key_Z && pe->modifiers()==(Qt::ControlModifier | Qt::ShiftModifier))
    {
        this->backupNext();
    }
}
