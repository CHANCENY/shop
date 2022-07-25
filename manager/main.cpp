#include <QCoreApplication>
#include "adminmanagerclass.h"
#include <QString>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString recv;

    for(int i = 0; i < argc; i++)
    {
       recv = recv + argv[i];
    }

    QStringList list = recv.split("exe");

    if(list.last() != nullptr)
    {

        adminManagerClass admin(list.last());

    }

    adminManagerClass admin;





    return a.exec();
}
