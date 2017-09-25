#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QWidget>
#include <QListWidget>
class QListWidgetItem;

class ToolPanel:public QListWidget
{
    Q_OBJECT
    QListWidgetItem* item;
public:
    ToolPanel(QWidget* parent=0);
    ~ToolPanel();
private slots:
    void SendTool(QListWidgetItem* item);
signals:
    void SendNum(int num);
};

#endif // TOOLPANEL_H
