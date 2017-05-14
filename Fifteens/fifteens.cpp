#include "fifteens.h"

Fifteens::Fifteens(int width, int height, QWidget *parent):
    QWidget(parent),
    fieldWidth(width),
    fieldHeight(height)
{
    width=width%17;
    height=height%17;

    win1=new unsigned char [width*height];
    win2=new unsigned char [width*height];

    for (int i=0;i<width*height-1;++i)
    {
        win1[i]=i+1;
    }
    win1[width*height-1]=0;

    for (int i=0;i<width*height-3;++i)
    {
        win2[i]=i+1;
    }
    win2[width*height-3]=width*height-1;
    win2[width*height-2]=width*height-2;
    win2[width*height-1]=0;

    buttons=new QPushButton* [width*height];
    numbers=new unsigned char [width*height];
    lay=new QGridLayout;

    QList<int> list;
    QPushButton* tempMass[width*height];
    int buttonSide=qApp->desktop()->width()/27.32;

    for (int i=0;i<width*height;++i)
    {
        tempMass[i]=new QPushButton(QString::number(i));
        tempMass[i]->setFixedSize(buttonSide,buttonSide);
        tempMass[i]->setFocusProxy(this);
        list.push_back(i);
    }

    qsrand(QTime::currentTime().second());

    for (int i=0;i<width*height;++i)
    {
        int index=qrand() % list.size();

        numbers[i]=list.at(index);
        buttons[i]=tempMass[numbers[i]];

        lay->addWidget(buttons[i],i/fieldWidth,i%fieldWidth);
        list.removeAt(index);

        if (numbers[i]==0)
        {
            zeroPos=i;
            buttons[i]->hide();
        }
    }

    this->setLayout(lay);
}

Fifteens::~Fifteens()
{
    delete [] buttons;
    delete [] numbers;
    delete [] win1;
    delete [] win2;
}

bool Fifteens::move(int direction)
{
    int newZeroPos;
    switch (direction)
    {
    case Up:
        if (zeroPos < fieldWidth)
        {
            return false;
        }
        newZeroPos=zeroPos-fieldWidth;
        break;

    case Down:
        if (zeroPos >= fieldWidth*(fieldHeight - 1))
        {
            return false;
        }
        newZeroPos=zeroPos+fieldWidth;
        break;

    case Left:
        if (zeroPos%fieldWidth == 0)
        {
            return false;
        }
        newZeroPos=zeroPos-1;
        break;

    case Right:
        if (zeroPos%fieldWidth == fieldWidth-1)
        {
            return false;
        }
        newZeroPos=zeroPos+1;
        break;

    default:
        return false;
    }

    lay->removeWidget(buttons[newZeroPos]);
    lay->removeWidget(buttons[zeroPos]);

    QPushButton* temp1=buttons[newZeroPos];
    buttons[newZeroPos]=buttons[zeroPos];
    buttons[zeroPos]=temp1;

    char temp2=numbers[newZeroPos];
    numbers[newZeroPos]=numbers[zeroPos];
    numbers[zeroPos]=temp2;

    lay->addWidget(buttons[newZeroPos],newZeroPos/fieldWidth,newZeroPos%fieldWidth);
    lay->addWidget(buttons[zeroPos],zeroPos/fieldWidth,zeroPos%fieldWidth);

    zeroPos=newZeroPos;

    return true;
}

bool Fifteens::checkWin()
{
    if (memcmp(this->numbers,win1,fieldWidth*fieldHeight)==0 ||
            memcmp(this->numbers,win2,fieldWidth*fieldHeight)==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Fifteens::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        this->move(Up);
        break;
    case Qt::Key_Down:
        this->move(Down);
        break;
    case Qt::Key_Left:
        this->move(Left);
        break;
    case Qt::Key_Right:
        this->move(Right);
        break;
    }
    if (checkWin())
    {
        QMessageBox::information(this,"Victory","You win!!!",QMessageBox::Ok);
        qApp->quit();
    }
}
