#ifndef ADMINCLASS_H
#define ADMINCLASS_H

#include <QtSql>
#include <QDir>
#include "databasesclass.h"



class AdminClass: public databasesClass
{
public:
    AdminClass();
    QByteArray employeesTable(QString line);
    QByteArray createBook(QString name, QString number);
    QByteArray changeUserInfo(QString obj);
    QByteArray deleteUser(QString username, QString password);
    QByteArray creatingAccountUser(QString name, QString username, QString title, QString password, QString photo);
    QByteArray releasingMoneyAuth(QString code, QString verified, QString expire, QString exp, QString amountex, QString admin);
    QByteArray expiringcode(QString line);
};

#endif // ADMINCLASS_H
