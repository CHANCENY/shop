#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QTimer>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::clearuser(QString line)
{

    if(line != nullptr)
    {
        QDir dir;
        QString datain = nullptr;

        QString filename = dir.absoluteFilePath("TEMP");
        QFile myfile(filename);
        myfile.open(QIODevice::WriteOnly);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);
           in<<line;
           myfile.flush();
            myfile.close();
        }
    }
    else
    {
        QDir dir;
        QString datain = nullptr;

        QString filename = dir.absoluteFilePath("RECEIVEDDATA");
        QFile myfile(filename);
        myfile.open(QIODevice::WriteOnly);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);
           in<<"";
           myfile.flush();
            myfile.close();
        }
    }

}

void login::validateuser()
{
    QDir dir;
    QString datain = nullptr;

    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        datain = in.readAll();
        myfile.close();
    }

    if(datain != nullptr)
    {
        QStringList list = datain.split(',');

        if(list[0] == "true")
        {
            clearuser(list[1]);
            clearuser("");
            qDebug()<<"you have logged in";
            admin = new Adminpage(this);
            admin->show();
        }
        else
        {
           QMessageBox::warning(this,"warning alert","You have entered wrong input (this page is for afmin only)");
        }
    }
}


void login::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if(username != nullptr && password != nullptr)
    {
       std::string user = username.toStdString();
       std::string pass = password.toStdString();
       std::string line = "AdminLogin,"+user+","+pass;

       QByteArray data;
       data.append(line);

       socket.SendingToServer(data);
       QTimer::singleShot(1000,this,SLOT(validateuser()));
    }
    else
    {
        QMessageBox::warning(this,"warning alert","Please fill in all fields");
    }
}


void login::on_lineEdit_2_returnPressed()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if(username != nullptr && password != nullptr)
    {
       std::string user = username.toStdString();
       std::string pass = password.toStdString();
       std::string line = "AdminLogin,"+user+","+pass;

       QByteArray data;
       data.append(line);

       socket.SendingToServer(data);
       QTimer::singleShot(1000,this,SLOT(validateuser()));
    }
    else
    {
        QMessageBox::warning(this,"warning alert","Please fill in all fields");
    }
}

