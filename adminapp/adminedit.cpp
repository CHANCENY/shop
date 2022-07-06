#include "adminedit.h"
#include "ui_adminedit.h"
#include <QMessageBox>


QString usernamefound,namefound, photofound;

static int lock = 0;

adminedit::adminedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminedit)
{
    ui->setupUi(this);
}

adminedit::~adminedit()
{
    delete ui;
}

void adminedit::result()
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

    if(line == "true" && lock == 1)
    {
        ui->messages->setText("User information changed!");
    }
    else if(line == "true" && lock == 2)
    {
       if(employdbcon())
       {
           QSqlQuery query;
           query.prepare("DELETE FROM employees WHERE username = '"+usernamefound+"';");
           if(query.exec())
           {
                ui->messages->setText("User has been deleted!");
           }
       }
    }
    else
    {
        QMessageBox::warning(this,"Network error",sock.errorString());
    }

}

void adminedit::on_selectphoto_clicked()
{
  QString photo = QFileDialog::getOpenFileName(this,"CHOOSE PHOTO",QDir::homePath(),"*.jpg *.jpeg *.png");
  if(photo != nullptr)
  {
      photofound = photo;
      QStringList list = photo.split('/');
      ui->image->setText(list.last());
  }
}


void adminedit::on_username_textChanged(const QString &arg1)
{
    usernamefound = arg1;
   if(arg1 != nullptr)
   {
       if(employdbcon())
       {
           QSqlQuery query;
           query.prepare("SELECT * FROM employees WHERE username ='"+arg1+"';");
           if(query.exec())
           {
               while(query.next())
               {
                   namefound = query.value(0).toString();
                   usernamefound = query.value(1).toString();
                   ui->name->setText(query.value(0).toString());
                   ui->username->setText(query.value(1).toString());
                   ui->title->setCurrentText(query.value(2).toString());
                   ui->password1->setText(query.value(3).toString());
                   ui->password2->setText(query.value(3).toString());
                   photofound = query.value(4).toString();
                   QStringList list = photofound.split('/');
                   ui->image->setText(list.last());
               }
           }

       }
   }
}


void adminedit::on_name_textChanged(const QString &arg1)
{
    namefound = arg1;
   if(arg1 != nullptr)
   {
       if(employdbcon())
       {
           QSqlQuery query;
           query.prepare("SELECT * FROM employees WHERE name ='"+arg1+"';");
           if(query.exec())
           {
               while(query.next())
               {
                   namefound = query.value(0).toString();
                   usernamefound = query.value(1).toString();
                   ui->name->setText(query.value(0).toString());
                   ui->username->setText(query.value(1).toString());
                   ui->title->setCurrentText(query.value(2).toString());
                   ui->password1->setText(query.value(3).toString());
                   ui->password2->setText(query.value(3).toString());
                   photofound = query.value(4).toString();
                   QStringList list = photofound.split('/');
                   ui->image->setText(list.last());
               }
           }

       }
   }
}


void adminedit::on_commitchange_clicked()
{
    QString title = ui->title->currentText();
    QString fullname = ui->name->text();
    QString username = ui->username->text();
    QString pass1 = ui->password1->text();
    QString pass2 = ui->password2->text();

    if(pass1 == pass2)
    {
       if(title != nullptr && fullname != nullptr && username != nullptr && pass1 != nullptr && pass2 != nullptr)
       {
           if(usernamefound == username)
           {
               QString line ="ChangeUser,"+fullname+"@"+username+"@"+title+"@"+pass1+"@"+photofound;
               QByteArray data;
               data.append(line.toStdString());
               sock.SendingToServer(data);
               lock = 1;
               QTimer::singleShot(1000,this,SLOT(result()));
           }
           else
           {
               QMessageBox::warning(this,"Username invalid","It looks like you have changed username (username cant be changed!)");
           }
       }
    }
    else
    {
        QMessageBox::warning(this,"warning","passwords dont match!");
    }
}


void adminedit::on_pushButton_3_clicked()
{
    QString title = ui->title->currentText();
    QString fullname = ui->name->text();
    QString username = ui->username->text();
    QString pass1 = ui->password1->text();
    QString pass2 = ui->password2->text();

    if(pass1 == pass2)
    {
       if(title != nullptr && fullname != nullptr && username != nullptr && pass1 != nullptr && pass2 != nullptr)
       {
           if(usernamefound == username)
           {

               QString line ="deleteUser,"+username+","+pass1;
               QByteArray data;
               data.append(line.toStdString());
               sock.SendingToServer(data);
               lock = 2;
               QTimer::singleShot(1000,this,SLOT(result()));
           }
           else
           {
               QMessageBox::warning(this,"Username invalid","It looks like you have changed username (username cant be changed!)");
           }
       }
    }
    else
    {
        QMessageBox::warning(this,"warning","passwords dont match!");
    }
}

