#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>



class Database
{
public:
    Database();
    bool connection();
    bool softcon();
    bool bookcon();
    bool itemdbcon();
    bool savedusercon();
    bool releasemoneycon();

    QSqlDatabase mydb;


};

#endif // DATABASE_H
