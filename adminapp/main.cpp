#include "login.h"
#include "newemployees.h"
#include <QtSql>

#include <QApplication>

bool checkAdmin();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    newEmployees ww;

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
