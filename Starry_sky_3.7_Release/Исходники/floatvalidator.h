#ifndef FLOATVALIDATOR_H
#define FLOATVALIDATOR_H

#include <QObject>
#include <QValidator>
class QString;
class QRegExp;

class FloatValidator:public QValidator
{
public:
    FloatValidator(QObject *parent=0):QValidator(parent) {}
    virtual State validate(QString &str,int& /*pos*/) const
    {
        if (str.length()>1 && str[0]=='0' && str[1]!='.')
            return Invalid;
        if (str.count('.')>1) return Invalid;
        QRegExp rxp1=QRegExp("[^0-9.]");
        if (str.contains(rxp1) || str=="." || str.size()>10)
            return Invalid;
        else return Acceptable;
    }
};


#endif // FLOATVALIDATOR_H
