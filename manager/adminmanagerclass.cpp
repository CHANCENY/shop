#include "adminmanagerclass.h"
#include <string>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QSqlTableModel>
#include <iomanip>
#include <QProcess>




static int position = 1;

bool loggedin = false;

QString openedDB = nullptr;
QString openedDB2 = nullptr;
QString nameAdmin = nullptr;

adminManagerClass::adminManagerClass()
{
    position = this->lastHistroy() + 1;
    this->homeCommandBased();

}

adminManagerClass::adminManagerClass(QString comm)
{

    // start prompting admin
   startingpoint:


 std::string command = comm.toStdString();

 QString com =  QString::fromStdString(command).toLower();

 QStringList list = com.split(' ');
 com = list[0];


 //collecting command history
 this->historyCollecting(com,1);
 // deciding the command action

 if(com == ".clear")
 {
     system("cls");
     goto startingpoint;
 }
 if(com == ".help")
 {
     this->helpFunction();
      goto startingpoint;
 }
 if(com == ".history")
 {
   this->historyCollecting("none",2);
   goto startingpoint;
 }
 if(com == ".home")
 {
     this->home();
 }
 else
 {
     std::cout<<std::endl<<"Log in to have full access"<<std::endl<<std::endl;
    return;
 }

}

int adminManagerClass::lastHistroy()
{
    QDir dir;

    QString filename = dir.absoluteFilePath("history.txt");

    QString info = nullptr;

    // reading help file

    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        while(!in.atEnd())
        {
            if(in.readLine(0) != nullptr)
            {
                info = in.readLine(0);
            }

        }
        myfile.close();

        if(info != nullptr)
        {
            QStringList list = info.split(':');
            return list[0].toInt();
        }
    }

    return 0;
}

void adminManagerClass::homeCommandBased()
{
   std::cout<<"Admin Command App Manager"<<std::endl;


   std::cout<<"Quick help: clear screen .clear, hitory .history,  more help .help"<<std::endl<<std::endl;

   // start prompting admin
  startingpoint:


  if(loggedin == true)
  {


std::string command, command2;
std::cout<<nameAdmin.toStdString()<<openedDB.toStdString()<<"$>";

std::getline(std::cin,command);


// converting std string to qt format string QString



QString com =  QString::fromStdString(command).toLower();

QStringList list = com.split(' ');
com = list[0];



//collecting command history
this->historyCollecting(com,1);
// deciding the command action

if(com == ".clear")
{
    system("cls");
    goto startingpoint;
}
if(com == ".help")
{
    this->helpFunction();
     goto startingpoint;
}
if(com == ".history")
{
  this->historyCollecting("none",2);
  goto startingpoint;
}
if(com == ".history-d")
{
    this->historyCollecting("none",3);
    goto startingpoint;
}
if(com == ".dbs")
{
    this->DatabaseList();
    goto startingpoint;
}
if(com == ".open")
{
    this->openDatabase(QString::fromStdString(command));
   goto startingpoint;
}
if(com == ".tables")
{
    this->showTables();
    goto startingpoint;
}
if(com == ".quit")
{
    this->closeDatabase();
    goto startingpoint;
}
if(com == "create")
{
    this->createTables(QString::fromStdString(command));
    goto startingpoint;
}
else
{
    this->homeCommandBased2(command);
    goto startingpoint;
}

goto startingpoint;

  }
  else
  {


      std::string command, command2;
      std::cout<<nameAdmin.toStdString()<<openedDB.toStdString()<<"$>";

      std::getline(std::cin,command);


      // converting std string to qt format string QString
      QString com =  QString::fromStdString(command).toLower();

      QStringList list = com.split(' ');
      com = list[0];

      //collecting command history
      this->historyCollecting(com,1);
      // deciding the command action

      if(com == ".help")
      {
          this->helpFunction();
           goto startingpoint;
      }
      if(com == ".history")
      {
        this->historyCollecting("none",2);
        goto startingpoint;
      }
      if(com == ".dbs")
      {
          this->DatabaseList();
          goto startingpoint;
      }
      if(com == ".quit")
      {
          this->closeDatabase();
          goto startingpoint;
      }
      if(com == ".clear")
      {
          system("cls");
          goto startingpoint;
      }
      if(com == ".login")
      {
          this->login();
           goto startingpoint;
      }
      if(com == ".home")
      {
          this->home();
      }
      else
      {
          std::cout<<std::endl<<"Log in to have full access"<<std::endl<<std::endl;
          goto startingpoint;
      }

  }
}

void adminManagerClass::helpFunction()
{
   system("cls");
   std::cout<<std::endl;
   QDir dir;

   QString filename = dir.absoluteFilePath("help.txt");

   // reading help file

   QFile myfile(filename);
   myfile.open(QIODevice::ReadOnly);
   if(myfile.isOpen())
   {
       QTextStream in(&myfile);

       std::cout<<in.readAll().toStdString()<<std::endl<<std::endl;
       myfile.close();
   }
}

void adminManagerClass::historyCollecting(QString hist, int flag)
{

    if(flag == 1)
    {

        QDir dir;
        QString filename = dir.absoluteFilePath("history.txt");

        // reading help file

        QFile myfile(filename);
        myfile.open(QIODevice::WriteOnly|QIODevice::Append|QFile::Text);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);
            in<<QString::number(position)+": "+hist+'\n';
            myfile.flush();
            myfile.close();

            position++;

        }

    }
    if(flag == 2)
    {
        QDir dir;

        QString filename = dir.absoluteFilePath("history.txt");

        // reading help file

        QFile myfile(filename);
        myfile.open(QIODevice::ReadOnly);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);

            std::cout<<std::endl<<in.readAll().toStdString()<<std::endl<<std::endl;
            myfile.close();
        }
    }

    if(flag == 3)
    {
        QDir dir;
        QString filename = dir.absoluteFilePath("history.txt");

        // reading help file

        QFile myfile(filename);
        myfile.open(QIODevice::WriteOnly|QFile::Text);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);

            in<<"";
            myfile.flush();
            myfile.close();

            position = 0;
        }
    }
}

void adminManagerClass::DatabaseList()
{
  QDir dir;

  // getting the running current directory

  QString currentdir = dir.currentPath();

  // collecting all files of db extension
  QStringList foundfiles = dir.entryList(QStringList()<<"*.db",QDir::Files);


  // checking if found any file of db extension
  if(foundfiles.empty())
  {
      std::cout<<"No databases found"<<std::endl<<std::endl;
      return;
  }


  //displaying all file on console
  std::cout<<std::endl;
  foreach(QString filename, foundfiles)
  {
      std::cout<<filename.toStdString()<<std::endl;
  }

  std::cout<<std::endl;
}

void adminManagerClass::openDatabase(QString databasename)
{
    // split command

   system("cls");

    QString dbname = databasename.split(' ').last();

    // check if name of db is collected successfully

    if(openedDB2 != nullptr)
    {
        std::cout<<"current connected "<<openedDB2.toStdString()<<std::endl<<std::endl;
        return;
    }
       // connecting to database opened

    // when database is not availble will create new db

   if(dbname != nullptr && dbname.split('.').last() == "db")
   {
        if(connectDatabase(dbname))
        {
            openedDB2 = dbname;
            QString append = dbname+">";
            std::cout<<"working on "<<dbname.toStdString()<<std::endl<<std::endl;
            openedDB = append;
           return;
        }
        else
        {
            std::cout<<"openning failed"<<std::endl<<std::endl;
            return;
        }
    }
   else
   {
       std::cout<<"line error  give db name .db"<<std::endl<<std::endl;
   }


}

void adminManagerClass::showTables()
{

     QSqlDatabase my = this->getConDb();

     QStringList tables = my.tables();

     if(tables.empty())
     {
         std::cout<<"no table found"<<std::endl<<std::endl;
     }
     else
     {
         foreach(QString line, tables)
         {
             std::cout<<line.toStdString()<<std::endl;
         }
     }

}

void adminManagerClass::closeDatabase()
{

    if(openedDB2 != nullptr)
    {
       this->closingConDb(openedDB2);
        openedDB = nullptr;
        openedDB2 = nullptr;
    }
    else
    {
        std::cout<<std::endl<<"Not connected to any database"<<std::endl<<std::endl;
    }

}

void adminManagerClass::createTables(QString tablequery)
{
   if(tablequery != nullptr)
   {
     QSqlQuery query;
     query.prepare(tablequery);
     if(query.exec())
     {
         std::cout<<"table created"<<std::endl<<std::endl;
         return;
     }
     else
     {
         std::cout<<"error occurred"<<std::endl;
         std::cout<<std::endl<<std::endl;
         return;
     }
   }

}

void adminManagerClass::insertingData(QString insertquery)
{
    if(insertquery != nullptr)
    {
        QStringList querys = insertquery.split(';');

        int counter = 0;

        if(querys.size() > 0)
        {
            for(int i = 0; i < querys.size() - 1; i++)
            {
                QSqlQuery query;
                query.prepare(querys[i]+";");
                if(query.exec())
                {
                   counter++;
                   std::cout<<"row affected count "<<counter<<std::endl;
                   continue;
                }

            }
        }

        if(counter == querys.size() - 1)
        {
            std::cout<<"Data saved completed in "+openedDB2.toStdString()<<std::endl;
            return;
        }
    }

}

void adminManagerClass::homeCommandBased2(std::string line)
{

    QString com =  QString::fromStdString(line).toLower();

    QStringList list = com.split(' ');
    com = list[0];

    if(com == "insert")
    {
        this->insertingData(QString::fromStdString(line));
        return;
    }
    if(com == "update")
    {
        this->updateTableValues(QString::fromStdString(line));
    }
    if(com == "drop")
    {
        this->removeTable(QString::fromStdString(line));
        return;
    }
    if(com == "delete")
    {
        this->deleteInTable(QString::fromStdString(line));
        return;
    }
    if(com == "select")
    {
        this->viewValuesInTable(QString::fromStdString(line));
        return;
    }
    if(com ==".new")
    {
        this->newWindow();
        return;
    }
    if(com == ".login")
    {
        this->login();
        return;
    }
    if(com == ".logout")
    {
        this->logout();
        return;
    }
    if(com == ".home")
    {
        this->home();
    }
}

void adminManagerClass::updateTableValues(QString updatequery)
{
    if(updatequery != nullptr)
    {
        QSqlQuery query;
        query.prepare(updatequery);
        if(query.exec())
        {
            std::cout<<"Data updated in "+openedDB2.toStdString()<<std::endl;
            return;
        }
        else
        {

            std::cout<<"error occurred"<<std::endl;
        }
    }
}

void adminManagerClass::removeTable(QString droptablequery)
{
  if(droptablequery != nullptr)
  {
      QSqlQuery query;
      query.prepare(droptablequery);
      if(query.exec())
      {
          std::cout<<"table dropped successfully"<<std::endl<<std::endl;
          return;
      }
      else
      {
          std::cout<<"error occurred"<<std::endl<<std::endl;
          return;
      }
  }
}

void adminManagerClass::deleteInTable(QString deletequery)
{
  if(deletequery != nullptr)
  {
      QSqlQuery query;
      query.prepare(deletequery);

      if(query.exec())
      {
          std::cout<<"deleting occurred successfully"<<std::endl<<std::endl;
          return;
      }
      else
      {
          std::cout<<"error occurred"<<std::endl<<std::endl;
          return;
      }

  }
}

void adminManagerClass::viewValuesInTable(QString viewquery)
{
    if(viewquery != nullptr)
    {
        // making process
        QProcess process;
        for(int i = 0; i < viewquery.length(); i++)
        {
            if(viewquery[i] ==' ')
            {
                viewquery[i] = '#';
            }

        }

        QString arg = openedDB2+"-"+viewquery;

        QStringList argument;
        argument.append(arg);

        // process execution of ResultCom.exe software
        process.execute("ResultCom.exe",argument);

        return;



    }
}

void adminManagerClass::newWindow()
{



}

void adminManagerClass::loginAdmin(QString username, QString password)
{
    QSqlDatabase dbs = QSqlDatabase::addDatabase("QSQLITE");
    dbs.setDatabaseName("SHOPKDATA.db");
    if(dbs.open())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM employees WHERE username='"+username+"';");
        if(query.exec())
        {
            QString usernamedb = nullptr;
            QString passwordb = nullptr;
            QString name = nullptr;

            while(query.next())
            {
              usernamedb = query.value(1).toString();
              passwordb = query.value(3).toString();
              name = query.value(0).toString();

            }

            if(usernamedb != nullptr && passwordb != nullptr)
            {
               if(password == passwordb)
               {
                  loggedin = true;
                  dbs.removeDatabase("SHOPKDATA.db");
                  system("cls");
                  nameAdmin = nameAdmin + name+">";
                  dbs.close();
                  return;
               }
               else
               {
                   std::cout<<std::endl<<"Password failed to match!"<<std::endl<<std::endl;
                   dbs.removeDatabase("SHOPKDATA.db");
                   dbs.close();
                   return;
               }
            }
            else
            {
                std::cout<<std::endl<<"Username failed to match!"<<std::endl<<std::endl;
                dbs.removeDatabase("SHOPKDATA.db");
                dbs.close();
                return;
            }
        }
    }

}

void adminManagerClass::login()
{
     system("cls");
   loggedin = false;
   openedDB2 = nullptr;
   openedDB = nullptr;
   nameAdmin = nullptr;

   std::string username, password;
   std::cout<<"USERNAME: ";
   std::getline(std::cin,username);
   std::cout<<"ENTER PASSWRD: ";
   std::getline(std::cin,password);

   if(username.length() > 0 && password.length() > 0)
   {
       this->loginAdmin(QString::fromStdString(username), QString::fromStdString(password));
       return;

   }

   return;
}

void adminManagerClass::logout()
{
    system("cls");
    loggedin = false;
    openedDB2 = nullptr;
    nameAdmin = nullptr;
    openedDB = nullptr;
    std::cout<<std::endl<<"logged out"<<std::endl<<std::endl;
    return;
}

void adminManagerClass::home()
{
    system("cls");
  this->homeCommandBased();
}














