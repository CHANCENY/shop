#include "tellerhome.h"
#include "ui_tellerhome.h"
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>

 QString endtime = nullptr;

 QStringList soldbarcode;
 QStringList  soldprices;
 QStringList cart;
 QString currentTextbarcode = nullptr;
 QString currentitemincart = nullptr;



QString usernameloggedin = nullptr;


TellerHome::TellerHome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TellerHome)
{
    ui->setupUi(this);
    setTellerInfo();

    QDateTime time = QDateTime::currentDateTime();
    QString timenow = time.toString("hh:mm");



    QStringList t = timenow.split(':');
    int hour = t[0].toInt();

    int lasthour = hour+9;

    if(lasthour < 10 && lasthour < 12)
    {
        endtime ="0"+QString::number(lasthour)+":"+t.last()+" AM";
        ui->end->setText(endtime);
    }
    else
    {
        endtime = QString::number(lasthour)+":"+t.last()+" PM";
        ui->end->setText(endtime);
    }

     updatefromserver();

    QTimer *timer = new QTimer(this);
     QTimer *timer2 = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(clockingout()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(updatefromserver()));
    timer->start(1000);
    timer2->start(30000);



}

TellerHome::~TellerHome()
{
    delete ui;
}

void TellerHome::setTellerInfo()
{
    QDir dir2;
    QString line = nullptr;
    QString filenames = dir2.absoluteFilePath("SAVEDUSER");
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
        QStringList list = line.split(',');

        ui->name->setText(list[1]);
        ui->title->setText(list.at(3));
        usernameloggedin = list[2];
        QPixmap profile(setPicture(list[2]));
        ui->profile->setPixmap(profile);
    }
}

void TellerHome::deleteitems()
{
    if(itemcon())
    {
        QSqlQuery query;

        for(int i = 0; i < soldbarcode.size(); i++)
        {
           query.prepare("DELETE FROM items WHERE barcode ='"+soldbarcode[i]+"';");
           if(query.exec())
           {
               continue;
           }
           else
           {
               break;
           }
        }
    }
}

QString TellerHome::setPicture(QString username)
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
             line = query.value(2).toString();
           }
       }

       return line;
   }
   return "none";
}

void TellerHome::clockingout()
{
  QDateTime time = QDateTime::currentDateTime();
  QString timenow = time.toString("hh:mm");


  QStringList t = timenow.split(':');
  int hour = t[0].toInt();

  if(hour < 12)
  {
     ui->start->setText(timenow+" AM");
  }
  else if(hour > 12)
  {
      ui->start->setText(timenow+" PM");
  }

  if(endtime == timenow)
  {
      QMessageBox::information(this, "Time up","You have reached your end time for today nice work have good night");
  }

}

void TellerHome::updatefromserver()
{
   QString query ="SELECT * FROM items WHERE SoldStatus ='Unsold';";
   QByteArray data = "Availableitem,"+query.toLocal8Bit();
   socks.SendingToServer(data);
   QTimer::singleShot(2000,this,SLOT(updatelocaldb()));
}

void TellerHome::updatelocaldb()
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
        QStringList rows = line.split(';');
        int sizes = rows.size();

        if(sizes > 0)
        {
            if(itemcon())
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

                }

                for(int i = 0; i < sizes -1; i++)
                {
                    QStringList col = rows[i].split('@');

                    QSqlQuery query;
                    query.prepare("INSERT INTO items(name,price,barcode,groups,description,SoldStatus,offer) VALUES('"+col[0]+"','"+col[1]+"','"+col[2]+"','"+col[3]+"','"+col[4]+"','"+col[5]+"','"+col[6]+"');");
                    if(query.exec())
                    {
                        continue;
                    }
                }

            }

        }
    }
}

void TellerHome::soldfeedback()
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
        ui->message->setText("Sold "+ui->itemladded->text());
        ui->itemladded->setText("0");
        ui->total->setText("0");
        deleteitems();
        soldbarcode.clear();
        soldprices.clear();
        cart.clear();
        ui->cartlist->clear();
    }
    else
    {
        ui->message->setText("Failed network problem");
    }
}

void TellerHome::on_lineEdit_returnPressed()
{
    QString line = ui->lineEdit->text();

    if(line != nullptr)
    {
        if(itemcon())
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM items WHERE barcode='"+line+"';");
            if(query.exec())
            {
                while(query.next())
                {
                    ui->itemname->setText(query.value(0).toString());
                    ui->itemprice->setText(query.value(1).toString());
                     ui->barcode->setText(query.value(2).toString());
                    ui->itemgroup->setText(query.value(3).toString());
                    ui->itemoffer->setText(query.value(6).toString());
                }
            }
        }
    }
}


void TellerHome::on_pushButton_3_clicked()
{
    QString name = ui->itemname->text();
    QString price = ui->itemprice->text();
    QString barcode = ui->barcode->text();

    if(name != nullptr && price != nullptr && barcode != nullptr)
    {
        int total =ui->total->text().toInt() + price.toInt();
        ui->total->setText(QString::number(total));

        int itemadded = ui->itemladded->text().toInt() + 1;
        ui->itemladded->setText(QString::number(itemadded));

        QString incart = barcode+":      Name: "+name+"  Price: "+price;

        ui->cartlist->addItem(incart);
        cart.append(incart);
        soldbarcode.append(barcode);
        soldprices.append(price);
        ui->barcode->clear();
        ui->itemprice->clear();
        ui->itemgroup->clear();
        ui->itemname->clear();
        ui->itemoffer->clear();
    }
}


void TellerHome::on_pushButton_4_clicked()
{
    QString barcode = ui->barcode->text();
    if(itemcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE barcode='"+barcode+"';");
        if(query.exec())
        {
            while(query.next())
            {
                QMessageBox::information(this,"Offer description",query.value(4).toString());
            }
        }
    }
}


void TellerHome::on_cartlist_currentTextChanged(const QString &currentText)
{
    QStringList list = currentText.split(':');
    currentTextbarcode = list[0];
    currentitemincart = currentText;
}


void TellerHome::on_pushButton_5_clicked()
{
    if(currentTextbarcode != nullptr && currentitemincart != nullptr)
    {
        int sizes = soldbarcode.size();

        int cartsize = cart.size();


        for(int i = 0; i < sizes; i++)
        {
            if(soldbarcode[i] == currentTextbarcode)
            {
                soldbarcode.removeAt(i);
                ui->itemladded->setText(QString::number(ui->itemladded->text().toInt() - 1));
                int pr = soldprices[i].toInt();
                ui->total->setText(QString::number(ui->total->text().toInt() - pr));
                soldprices.removeAt(i);
                break;
            }
        }


        for(int i = 0; i < cartsize; i++)
        {
            if(cart[i] == currentitemincart)
            {
                cart.removeAt(i);
                ui->cartlist->clear();
                ui->cartlist->addItems(cart);
                break;
            }

        }


        currentTextbarcode = nullptr;
        currentitemincart = nullptr;
        qDebug()<<soldbarcode;
        qDebug()<<soldprices;

    }
}


void TellerHome::on_pushButton_clicked()
{
    QString total = ui->total->text();
    if(total.toInt() > 0)
    {
        QString barcodes = nullptr;
        QString prices = nullptr;
        int sizes = soldbarcode.size();

        for(int i = 0; i < sizes; i++)
        {
            barcodes = barcodes +soldbarcode[i]+"@";
        }
        for(int i = 0; i < sizes; i++)
        {
            prices = prices +soldprices[i]+"@";
        }

        QString sellinginfo = "sell,"+barcodes+";"+prices+";"+total;

        QByteArray data = sellinginfo.toLocal8Bit();
        socks.SendingToServer(data);
        QTimer::singleShot(1000,this,SLOT(soldfeedback()));
        ui->lineEdit->clear();

    }
}


void TellerHome::on_addprofile_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this,"Choice photo",QDir::homePath(),"*.jpg *.jpeg *.png");
  if(filename != nullptr)
  {
      if(saverusercon())
      {
          QSqlQuery query; query.prepare("UPDATE log SET profile='"+filename+"' WHERE username='"+usernameloggedin+"';");
          if(query.exec())
          {
              QPixmap pro(filename);
              ui->profile->setPixmap(pro);
          }
      }
  }
}

