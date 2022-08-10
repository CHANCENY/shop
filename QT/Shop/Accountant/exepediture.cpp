#include "exepediture.h"
#include "ui_exepediture.h"
#include <QMessageBox>

QString fullname = nullptr;
Exepediture::Exepediture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exepediture)
{
    ui->setupUi(this);

    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");

    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        fullname = in.readAll();
        myfile.close();

    }
}

Exepediture::~Exepediture()
{
    delete ui;
}

bool Exepediture::checkcode(QString code)
{
    QString exp = nullptr;
    QString verified = nullptr;
   if(releasemoneycon())
   {
       QSqlQuery query;
       qDebug()<<"code 1";
       query.prepare("SELECT * FROM Rmoney WHERE code ='"+code+"';");
       if(query.exec())
       {
            qDebug()<<"code 2";
           while(query.next())
           {
               verified = query.value(1).toString();
               exp = query.value(5).toString();
           }

            qDebug()<<"code 3"<<verified<<exp;
       }

       if(verified == "0" && exp == "false")
       {
            qDebug()<<"code 4";
           query.prepare("UPDATE Rmoney SET verified ='1', exp='true' WHERE code='"+code+"';");
           if(query.exec())
           {
               return true;
           }
       }
   }

   return false;
}

bool Exepediture::accountcheck(QString password)
{
    if(savedusercon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM log WHERE password='"+password+"';");
        if(query.exec())
        {
            QString line = nullptr;
            while(query.next())
            {
                line = query.value(1).toString();
            }

            if(line == password)
            {
                return true;
            }
        }
    }
    return false;
}

void Exepediture::releaseMoney(QString amount, QString code, QString  desc)
{
    QString line = "expediture,"+amount+"@"+code+"@"+desc+"@"+fullname;
    QByteArray data;
    data = line.toLocal8Bit();
    socketing.SendingToServer(data);
    QTimer::singleShot(1000,this,SLOT(resultexp()));

}

void Exepediture::resultexp()
{
    QDir dir2;
    QString line = nullptr;
    QString filenames = dir2.absoluteFilePath("RECEIVEDDATA");
    QFile myfile1(filenames);
    myfile1.open(QIODevice::ReadOnly);
    if(myfile1.isOpen())
    {
        QTextStream in(&myfile1);
        line = in.readAll();
        myfile1.close();
    }

    if(line != "none")
    {
        ui->amount->setText(nullptr);
        ui->code->setText(nullptr);
        ui->password->setText(nullptr);
        ui->descp->clear();
        QMessageBox::information(this,"Message",line);
    }
    else
    {
         QMessageBox::warning(this,"warning","Releasing money failed due to funds problems");
    }
}

void Exepediture::on_pushButton_clicked()
{
    QString amount = ui->amount->text();
    QString code = ui->code->text();
    QString password = ui->password->text();
    QString desc = ui->descp->toPlainText();

    if(amount != nullptr && code != nullptr && password != nullptr && desc != nullptr)
    {
      if(accountcheck(password))
      {
        if(checkcode(code))
        {
           releaseMoney(amount,code,desc);
        }
        else
        {
           QMessageBox::warning(this,"warning","Check your code is wrong!");
        }
      }
      else
      {
          QMessageBox::warning(this,"warning","Check your password is wrong!");
      }
    }
}

