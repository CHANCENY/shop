#include "mytask.h"




mytask::mytask()
{

}

void mytask::TaskGivenFile()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
       this->data = in.readAll().toUtf8();
        myfile.close();
    }

}

void mytask::PassDataTosend(QByteArray arr)
{
    QDir dir;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
         in<<arr;
         myfile.flush();
        myfile.close();
    }
}

QByteArray mytask::Sending()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
       QByteArray r = in.readAll().toUtf8();
        myfile.close();
        return r;
    }
    return nullptr;
}

void mytask::DecisionPath()
{
    QString dataline =QString::fromStdString(this->data.toStdString());
    QStringList list = dataline.split(',');


    // action variable hold the request type to be done eg login
    QString action = list.at(0);

    if(action == "login")
    {
        PassDataTosend(loginuser(list[1],list[2]));
    }
    if(action == "Availableitem")
    {
        PassDataTosend(collectAvaiableItems(list[1]));
    }
    if(action == "sell")
    {
      PassDataTosend(sellingupdate(list[1]));
    }
    if(action == "Alogin")
    {
        PassDataTosend(loginaccountant(list[1],list[2]));
    }
    if(action == "ALLITEMS")
    {
        PassDataTosend(allcollectionitems(list[1]));
    }
    if(action == "ALLBOOK")
    {
        PassDataTosend(allcollectionbook(list[1]));
    }
    if(action == "saving")
    {
        PassDataTosend(savingiteminshop(list[1]));
    }
    if(action == "change")
    {
       PassDataTosend(changecollect(list[1]));
    }
    if(action == "expediture")
    {
        PassDataTosend(expeditures(list[1]));
    }
    if(action == "AdminLogin")
    {
        PassDataTosend(loginadmin(list[1],list[2]));
    }
    if(action == "employees")
    {
        PassDataTosend(employeesTable(list[1]));
    }
    if(action == "CreateBookAccount")
    {
        PassDataTosend(createBook(list[1], list[2]));
    }
    if(action == "ChangeUser")
    {
        PassDataTosend(changeUserInfo(list[1]));
    }
    if(action == "deleteUser")
    {
        PassDataTosend(deleteUser(list[1],list[2]));
    }
    if(action == "CreateAccountUser")
    {
        PassDataTosend(creatingAccountUser(list[1], list[2],list[3], list[4], list[5]));
    }
    if(action == "ReleaseMoney")
    {
       PassDataTosend(releasingMoneyAuth(list[1], list[2],list[3], list[4], list[5], list[6]));
    }
    if(action == "DieCode")
    {
        PassDataTosend(expiringcode(list[1]));
    }
    if(action == "addpicture")
    {
        qDebug()<<list[1]<<list.last();
        PassDataTosend(addingprofilepicture(list[1],list.last()));
    }

}

void mytask::run()
{
    qDebug()<<"Task has started.....";

    // to processing request
       TaskGivenFile();
       DecisionPath();

       // after processing request and sending feedback

      QByteArray data = Sending();
       qDebug()<<"Task done....";
       qDebug()<<"Sending result......";
       emit Result(data);
}
