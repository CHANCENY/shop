#include "dbcon.h"

DBCon::DBCon()
{

}

bool DBCon::itemcon()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopitems.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}

bool DBCon::saverusercon()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("saveuser.db");
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}
