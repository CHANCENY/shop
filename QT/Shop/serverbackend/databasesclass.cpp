#include "databasesclass.h"

databasesClass::databasesClass()
{

}

bool databasesClass::emmployeescon()
{
    qDebug()<<"Connecting to Databse.....";
   mydb = QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName("SHOPKDATA.db");
   if(mydb.open())
   {
       qDebug()<<"Database connected....";
       return true;
   }
   qDebug()<<"Database connection failed....";
   return false;
}

bool databasesClass::itemsdb()
{
     qDebug()<<"Connecting to Databse.....";
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopitems.db");
    if(mydb.open())
    {
         qDebug()<<"Database connected....";
        return true;
    }
    qDebug()<<"Database connection failed....";
    return false;
}

bool databasesClass::bookshopcon()
{
     qDebug()<<"Connecting to Databse.....";
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopbook.db");
    if(mydb.open())
    {
         qDebug()<<"Database connected....";
        return true;
    }
    qDebug()<<"Database connection failed....";
    return false;
}

bool databasesClass::releasemoney()
{
     qDebug()<<"Connecting to Databse.....";
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("ReleaseMoney.db");
    if(mydb.open())
    {
         qDebug()<<"Database connected....";
        return true;
    }
    qDebug()<<"Database connection failed....";
    return false;
}


