#include "settings.h"
#include "ui_settings.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>


settings::settings(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}


void settings::on_set_clicked()
{
    QString ipAddress =ui->ipaddress->text();
    QString port = ui->port->text();

    if(ipAddress != nullptr && port != nullptr)
    {
       QDir dir;
       QString filename = dir.absoluteFilePath("ConfigNetwork");

       QFile myfile(filename);
       myfile.open(QIODevice::WriteOnly|QFile::Text);
       if(myfile.isOpen())
       {
           QTextStream out(&myfile);
           out<<ipAddress+"@"+port;
           myfile.flush();
           myfile.close();
           ui->messages->setText("IP: "+ipAddress+" PORT: "+port+" confirmed");
           QMessageBox::information(this,"Configuration","IP: "+ipAddress+" PORT: "+port+" confirmed you can restart");
           this->close();
       }
    }
    ui->messages->setText("IP: "+ipAddress+" PORT: "+port+" Failed");
}


void settings::on_ipaddress_returnPressed()
{
    QString ipAddress =ui->ipaddress->text();
    QString port = ui->port->text();

    if(ipAddress != nullptr && port != nullptr)
    {
       QDir dir;
       QString filename = dir.absoluteFilePath("ConfigNetwork");

       QFile myfile(filename);
       myfile.open(QIODevice::WriteOnly|QFile::Text);
       if(myfile.isOpen())
       {
           QTextStream out(&myfile);
           out<<ipAddress+"@"+port;
           myfile.flush();
           myfile.close();
           ui->messages->setText("IP: "+ipAddress+" PORT: "+port+" confirmed");
           QMessageBox::information(this,"Configuration","IP: "+ipAddress+" PORT: "+port+" confirmed you can restart");
           this->close();
       }
    }
    ui->messages->setText("IP: "+ipAddress+" PORT: "+port+" Failed");
}

