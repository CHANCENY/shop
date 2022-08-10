#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QTimer>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::logInNow(QString username, QString passwrd)
{

    if(username != nullptr && passwrd != nullptr)
    {
        QByteArray user;
        user.append("login,");
        user.append(username.toStdString());
        user.append(","+passwrd.toStdString());
        socket.SendingToServer(user);

    }


}

void Login::saveduserfound(QString line)
{
    QDir dir;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        in<<"";
        myfile.flush();
        myfile.close();
    }

    QDir dir2;

    QString filenames = dir2.absoluteFilePath("SAVEDUSER");
    QFile myfile1(filenames);
    myfile1.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile1.isOpen())
    {
        QTextStream in(&myfile1);
        in<<line;
        myfile1.flush();
        myfile1.close();
    }


}

void Login::readfile()
{
    QDir dir;
    QByteArray d ;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        d = in.readAll().toLocal8Bit();
        myfile.flush();
        myfile.close();
    }

    if(!d.isEmpty())
    {
        std::string line = d.toStdString();
        QString info = QString::fromStdString(line);
        QStringList list = info.split(',');

        if(list[0] == "true")
        {
            saveduserfound(info);
            teller = new TellerHome(this);
            teller->show();
        }
        else
        {
           QMessageBox::warning(this,"warning","You have enter wrong input note this is for teller's only");
        }
    }
}


void Login::on_pushButton_clicked()
{
    QString user = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
     saveuser(user,pass);
     logInNow(user,pass);
     QTimer::singleShot(2000,this, SLOT(readfile()));
}


void Login::on_lineEdit_2_returnPressed()
{
    QString user = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    saveuser(user,pass);
     logInNow(user,pass);
     QTimer::singleShot(2000,this, SLOT(readfile()));
}

void Login::saveuser(QString username, QString password)
{
    if(saverusercon())
    {
        QString line = nullptr;
        QSqlQuery query;
        query.prepare("SELECT * FROM log WHERE username ='"+username+"';");
        if(query.exec())
        {
         while(query.next())
         {
             line = query.value(0).toString();
         }
        }

        if(line == nullptr)
        {
            query.prepare("INSERT INTO log VALUES('"+username+"','"+password+"','none');");
            query.exec();
        }
        else
        {
            query.prepare("UPDATE log SET username ='"+username+"' password ='"+password+"' WHERE username ='"+username+"';");
            query.exec();
        }
    }
}
