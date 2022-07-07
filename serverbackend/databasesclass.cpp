#include "databasesclass.h"

databasesClass::databasesClass()
{

}

bool databasesClass::emmployeescon()
{
   mydb = QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName("SHOPKDATA.db");
   if(mydb.open())
   {
       return true;
   }
   return false;
}

bool databasesClass::itemsdb()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopitems.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}

bool databasesClass::bookshopcon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopbook.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}

bool databasesClass::releasemoney()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("ReleaseMoney.db");
    if(mydb.open())
    {
        return true;
    }
    return false;
}


