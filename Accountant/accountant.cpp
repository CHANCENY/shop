#include "accountant.h"
#include "ui_accountant.h"
#include <QStringList>
#include <QDate>
#include <QTimer>
#include <QVector>

QTimer *check;

Accountant::Accountant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Accountant)
{
    ui->setupUi(this);
    setAccountantInfo();

    accountbook();

     check = new QTimer(this);
     connect(check,SIGNAL(timeout()),this,SLOT(findinghighsoldandless()));
     connect(check,SIGNAL(timeout()),this,SLOT(accountbook()));
     connect(check,SIGNAL(timeout()),this,SLOT(rating()));
     check->start(10000);

     QTimer *timer2 = new QTimer(this);
     connect(timer2,SIGNAL(timeout()),this,SLOT(updateFroServerForItems()));
     timer2->start(30000);

}

Accountant::~Accountant()
{
    delete ui;
}

void Accountant::setAccountantInfo()
{
  QDir dir;
  QString filename = dir.absoluteFilePath("RECEIVEDDATA");

  QFile myfile(filename);
  myfile.open(QIODevice::ReadOnly);
  if(myfile.isOpen())
  {
      QTextStream in(&myfile);
      QString line = in.readAll();

      if(line != nullptr)
      {
          QStringList info = line.split(',');
          ui->fullname->setText(info.at(1));

          QPixmap pro(info.last());
          ui->profile->setPixmap(pro);

          QDate date = QDate::currentDate();
          QString dates = date.toString("dd-MM-yy");

          ui->datesplace->setText(dates);



      }
  }
}

void Accountant::checkmonthlyrate()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList list = dates.split('-');
    QString firstday = "01-"+list.at(1)+"-"+list.last();
    QString lastday = "28-"+list.at(1)+"-"+list.last();

    QStringList prices;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE datesold BETWEEN '"+firstday+"' AND '"+lastday+"' AND SoldStatus ='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
               prices.append(query.value(8).toString());
            }
        }
    }

   int totals = 0;
   int sizes = prices.size();

   for(int i = 0; i < sizes; i++)
   {
       totals = totals + prices[i].toInt() / sizes;
   }
  int pernce = totals / 100;

  ui->monthy->setValue(pernce);

}

void Accountant::checktwoweeks()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList list = dates.split('-');

    int ago = list[0].toInt() - 14;

    if(ago < 0)
    {
        ago = 01;
    }

    QString firstday = QString::number(ago)+"-"+list.at(1)+"-"+list.last();


    QStringList prices;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE datesold BETWEEN '"+firstday+"' AND '"+dates+"' AND SoldStatus ='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
               prices.append(query.value(8).toString());
            }
        }
    }

   int totals = 0;
   int sizes = prices.size();

   for(int i = 0; i < sizes; i++)
   {
       totals = totals + prices[i].toInt() / sizes;
   }
  int pernce = totals / 100;

  ui->twoweeks->setValue(pernce);
}

void Accountant::checkweek()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList list = dates.split('-');

    int ago = list[0].toInt() - 7;

    if(ago < 0)
    {
        ago = 01;
    }

    QString firstday = QString::number(ago)+"-"+list.at(1)+"-"+list.last();

   qDebug()<<firstday;
    QStringList prices;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE datesold BETWEEN '"+firstday+"' AND '"+dates+"' AND SoldStatus ='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
               prices.append(query.value(8).toString());
            }
        }
    }

   int totals = 0;
   int sizes = prices.size();

   for(int i = 0; i < sizes; i++)
   {
       totals = totals + prices[i].toInt() / sizes;
   }
  int pernce = totals / 100;

  ui->weekly->setValue(pernce);
}

void Accountant::checktody()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList prices;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE datesold BETWEEN '"+dates+"' AND '"+dates+"' AND SoldStatus ='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
               prices.append(query.value(8).toString());
            }
        }
    }

   int totals = 0;
   int sizes = prices.size();

   for(int i = 0; i < sizes; i++)
   {
       totals = totals + prices[i].toInt() / sizes;
   }
  int pernce = totals / 100;

  ui->todays->setValue(pernce);
}

void Accountant::accountbook()
{
  if(bookcon())
  {
      QSqlQuery query;
      query.prepare("SELECT * FROM book;");
      if(query.exec())
      {
          while(query.next())
          {
              ui->accountname->setText(query.value(0).toString());
              ui->balancelabel->setText(query.value(1).toString());
          }
      }
  }
}

void Accountant::findinghighsoldandless()
{
  if(itemdbcon())
  {
      QStringList names, prices;
      QSqlQuery query;
      query.prepare("SELECT * FROM items WHERE SoldStatus ='Sold';");
      if(query.exec())
      {
        while(query.next())
        {
           names.append(query.value(0).toString());
           prices.append(query.value(8).toString());
        }
      }

      if(names.size() > 0)
      {
          int low = prices.at(0).toInt();
          int high = prices.at(0).toInt();
          int medium = 0;

          QString hname = names.at(0);
          QString lname = names.at(0);
          QString mname = nullptr;

          int sizes = names.size();

          for(int i = 0; i < sizes; i++)
          {
             if(high < prices[i].toInt())
             {
                high = prices[i].toInt();
                hname = names[i];
             }
             else if(prices[i].toInt() < low)
             {
                 low = prices[i].toInt();
                 lname = names[i];
             }
          }

          for(int i =0; i < sizes; i++)
          {
              if(prices[i].toInt() > low && prices[i].toInt() < high && prices[i].toInt() > medium)
              {
                  medium = prices[i].toInt();
                  mname = names[i];
              }
          }

          ui->hname->setText(hname);
          ui->mname->setText(mname);
          ui->lname->setText(lname);
          ui->priceh->setText(QString::number(high));
          ui->pricem->setText(QString::number(medium));
          ui->pricel->setText(QString::number(low));

          int qh =0,qm = 0, ql = 0;
          for(int i = 0; i < sizes; i++)
          {
              if(names[i] == hname)
              {
                  qh = qh + 1;
              }
              if(names[i] == mname)
              {
                  qm = qm + 1;
              }
              if(names[i] == lname)
              {
                  ql = ql + 1;
              }
          }

          ui->qhunumber->setText(QString::number(qh));
          ui->qmnumber->setText(QString::number(qm));
          ui->qlnumber->setText(QString::number(ql));


      }
  }
}

void Accountant::rating()
{
  checkmonthlyrate();
  checktwoweeks();
  checkweek();
  checktody();
}

void Accountant::updateFroServerForItems()
{
    std::string query = "SELECT * FROM items;";
    QByteArray data;
    data.append("ALLITEMS,"+query);
    socket.SendingToServer(data);
    QTimer::singleShot(1000,this,SLOT(itemupdatelocal()));
}

void Accountant::itemupdatelocal()
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

            if(itemdbcon())
            {
                for(int i =0; i < sizes - 1; i++)
                {
                    QStringList col = rows[i].split('@');

                    QSqlQuery query;
                    query.prepare("DELETE FROM items WHERE barcode='"+col[2]+"';");
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
                    query.prepare("INSERT INTO items(name,price,barcode,groups,description,SoldStatus,offer,datesold,soldprice) VALUES('"+col[0]+"','"+col[1]+"','"+col[2]+"','"+col[3]+"','"+col[4]+"','"+col[5]+"','"+col[6]+"','"+col[7]+"','"+col[8]+"');");
                    if(query.exec())
                    {
                        continue;
                    }
                }
            }

           QStringList bank = allinfo[1].split('@');
           qDebug()<<"bank ->"<<bank;

           if(bookcon())
           {
               QSqlQuery query;
               QString lin = nullptr;

                   query.prepare("SELECT * FROM book WHERE booknumber='"+bank[2]+"';");
                   if(query.exec())
                   {

                       while(query.next())
                       {
                          lin = query.value(2).toString();
                       }
                   }

                   if(lin == nullptr)
                   {
                     query.prepare("INSERT INTO book VALUES('"+bank[0]+"','"+bank[1]+"','"+bank[2]+"');");
                     query.exec();
                   }
                   else
                   {
                       query.prepare("UPDATE book SET bookbalance ='"+bank[1]+"' WHERE booknumber='"+bank[2]+"';");
                       query.exec();
                   }
           }




           QStringList rowss = allinfo[2].split(';');
           int sizess = rowss.size();
           qDebug()<<"Rmoney "<<rowss;

           if(releasemoneycon())
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
                   query.prepare("INSERT INTO Rmoney(code,verified,amount,description,expire,exp,ReleasedBy,ExpectedAmount,AdminAuth,Date) VALUES('"+col[0]+"','"+col[1]+"','"+col[2]+"','"+col[3]+"','"+col[4]+"','"+col[5]+"','"+col[6]+"','"+col[7]+"','"+col[8]+"','"+col[9]+"');");
                   if(query.exec())
                   {
                       continue;
                   }
               }
           }


        }

}

void Accountant::on_todaybutton_4_clicked()
{
    stock = new Stockwindow(this);
    stock->show();

}

void Accountant::on_todaybutton_clicked()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);
        out<<"today";
        myfile.flush();
        myfile.close();
    }

    sold = new soldcheckpage(this);
    sold->show();
}

void Accountant::on_pushButton_clicked()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);
        out<<"all";
        myfile.flush();
        myfile.close();
    }

    sold = new soldcheckpage(this);
    sold->show();
}

void Accountant::on_pushButton_2_clicked()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);
        out<<"exp";
        myfile.flush();
        myfile.close();
    }

    sold = new soldcheckpage(this);
    sold->show();
}

void Accountant::on_search_returnPressed()
{

   if(ui->search->text() != nullptr)
   {
       QString searchfor = ui->search->text();

       QDir dir;
       QString filename = dir.absoluteFilePath("TEMPDATA");
       QFile myfile(filename);
       myfile.open(QIODevice::WriteOnly|QFile::Text);
       if(myfile.isOpen())
       {
           QTextStream out(&myfile);
           out<<searchfor;
           myfile.flush();
           myfile.close();
       }

       searchs = new search(this);
       searchs->show();
   }

}


void Accountant::on_todaybutton_3_clicked()
{
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);
        out<<ui->fullname->text();
        myfile.flush();
        myfile.close();
    }
    exp = new Exepediture(this);
    exp->show();
}


void Accountant::on_todaybutton_2_clicked()
{
    rep = new report(this);
    rep->show();
}


