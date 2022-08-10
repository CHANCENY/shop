#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QTimer>


QString locktime = nullptr;

QTimer *timerlock;

static  int lock = 4;

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);


    ui->message->setVisible(false);

    timerlock = new QTimer(this);

    QDir dir;
    QString locks = nullptr;

    QString filename = dir.absoluteFilePath("lock");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        locks = in.readAll();
        myfile.close();
    }

    if(locks == "1")
    {

        QDateTime t = QDateTime::currentDateTime();
        QString time = t.toString("h:m");

       // int hour = time.split(':')[0].toInt() + 1;

       // locktime = QString::number(hour)+":"+time.split(':').last();
          locktime = time.split(':')[0]+":"+QString::number(time.split(':').last().toInt() + 2);

        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton->setEnabled(false);

        ui->pushButton->setVisible(false);
        ui->message->setVisible(true);

        connect(timerlock,SIGNAL(timeout()),this,SLOT(lockTimer()));
        timerlock->start(1000);
    }



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
           lock--;
           QMessageBox::warning(this,"warning alert","Invalid input (this page is for admin only) attempts left "+QString::number(lock));
           if(lock == 0)
           {
               QFile myfile("lock");
               myfile.open(QIODevice::WriteOnly|QFile::Text);
               if(myfile.isOpen())
               {
                   QTextStream in(&myfile);
                   in<<"1";
                   myfile.flush();
                   myfile.close();

                   QDateTime t = QDateTime::currentDateTime();
                   QString time = t.toString("h:m");

                  // int hour = time.split(':')[0].toInt() + 1;

                  // locktime = QString::number(hour)+":"+time.split(':').last();
                     locktime = time.split(':')[0]+":"+QString::number(time.split(':').last().toInt() + 2);


                   ui->lineEdit->setEnabled(false);
                   ui->lineEdit_2->setEnabled(false);
                   ui->pushButton->setEnabled(false);

                   ui->pushButton->setVisible(false);
                   ui->message->setVisible(true);

                   connect(timerlock,SIGNAL(timeout()),this,SLOT(lockTimer()));
                   timerlock->start(1000);
               }
           }

        }
    }
}

void login::lockTimer()
{
    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString("h:m");

    if(locktime == time)
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton->setVisible(true);
        ui->message->setVisible(false);
        lock = 4;
        timerlock->stop();

        QFile myfile("lock");
        myfile.open(QIODevice::WriteOnly|QFile::Text);
        if(myfile.isOpen())
        {
            QTextStream in(&myfile);
            in<<"0";
            myfile.flush();
            myfile.close();
        }
    }
    else
    {
      ui->message->setText("Exhusted chances unlock in "+locktime);
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

