#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QTimer>



static int lock = 4;
QString locktime = nullptr;

QTimer *locktimes;

 QString username = nullptr;
 QString password = nullptr;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->messages->setVisible(false);
    locktimes = new QTimer(this);

    QDir dir;
    QString filename = dir.absoluteFilePath("LOCK");
    QFile myfile(filename);

    QString line = nullptr;

    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        line = in.readAll();
        myfile.close();

        if(line == "1")
        {
            QDateTime t = QDateTime::currentDateTime();
            QString time = t.toString("h:m");

            locktime = time.split(':')[0]+":"+QString::number(time.split(':').last().toInt() + 5);

            connect(locktimes,SIGNAL(timeout()),this,SLOT(lockingTimer()));
            locktimes->start(1000);
        }
    }


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
          writeLock(username);

          accountpage = new Accountant(this);
          accountpage->show();
      }
      else
      {
          lock--;
         QMessageBox::warning(this,"warning","Invalid Input (this is accountant login page only) attempts left "+QString::number(lock));

         if(lock == 0)
         {
             QDateTime t = QDateTime::currentDateTime();
             QString time = t.toString("h:m");

             this->writeLock("1");

             locktime = time.split(':')[0]+":"+QString::number(time.split(':').last().toInt() + 5);
             ui->pushButton->setEnabled(false);
             connect(locktimes,SIGNAL(timeout()),this,SLOT(lockingTimer()));
             locktimes->start(1000);
         }
      }
  }
}

void Login::lockingTimer()
{

    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString("h:m");

    if(time == locktime)
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton->setVisible(true);
        ui->messages->setVisible(false);
        lock = 4;
        this->writeLock("0");
    }
    else
    {
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton->setVisible(false);
        ui->messages->setVisible(true);
        ui->messages->setText("Blocked unlocking in "+locktime);
    }

}

void Login::saveuser(QString username, QString password)
{


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

void Login::writeLock(QString lock)
{
    QDir dir;
    QString filename = dir.absoluteFilePath("LOCK");

    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
       in<<lock;
        myfile.close();
    }
}

void Login::on_pushButton_clicked()
{
    username = ui->lineEdit->text();
    password = ui->lineEdit_2->text();


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
    username = ui->lineEdit->text();
    password = ui->lineEdit_2->text();

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

