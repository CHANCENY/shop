#include <QCoreApplication>
#include "myserver.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <iostream>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    myServer server;
    server.startServer();

    return a.exec();
}


