#include "toolpanel.h"

ToolPanel::ToolPanel(QWidget* parent):QListWidget(parent)
{
    this->setViewMode(QListWidget::IconMode);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/rama.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/pen.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/lastik.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/pipetka.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/zalivka.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/rect.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/triangle.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/ellipse.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/five.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/star.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/lomanaya.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item=new QListWidgetItem(this);
    item->setIcon(QIcon(":/resources/polygon.png"));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(157,115);
    QObject::connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(SendTool(QListWidgetItem*)));
}

ToolPanel::~ToolPanel()
{
    QObject::disconnect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(SendTool(QListWidgetItem*)));
    delete item;
}

void ToolPanel::SendTool(QListWidgetItem* item)
{
    emit SendNum(this->row(item));
}
