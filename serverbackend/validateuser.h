#ifndef VALIDATEUSER_H
#define VALIDATEUSER_H

#include <QtSql>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "databasesclass.h"


class validateuser: public databasesClass
{
public:
    validateuser();
    QByteArray loginuser(QString username, QString password);
    QByteArray loginaccountant(QString username,QString password);
    QByteArray loginadmin(QString username, QString password);


private:
    QByteArray userfound;
};

#endif // VALIDATEUSER_H
