#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QMessageBox>

class Generator: public QObject
{
    Q_OBJECT
    enum {START=0,Templates=0,He,She,They,WhatHe,WhatShe,WhatThey,Does,Do,DidHe,DidShe,DidThey,How,Where,END};

    QVector<QVector<QString>> dictionaries;

    static short stringToEnum(const QString& str);
    static unsigned int numberOfSyllables(const QVector<QString>& vec);
    static bool checkForCorrectness(const QVector<QString>& vec,unsigned int i);

public:
    Generator();
    void loadDictionaries(QVector<QString> dict);
    QString generate() const;

public slots:
    void generateHokku();
signals:
    void takeHokku(QString str);
};

#endif // GENERATOR_H
