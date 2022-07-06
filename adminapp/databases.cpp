#include "databases.h"

Databases::Databases()
{

}

bool Databases::employdbcon()
{
   mydb = QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName("SHOPKDATA.db");
   if(mydb.open())
   {
       return true;
   }
   return false;
}

bool Databases::bookcon()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopbook.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}

bool Databases::releasMoneycon()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("ReleaseMoney.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}
