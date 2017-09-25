#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QSettings>
#include <QString>

class App:public QApplication
{
    QSettings* setting;
public:
    App(int& argc,char** argv,QString strOrg,QString strAppName):QApplication(argc,argv),setting(0)
    {
        this->setOrganizationName(strOrg);
        this->setApplicationName(strAppName);
        setting=new QSettings(strOrg,strAppName,this);
    }
    ~App()
    {
        delete setting;
    }

    static App* theApp()
    {
        return (App*)qApp;
    }

    QSettings* settings()
    {
        return setting;
    }
};

#endif // APP_H
