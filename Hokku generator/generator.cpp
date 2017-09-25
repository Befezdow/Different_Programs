#include "generator.h"
#include <QTextStream>
#include <QFile>
#include <QApplication>
#include <QTime>

short Generator::stringToEnum(const QString &str)
{
    if (str=="HE")
        return 1;
    if (str=="SHE")
        return 2;
    if (str=="THEY")
        return 3;
    if (str=="WHAT_HE")
        return 4;
    if (str=="WHAT_SHE")
        return 5;
    if (str=="WHAT_THEY")
        return 6;
    if (str=="DOES")
        return 7;
    if (str=="DO")
        return 8;
    if (str=="DID_HE")
        return 9;
    if (str=="DID_SHE")
        return 10;
    if (str=="DID_THEY")
        return 11;
    if (str=="HOW")
        return 12;
    if (str=="WHERE")
        return 13;
    return -1;
}

unsigned int Generator::numberOfSyllables(const QVector<QString>& vec)
{
    QString vowels="уеыаоэяиУЕЫАОЭЯИ";
    unsigned int counter=0;
    for (int i=0; i<vec.size(); ++i)
    {
        QString str=vec.at(i);
        for (int j=0; j<str.size(); ++j)
        {
            if (vowels.contains(str.at(j)))
            {
                counter++;
            }
        }
    }
    return counter;
}

bool Generator::checkForCorrectness(const QVector<QString> &vec, unsigned int i)
{
    unsigned int count=numberOfSyllables(vec);
    return count == i;
}

Generator::Generator()
{
    for (int i=0; i<END; ++i)
    {
        dictionaries.push_back(QVector<QString>());
    }
}

void Generator::loadDictionaries(QVector<QString> dict)
{
    if (dict.size()!=END)
    {
        throw QString("Unexpected count of dictionaries");
    }

    QTextStream stream;
    QFile file;
    stream.setDevice(&file);
    for (int i=0; i<dict.size(); ++i)
    {
        file.setFileName(dict.at(i));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw QString("Dictionary isn't open");
        }
        while (!stream.atEnd())
        {
            dictionaries[i].push_back(stream.readLine());
        }
        file.close();
    }
}

QString Generator::generate() const
{
    QString result;
    qsrand(QTime::currentTime().msec());
    unsigned int templateSeed=qrand() % dictionaries.at(Templates).size();
    QString templateString=dictionaries.at(Templates).at(templateSeed);
    QVector<QString> lines=templateString.split("/").toVector();
    for (int i=0; i<lines.size(); ++i)
    {
        QVector<QString> words;
        while(true)
        {
            words=lines.at(i).split(" ").toVector();
            for (int j=0; j<words.size(); ++j)
            {
                QVector<QString> variants=words.at(j).split("|").toVector();
                unsigned int varSeed=qrand() % variants.size();
                short e=stringToEnum(variants.at(varSeed));
                if (e==-1)
                {
                    throw "Unknown word: "+words.at(j);
                }
                unsigned int wordSeed=qrand() % dictionaries.at(e).size();
                words[j].clear();
                words[j]=dictionaries.at(e).at(wordSeed);
            }
            if (i%2 == 0)
            {
                if (checkForCorrectness(words,5))
                {
                    break;
                }
            }
            else
            {
                if (checkForCorrectness(words,7))
                {
                    break;
                }
            }
        }
        words[0][0]=QChar(words.at(0).at(0)).toUpper();
        result+=QStringList(words.toList()).join(" ")+".\n";
    }
    result.remove(result.size()-1,1);
    return result;
}

void Generator::generateHokku()
{
    QString hokku;
    try
    {
        hokku=this->generate();
    }
    catch (QString str)
    {
        QMessageBox::critical(Q_NULLPTR,"Error",str,QMessageBox::Ok);
        qApp->exit(1);
    }
    emit takeHokku(hokku);
}

