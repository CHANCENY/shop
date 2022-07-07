#ifndef DATABASESCLASS_H
#define DATABASESCLASS_H

#include <QtSql>
#include <QDir>



class databasesClass
{
public:
    databasesClass();
    bool emmployeescon();
    bool itemsdb();
    bool bookshopcon();
    bool releasemoney();



private:

    QSqlDatabase mydb;
};

#endif // DATABASESCLASS_H
