#include "login.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "settings.h"

#include <QApplication>

bool checkIpConfig();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;

    settings ww;

    if(checkIpConfig())
    {
        w.show();
        return a.exec();
    }
    else
    {
        ww.show();
        return a.exec();
    }


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
