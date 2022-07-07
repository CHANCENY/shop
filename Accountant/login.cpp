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

void Login::validateaccountant()
{
  QDir dir;
  QString filename = dir.absoluteFilePath("RECEIVEDDATA");
  QFile myfile(filename);

  QString line = nullptr;

  myfile.open(QIODevice::ReadOnly);
  if(myfile.isOpen())
  {
      QTextStream in(&myfile);
      line = in.readAll();
      myfile.close();
  }

  if(line != nullptr)
  {
      QStringList list = line.split(',');
      qDebug()<<"here: ->"<<list;

      if(list[0] == "true")
      {

          accountpage = new Accountant(this);
          accountpage->show();
      }
      else
      {
         QMessageBox::warning(this,"warning","You have entered wrong input (this is accountant login page only)");
      }
  }
}

void Login::saveuser(QString username, QString password)
{

   qDebug()<<"hello "<<username<<" and "<<password;
  if(savedusercon())
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
          query.prepare("INSERT INTO log VALUES('"+username+"','"+password+"');");
          query.exec();
      }
      else
      {
          query.prepare("UPDATE log SET username ='"+username+"' password ='"+password+"' WHERE username ='"+username+"';");
          query.exec();
      }
  }
}

void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if(username != nullptr && password != nullptr)
    {
         std::string user =  username.toStdString();
         std::string pass = password.toStdString();
         std::string line ="Alogin,"+user+","+pass;
         saveuser(username,password);
         QByteArray data;
         data.append(line);
        socket.SendingToServer(data);
        QTimer::singleShot(1000,this,SLOT(validateaccountant()));
    }
}


void Login::on_lineEdit_2_returnPressed()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if(username != nullptr && password != nullptr)
    {
         std::string user =  username.toStdString();
         std::string pass = password.toStdString();
         std::string line ="Alogin,"+user+","+pass;
          saveuser(username,password);
         QByteArray data;
         data.append(line);
        socket.SendingToServer(data);
        QTimer::singleShot(1000,this,SLOT(validateaccountant()));
    }
}

