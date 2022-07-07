#include "stockwindow.h"
#include "ui_stockwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>



QString name = nullptr;
QString price = nullptr;
QString barcode = nullptr;
QString group = nullptr;

Stockwindow::Stockwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stockwindow)
{
    ui->setupUi(this);
    ui->totalindb->setText(totalavailableitem());
}

Stockwindow::~Stockwindow()
{
    delete ui;
}

QString Stockwindow::generateBarcode()
{
   QString code = nullptr;
   here:
   for(int i = 0; i < 8; i++)
   {
       int x = QRandomGenerator::global()->bounded(0,9);
       code = code + QString::number(x);
   }

   // check in db if exist already

   if(itemdbcon())
   {
     QSqlQuery query;
     query.prepare("SELECT barcode FROM items WHERE barcode='"+code+"';");
     if(query.exec())
     {
        while(query.next())
        {
            if(query.value(0).toString() != nullptr)
            {
                return code;
            }
            else
            {
                goto here;
            }
        }
     }
   }


   return code;
}

void Stockwindow::savingItem(QStringList item)
{
   QString line = nullptr;

   for(int i = 0; i < item.size(); i++)
   {
     line = line + item[i]+"/";
   }

   std::string line2 ="saving,"+line.toStdString();
   QByteArray data;
   data.append(line2);
   sock.SendingToServer(data);
   QTimer::singleShot(1000,this,SLOT(resultofsaving()));

}

QString Stockwindow::totalavailableitem()
{
    if(itemdbcon())
    {
      QSqlQuery query;
      query.prepare("SELECT * FROM items WHERE SoldStatus='Unsold';");
      if(query.exec())
      {
          QStringList list;

          while(query.next())
          {
              list.append(query.value(0).toStringList());
          }

          QString size = QString::number(list.size());
          list.clear();
          return size;
      }
    }

    return "0";
}

void Stockwindow::changecollect(QString barcode)
{
   QByteArray data;
   data.append("change,"+barcode.toStdString());
   sock.SendingToServer(data);
   QTimer::singleShot(1000,this,SLOT(resultofchanges()));
}

void Stockwindow::resultofsaving()
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
            ui->savecounter->setText(QString::number(ui->savecounter->text().toInt() + 1));
            ui->totalindb->setText(totalavailableitem());
            ui->listsaved->addItem("N: "+name+"    P: "+price+"    G: "+group+" B:"+barcode);
        }
        else
        {
            QMessageBox::warning(this,"warning","the item you want to save it barcode code already exist!");
        }


}

void Stockwindow::resultofchanges()
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
        QStringList list = line.split('@');

        ui->itemname->setText(list.at(0));
        ui->itemprice->setText(list.at(1));
        ui->itembarcode->setText(list.at(2));
        ui->selectgroup->setCurrentText(list.at(3));
        ui->offerdecription->insertPlainText(list.at(4));
    }
    else
    {
        QMessageBox::warning(this,"network error","Network error occured");
    }
}

void Stockwindow::on_barcodebutton_clicked()
{
    ui->itembarcode->setText(generateBarcode());
    ui->itembarcode->setReadOnly(true);
}


void Stockwindow::on_saveitem_clicked()
{
    if(ui->selectgroup->currentText() != "Select group here")
    {
         name = ui->itemname->text();
         price = ui->itemprice->text();
         barcode = ui->itembarcode->text();
         QString description = nullptr;
         group = ui->selectgroup->currentText();
        if(ui->offerdecription->toPlainText() == nullptr)
        {
            description = "No offer";
        }
        else
        {
           description = ui->offerdecription->toPlainText();
        }

        if(name != nullptr && price != nullptr && barcode != nullptr && description != nullptr)
        {
            QStringList list;
            list.append(name);
            list.append(price);
            list.append(barcode);
            list.append(group);
            list.append(description);

            savingItem(list);

        }

    }
    else
    {
       QMessageBox::warning(this,"warning","You have't select group");
    }

}


void Stockwindow::on_changebutton_clicked()
{
    QString line = ui->listsaved->currentItem()->text();
    QStringList list = line.split(':');
    changecollect(list.last());
}

