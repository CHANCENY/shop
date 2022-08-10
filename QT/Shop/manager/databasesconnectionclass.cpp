#include "databasesconnectionclass.h"

DataBasesConnectionClass::DataBasesConnectionClass()
{

}

bool DataBasesConnectionClass::connectDatabase(QString databasename)
{
   mydb = QSqlDatabase::addDatabase("QSQLITE");
   mydb.setDatabaseName(databasename);

   if(mydb.open())
   {
       return true;
   }
   else
   {

   }

   return false;
}

QSqlDatabase DataBasesConnectionClass::getConDb()
{
    return this->mydb;
}

void DataBasesConnectionClass::closingConDb(QString dbname)
{
   mydb.removeDatabase(dbname);

   mydb.close();

}

