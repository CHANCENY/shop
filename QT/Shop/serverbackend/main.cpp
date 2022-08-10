#include <QCoreApplication>
#include "myserver.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <iostream>




bool checkport()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("PORT");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        QString line = in.readAll();
        myfile.flush();
        myfile.close();

        if(line != nullptr)
        {
            return true;
        }
    }

  return false;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    bool okport = checkport();

    if(okport == true)
    {
        myServer server;
        server.startServer();
         return a.exec();
    }
    else
    {
      QDir dir;
      QString portingapp = dir.absoluteFilePath("porting.exe");



      for(int i = 0; i < portingapp.size(); i++)
      {
        if(portingapp[i] =='/')
        {
            portingapp[i]='\\';
        }
      }
      if(portingapp != nullptr)
      {


         std::cout<<"PORT NUMBER IS NOT SET UP:\n\n Please cd in current directory and run this command\n\nporting.exe -portconfig";


      }

    }

   return a.exec();

}


