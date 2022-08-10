#ifndef DATABASESCONNECTIONCLASS_H
#define DATABASESCONNECTIONCLASS_H
#include <QtSql>
#include <QString>

class DataBasesConnectionClass
{
public:
    DataBasesConnectionClass();

    // connecting to database functions

    bool connectDatabase(QString databasename);
    QSqlDatabase getConDb();
    void closingConDb(QString dbname);



private:
    QSqlDatabase mydb;
};

#endif // DATABASESCONNECTIONCLASS_H
