#include "bookmaker.h"
#include "ui_bookmaker.h"
#include <QMessageBox>
#include <QTimer>

bookmaker::bookmaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookmaker)
{
    ui->setupUi(this);
}

bookmaker::~bookmaker()
{
    delete ui;
}

void bookmaker::resultmaker()
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
       QStringList list = line.split(',');

       if(list[0] == "true")
       {
         QMessageBox::information(this,"update information","Book Account: "+list[1]+"  Number: "+list.last()+ " created successfully");
       }
       else
       {
           QMessageBox::warning(this,"Network error","Sorry we have encountered network problem!");
       }
   }
}

void bookmaker::on_number_returnPressed()
{
    QString name = ui->name->text();
    QString number = ui->number->text();

    if(name != nullptr && number != nullptr)
    {
        QString lines ="CreateBookAccount,"+name+","+number;
        QByteArray data;
        data.append(lines.toStdString());
        socketcon.SendingToServer(data);
        QTimer::singleShot(1000,this,SLOT(resultmaker()));
    }
}

