#include "login.h"
#include "newemployees.h"
#include "settings.h"
#include <QtSql>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include <QApplication>

bool checkAdmin();

bool checkIpConfig();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    newEmployees ww;
    settings www;

    bool ipconfig = checkIpConfig();

    if(ipconfig == true)
    {
        bool ok = checkAdmin();

        if(ok == true)
        {
            w.show();
            return a.exec();
        }
        else
        {
            ww.firstTime("newnow");
            ww.show();
            return a.exec();
        }

    }
    else
    {
      www.show();
      return a.exec();
    }

}


bool checkAdmin()
{
    QSqlDatabase my = QSqlDatabase::addDatabase("QSQLITE");
    my.setDatabaseName("SHOPKDATA.db");
    if(my.open())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM employees;");
        if(query.exec())
        {
            QString line = nullptr;

            while(query.next())
            {
                line = query.value(1).toString();
            }

            if(line != nullptr)
            {
                return true;
            }
        }
    }

    return false;
}


bool checkIpConfig()
{
   QDir dir; QString filename = dir.absoluteFilePath("ConfigNetwork");

   QFile myfile(filename);
   myfile.open(QIODevice::ReadOnly);
   if(myfile.isOpen())
   {
       QTextStream in(&myfile);
       QString line = in.readAll();

       if(line != nullptr)
       {
           return true;
       }
   }
   return false;
}
