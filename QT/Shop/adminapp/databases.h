#ifndef DATABASES_H
#define DATABASES_H
#include <QtSql>



class Databases
{
public:
    Databases();
    bool employdbcon();
    bool bookcon();
    bool releasMoneycon();

    QSqlDatabase mydb;
};

#endif // DATABASES_H
