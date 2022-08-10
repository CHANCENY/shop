#include "database.h"

Database::Database()
{

}

bool Database::connection()
{
   mydb = QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName("SHOPKDATA.db");
   if(mydb.open())
   {
       return true;
   }
   else
   {
       return false;
   }

}

bool Database::softcon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("software.db");
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::bookcon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopbook.db");
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::itemdbcon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("shopitems.db");
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::savedusercon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
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

bool Database::releasemoneycon()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("ReleaseMoney.db");
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }

}
