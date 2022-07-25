#include "portclass.h"
#include <QDir>
#include <QDebug>
#include <iostream>
#include <string>



portClass::portClass()
{

}

void portClass::declarePortNumber(QString portnumber)
{
  if(portnumber != nullptr)
  {
    QDir dir;
    QString filename = dir.absoluteFilePath("PORT");


    // write into file

    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);

        out<<portnumber;
        myfile.flush();
        myfile.close();
        qDebug()<<"PORT -> "<<portnumber<<" set successfully";
        return;
    }
  }
}

void portClass::clearPortNumber()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("PORT");


    // write into file

    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);

        out<<"";
        myfile.flush();
        myfile.close();
        qDebug()<<"Port clearing successfully";
        return;
    }
}

void portClass::defaultPort()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("PORT");


    // write into file

    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);

        out<<"8888";
        myfile.flush();
        myfile.close();
        qDebug()<<"Port change to default 8888 successfully";
        return;
    }
}

void portClass::recieverCommands(QString command)
{

  if(command == "-portconfig" || command == "-PORTCONFIG")
  {
      std::string port;
      std::cout<<"New port number>";
     std::cin>>port;
    if(port.size() > 2)
    {
        this->declarePortNumber(QString::fromStdString(port));
        std::cout<<"Press any key to escape.";
        system("pause > 0");
    }
  }
  if(command == "-clearport" || command == "-CLEARPORT")
  {
     int confirm = 0;
     std::cout<<"Are you sure want to clear ? Yes (1) or No (0).";
     std::cin>>confirm;

     if(confirm == 1)
         this->clearPortNumber();
     else
       std::cout<<"Clearing port number denied"<<std::endl;

     return;
  }

  if(command == "-defaultport" || command == "-DEFAULTPORT")
  {
      int confirm = 0;
      std::cout<<"Are you sure you want to set default port ? Yes (1) or No (0).";
      std::cin>>confirm;

      if(confirm == 1)
          this->defaultPort();
      else
          std::cout<<"Setting default port 8888 denied"<<std::endl;

      return;
  }
  if(command == "-help" || command == "-HELP")
  {
      this->help();
  }
  if(command == "-home" || command == "-HOME")
  {
      this->homeLandingFunction();
  }
}

void portClass::homeLandingFunction()
{

    system("cls");
   std::cout<<"porting software is used to change port setting of the server software."<<std::endl;
   std::cout<<std::endl;

   std::cout<<"New port number (N) Clean port number (C) Set default port number (D) Help (H)."<<std::endl<<std::endl;


   std::string option;
   std::cout<<"option >";
   std::cin>>option;

   QString op = QString::fromStdString(option);

   if(op.toLower() == "n")
   {
       std::string port;

      this->recieverCommands("-portconfig");
   }
   if(op.toLower() == "c")
   {
       this->recieverCommands("-clearport");
   }
   if(op.toLower() == "d")
   {
       this->recieverCommands("-defaultport");
   }
   if(op.toLower() == "h")
   {
      this->recieverCommands("-help");
   }

}

void portClass::help()
{
    system("cls");
  QDir di;
  QString filename = di.absoluteFilePath("help.txt");
  QFile myfile(filename);

  myfile.open(QIODevice::ReadOnly);
  if(myfile.isOpen())
  {

      QTextStream in (&myfile);

      QString help = in.readAll();
     std::cout<<help.toStdString()<<std::endl<<std::endl; std::cout<<"press enter to continue to home menu.";
    system("pause > 0");
  }
}















