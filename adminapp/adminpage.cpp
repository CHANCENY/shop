#include "adminpage.h"
#include "ui_adminpage.h"
#include <QTimer>
#include <QtSql>
#include <QMessageBox>
#include <QRandomGenerator>



QString name = nullptr;
QString username = nullptr;
QString title = nullptr;
QString amountreleased = nullptr;

QTimer *checkbooktimer;

QString expiretime = nullptr;
QString codemade = nullptr;

Adminpage::Adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Adminpage)
{
    ui->setupUi(this);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton_5->setText("Withdraw");
    admininfo();
    getEmployeesUpdateFromServer();
    checkBookIfExist();



    QTimer *timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(getEmployeesUpdateFromServer()));
    timer->start(30000);

    checkbooktimer = new QTimer(this);
}

Adminpage::~Adminpage()
{
    delete ui;
}

void Adminpage::admininfo()
{
    QDir dir;
    QString datain = nullptr;

    QString filename = dir.absoluteFilePath("TEMP");
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
        QStringList list = datain.split('@');

        QPixmap profile(list.last());
        ui->profile->setPixmap(profile);

        name = list[0];
        username = list[1];
        title = list[2];

    }
}

void Adminpage::checkBookIfExist()
{
  if(bookcon())
  {
      QSqlQuery query;
      query.prepare("SELECT * FROM book;");
      if(query.exec())
      {
          QString lines = nullptr;
          while(query.next())
          {
              lines = query.value(0).toString();
          }

          if(lines != nullptr)
          {
              ui->groupBox_2->setVisible(true);
              ui->groupBox_3->setVisible(true);
              ui->searchresulttable->setVisible(true);
              ui->bookbutton->setVisible(false);
             // checkbooktimer->stop();

          }
          else
          {
              ui->groupBox_2->setVisible(false);
              ui->groupBox_3->setVisible(false);
              ui->searchresulttable->setVisible(false);
              ui->bookbutton->setVisible(true);

          }
      }
  }
}

QString Adminpage::generateCode()
{
    here:
  QString code = nullptr;

  for(int i = 0; i < 5; i++)
  {
      code += QString::number(QRandomGenerator::global()->bounded(100, 999));
  }

  if(releasMoneycon())
  {
      QSqlQuery query;
      query.prepare("SELECT * FROM Rmoney WHERE code='"+code+"';");
      if(query.exec())
      {
          while(query.next())
          {
              if(query.value(0).toString() == code)
              {
                  goto here;
              }

          }
      }
  }

  return code;

}

void Adminpage::getEmployeesUpdateFromServer()
{
   QString line = "employees,SELECT * FROM employees;";
   std::string lines = line.toStdString();
   QByteArray data;
   data.append(lines);


   sock.SendingToServer(data);
   QTimer::singleShot(1000,this,SLOT(localupdateemployees()));
}

void Adminpage::localupdateemployees()
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

           if(line != nullptr)
           {
               QStringList allinfo = line.split('#');
               QStringList rows = allinfo[0].split(';');
               int sizes = rows.size();

               if(employdbcon())
               {
                   for(int i =0; i < sizes - 1; i++)
                   {
                       QStringList col = rows[i].split('@');

                       QSqlQuery query;
                       query.prepare("DELETE FROM employees WHERE username='"+col[1]+"';");
                       if(query.exec())
                       {
                           continue;
                       }
                       else
                       {
                           break;
                       }

                   }

                   for(int i = 0; i < sizes -1; i++)
                   {
                       QStringList col = rows[i].split('@');

                       QSqlQuery query;
                       query.prepare("INSERT INTO employees(name,username,title,password,photo) VALUES('"+col[0]+"','"+col[1]+"','"+col[2]+"','"+col[3]+"','"+col[4]+"');");
                       if(query.exec())
                       {
                           continue;
                       }
                   }
               }


               QString bank = allinfo[1];

               if(bank != nullptr)
               {
                   QStringList book = bank.split('@');

                   if(bookcon())
                   {
                       QSqlQuery query;

                       QString line = nullptr;
                       query.prepare("SELECT * FROM book WHERE booknumber='"+book[2]+"';");
                       if(query.exec())
                       {
                           while(query.next())
                           {
                               line = query.value(0).toString();
                           }
                       }

                       if(line == nullptr)
                       {
                           query.prepare("INSERT INTO book VALUES('"+book[0]+"','"+book[1]+"','"+book[2]+"');");
                           query.exec();
                       }
                       else
                       {
                           query.prepare("UPDATE book SET bookname='"+book[0]+"' bookbalance='"+book[1]+"' booknumber='"+book[2]+"' WHERE booknumber='"+book[2]+"';");
                           query.exec();
                       }
                   }
               }




               QStringList rowss = allinfo[2].split(';');
               int sizess = rowss.size();

               if(releasMoneycon())
               {
                   for(int i =0; i < sizess - 1; i++)
                   {
                       QStringList col = rowss[i].split('@');

                       QSqlQuery query;
                       query.prepare("DELETE FROM Rmoney WHERE code='"+col[0]+"';");
                       if(query.exec())
                       {
                           continue;
                       }
                       else
                       {
                           break;
                       }

                   }

                   for(int i = 0; i < sizess -1; i++)
                   {
                       QStringList col = rowss[i].split('@');

                       QSqlQuery query;
                       query.prepare("INSERT INTO Rmoney(code,verified,amount,description,expire,exp,ReleasedBy,ExpectedAmount,AdminAuth) VALUES('"+col[0]+"','"+col[1]+"','"+col[2]+"','"+col[3]+"','"+col[4]+"','"+col[5]+"','"+col[6]+"','"+col[7]+"','"+col[8]+"');");
                       if(query.exec())
                       {
                           continue;
                       }
                   }
               }
           }
}

void Adminpage::bookMakerResponse()
{

    if(bookcon())
    {
        QString line = nullptr;
        QSqlQuery query;
        query.prepare("SELECT * FROM book;");
        if(query.exec())
        {
            while(query.next())
            {
                line = query.value(0).toString();
            }
        }

        if(line != nullptr)
        {
            ui->groupBox_2->setVisible(true);
            ui->groupBox_3->setVisible(true);
            ui->searchresulttable->setVisible(true);
            ui->bookbutton->setVisible(false);
            checkbooktimer->stop();
        }
        else
        {
            ui->groupBox_2->setVisible(false);
            ui->groupBox_3->setVisible(false);
            ui->searchresulttable->setVisible(false);
            ui->bookbutton->setVisible(true);
        }
    }
}

void Adminpage::countingExpire()
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

    if(line == "true")
    {
       checkbooktimer = new QTimer(this);
       connect(checkbooktimer,SIGNAL(timeout()),this,SLOT(timing()));
       checkbooktimer->start(1000);
    }
}

void Adminpage::timing()
{
    QDateTime t = QDateTime::currentDateTime();
    QString time = t.toString("h:m");

     ui->expiremessage->setText("Time: "+time+" Expiring: "+expiretime);

    if(time == expiretime)
    {
        if(releasMoneycon())
        {
            QString verified = nullptr;
            QSqlQuery query;
            query.prepare("SELECT * FROM Rmoney WHERE code ='"+codemade+"';");
            if(query.exec())
            {
                while(query.next())
                {
                   verified = query.value(1).toString();
                }
            }


            if(verified == "0")
            {
                QString line = "UPDATE Rmoney SET verified ='1'@ exp = 'true' WHERE code ='"+codemade+"';";
                QString line2 = "DieCode,"+line;
                QByteArray data; data.append(line2.toStdString());
                sock.SendingToServer(data);
               ui->expiremessage->setText("Time: "+time+" Expiring: "+expiretime+" has expired unsed");
               checkbooktimer->stop();

            }
            else
            {
                 ui->expiremessage->setText("Time: "+time+" Expiring: "+expiretime+" has expired used");
                 checkbooktimer->stop();
            }
        }
    }
}

void Adminpage::on_bookbutton_clicked()
{
  // make account book

    book = new bookmaker(this);
    book->show();

    connect(checkbooktimer,SIGNAL(timeout()),this,SLOT(bookMakerResponse()));
    checkbooktimer->start(1000);

}

void Adminpage::on_pushButton_4_clicked()
{
    QString search = ui->lineEdit->text();

    if(search != nullptr)
    {
        if(employdbcon())
        {
            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery *query1 = new QSqlQuery(mydb);
            query1->prepare("SELECT * FROM employees WHERE username = '"+search+"';");
            if(query1->exec())
              {

                model->setQuery(*query1);
                ui->searchresulttable->setModel(model);
              }

        }
    }
}


void Adminpage::on_pushButton_clicked()
{
    if(employdbcon())
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *query1 = new QSqlQuery(mydb);
        query1->prepare("SELECT * FROM employees;");
        if(query1->exec())
          {

            model->setQuery(*query1);
            ui->searchresulttable->setModel(model);
          }

    }
}


void Adminpage::on_searchresulttable_clicked(const QModelIndex &index)
{
    QString texts = ui->searchresulttable->model()->data(index).toString();
    QStringList list = {"Name","Username","Title","Password","Profile"};
    int col = ui->searchresulttable->currentIndex().column();
    QMessageBox::information(this,list[col],texts);
}


void Adminpage::on_lineEdit_returnPressed()
{
    QString search = ui->lineEdit->text();

    if(search != nullptr)
    {
        if(employdbcon())
        {
            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery *query1 = new QSqlQuery(mydb);
            query1->prepare("SELECT * FROM employees WHERE username = '"+search+"';");
            if(query1->exec())
              {

                model->setQuery(*query1);
                ui->searchresulttable->setModel(model);
              }

        }
    }
}


void Adminpage::on_pushButton_2_clicked()
{
    edit = new adminedit(this);
    edit->show();
}


void Adminpage::on_pushButton_3_clicked()
{
    employer = new newEmployees(this);
    employer->show();
}


void Adminpage::on_pushButton_5_clicked()
{
    codemade = nullptr;
    expiretime = nullptr;

    if(ui->pushButton_5->text() == "Withdraw")
    {
         ui->lineEdit_2->setVisible(true);
         ui->pushButton_5->setVisible(false);
    }

    else if(ui->pushButton_5->text() == "Code")
    {
        if(amountreleased != nullptr)
        {
            QString code = generateCode();
            if(code != nullptr)
            {
                QDateTime t = QDateTime::currentDateTime();
                QString time = t.toString("h:m");


                int hour = time.split(':')[0].toInt() + 2;

                expiretime = QString::number(hour)+":"+time.split(':').last();
                //expiretime = time.split(':')[0]+":"+QString::number(hour);

                QString line = "ReleaseMoney,"+code+",0,"+expiretime+","+"false"+","+amountreleased+","+name;

                codemade = code;
                QByteArray data; data.append(line.toStdString());
                sock.SendingToServer(data);
                QTimer::singleShot(1000,this,SLOT(countingExpire()));

            }
        }

    }

}


void Adminpage::on_lineEdit_2_returnPressed()
{
  QString amount = ui->lineEdit_2->text();
  if(amount != nullptr)
  {
      amountreleased = amount;
      ui->lineEdit_2->setVisible(false);
      ui->pushButton_5->setVisible(true);
      ui->pushButton_5->setText("Code");
  }
}

