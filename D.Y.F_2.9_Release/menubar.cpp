#include "menubar.h"
#include <QLabel>
#include <QApplication>
#include <QIcon>

MenuBar::MenuBar(PaintArea* area,QApplication *app, QWidget* parent):QMenuBar(parent)
{
    swgt=new SettingsWidget;
    file=new QMenu("Файл");
    save=file->addAction(QIcon(":/resources/save"),"Сохранить");
    saveas=file->addAction(QIcon(":/resources/saveas"),"Сохранить как ...");
    load=file->addAction(QIcon(":/resources/open"),"Открыть");
    file->addSeparator();
    quit=file->addAction(QIcon(":/resources/exit"),"Выход");
    this->addMenu(file);
    edit=new QMenu("Изменить");
    back=edit->addAction(QIcon(":/resources/back"),"Отменить",area,SLOT(backupPrev()),Qt::CTRL + Qt::Key_Z);
    front=edit->addAction(QIcon(":/resources/front"),"Повторить",area,SLOT(backupNext()),Qt::SHIFT+Qt::CTRL + Qt::Key_Z);
    edit->addSeparator();
    add=edit->addAction(QIcon(":/resources/+"),"Добавить изображение");
    change=edit->addAction(QIcon(":/resources/resize"),"Изменить разметы холста");
    edit->addSeparator();
    settings=edit->addAction(QIcon(":/resources/settings"),"Параметры",swgt,SLOT(show()));
    this->addMenu(edit);
    this->addSeparator();
    info=this->addAction("О программе");
    lbl=new QLabel("\nЭто самопальная версия графического редактора и\n"
                   "мой второй проект на QT. Здесь отсутствуют\n "
                   "функции зума изображения, рисования текста\n"
                   " и рисования закругленной кривой.\n"
                   "Возможно в будущем я это исправлю. @Befezdow\n"
                   "Hotkeys:\n Delete - удалить выделенную область\n"
                   "Ctrl+C - копировать выделенную область\n"
                   "Ctrl+V - вставить выделенную область\n"
                   "ПКМ - масштабирование\n"
                   "СКМ - перемещение по холсту\n"
                   "Колесико - поворот\n"
                   "Также есть комбинации с Ctrl и Shift "
                   "при рисовании фигур.\n");
    QFont font = lbl->font();
    font.setPointSize(12);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setFixedSize(500,275);
    lbl->setWindowTitle("О программе");
    QPalette pal;
    pal.setBrush(lbl->backgroundRole(),QColor(157,255,108));
    lbl->setPalette(pal);
    resizer=new ChangeSize;
    asker=new YesNo;
    QObject::connect(save,SIGNAL(triggered(bool)),area,SLOT(save()));
    QObject::connect(saveas,SIGNAL(triggered(bool)),area,SLOT(saveas()));
    QObject::connect(load,SIGNAL(triggered(bool)),area,SLOT(setImage()));
    QObject::connect(this,SIGNAL(ask()),area,SLOT(dif()));
    QObject::connect(area,SIGNAL(getDif(bool)),this,SLOT(changeState(bool)));
    QObject::connect(quit,SIGNAL(triggered(bool)),this,SLOT(askArea()));
    QObject::connect(asker,SIGNAL(yes()),area,SLOT(save()));
    QObject::connect(asker,SIGNAL(yes()),app,SLOT(quit()));
    QObject::connect(asker,SIGNAL(no()),app,SLOT(quit()));
    QObject::connect(add,SIGNAL(triggered(bool)),area,SLOT(addImage()));
    QObject::connect(change,SIGNAL(triggered(bool)),resizer,SLOT(show()));
    QObject::connect(resizer,SIGNAL(sendSize(QSize)),area,SLOT(resizeSheet(QSize)));
    QObject::connect(info,SIGNAL(triggered(bool)),lbl,SLOT(show()));
    QObject::connect(swgt,SIGNAL(getAnti()),area,SLOT(getAnti()));
    QObject::connect(swgt,SIGNAL(getFill(int)),area,SLOT(getFillSens(int)));
}

MenuBar::~MenuBar()
{
    delete info;
    delete save;
    delete saveas;
    delete load;
    delete add;
    delete change;
    delete quit;
    delete file;
    delete back;
    delete front;
    delete settings;
    delete edit;
    delete lbl;
    delete resizer;
    delete asker;
}

void MenuBar::changeState(bool a)
{
    state=a;
}

void MenuBar::askArea()
{
    emit ask();
    if (state)
        asker->show();
    else
        QApplication::quit();
}
