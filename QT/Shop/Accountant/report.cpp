#include "report.h"
#include "ui_report.h"
#include <QQueue>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QMessageBox>


int row = 0;
 QString nameb, balance, number;
 QString bank = nullptr;
 QString totalsold = nullptr;
 QString totalunsold = nullptr;

report::report(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::report)
{
    ui->setupUi(this);
    fullsold();
    lesssold();
    available();
    collectbook();



    QMessageBox::about(this,"NOTICE","NOTICE HOW TO WORK WITH DOCUMENT PRINTED HERE.\n\nThe document which can be printed out here are in html format.\nYou can open them with any browser.\nYou can convert them to pdf using this link\n\n( https://www.sejda.com/html-to-pdf )");


}

report::~report()
{
    delete ui;
}

void report::fullsold()
{
    if(itemdbcon())
    {
        double total = 0;
        QSqlQuery q;
        q.prepare("SELECT * FROM items WHERE SoldStatus='Sold'");
        if(q.exec())
        {
            while(q.next())
            {
                total =total + q.value(1).toDouble();

            }
        }

        ui->fullsoldlabel->setText(QString::number(total));

        totalsold ="<div class='container'><div class='row'><div class='col'>Total Found Amount: "+QString::number(total)+"</div></div></div>";

        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *query1 = new QSqlQuery(mydb);
        query1->prepare("SELECT * FROM items WHERE SoldStatus = 'Sold';");
        if(query1->exec())
        {

            model->setQuery(*query1);
            ui->tableView->setModel(model);

        }
    }

}

void report::lesssold()
{
  if(itemdbcon())
  {

          QSqlQueryModel *model = new QSqlQueryModel();
          QSqlQuery *query1 = new QSqlQuery(mydb);
          query1->prepare("SELECT * FROM items WHERE SoldStatus = 'Unsold';");
          if(query1->exec())
          {

              model->setQuery(*query1);
              ui->tableView_2->setModel(model);

          }

  }
}

void report::available()
{
   if(itemdbcon())
   {
       double total=0;
       QSqlQuery q;
       q.prepare("SELECT * FROM items WHERE SoldStatus='Unsold'");
       if(q.exec())
       {
           while(q.next())
           {

               total = total + q.value(1).toDouble();
           }
       }

       ui->availablelabel->setText(QString::number(total));
        totalunsold ="<div class='container'><div class='row'><div class='col'>Total Found Amount: "+QString::number(total)+"</div></div></div>";

   }
}

void report::collectbook()
{


    if(bookcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM book;");
        if(query.exec())
        {
            while(query.next()){
                nameb = query.value(0).toString();
                balance = query.value(1).toString();
                number = query.value(2).toString();
            }

        }

        bank = "<div class='container'><div class='row'><div class='col'>Acc Name: "+nameb+"</div><div class='col'>Acc Number: "+number+"</div><div class='col'>Acc Balance: "+balance+"</div></div></div>";
    }
}

void report::on_pushButton_clicked()
{

    // making html head with css boostrap
    QString header = "<!DOCTYPE html><html> <head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>document</title>'<link rel='stylesheet' type='text/css' href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css'></head><body>";
    QString tail ="</body></html>";
    QString table = "<table class='table table-bordered'>";
    QString thead = "<thead><tr><th scope='col'>Name</th><th scope='col'>Price</th><th scope='col'>Groups</th><th scope='col'>Description</th><th scope='col'>Offer</th><th scope='col'>DateSold</th><th scope='col'>SoldPrice</th></tr></thead>";
    QString data = nullptr;


   if(itemdbcon())
   {
       QSqlQuery query;
       query.prepare("SELECT * FROM items WHERE SoldStatus ='Sold';");
       if(query.exec())
       {
           while(query.next())
           {
               QString line = "<tbody><tr><th scope='row'>"+query.value(0).toString()+"</th>"
                               "<td>"+query.value(1).toString()+"</td>"

                               "<td>"+query.value(3).toString()+"</td>"
                               "<td>"+query.value(4).toString()+"</td>"

                               "<td>"+query.value(6).toString()+"</td>"
                               "<td>"+query.value(7).toString()+"</td>"
                               "<td>"+query.value(8).toString()+"</td></tr>";

             data = data + line;

           }

           QString dochtml =bank+header+table+thead+data+"</table>"+totalsold+tail;
           QByteArray datas = dochtml.toUtf8();

           QFileDialog dialog;
           dialog.saveFileContent(datas,"Fullsold_items.html");

       }
   }

}

void report::on_pushButton_3_clicked()
{
    // making html head with css boostrap
    QString header = "<!DOCTYPE html><html> <head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>document</title>'<link rel='stylesheet' type='text/css' href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css'></head><body>";
    QString tail ="</body></html>";
    QString table = "<table class='table table-bordered'>";
    QString thead = "<thead><tr><th scope='col'>Name</th><th scope='col'>Price</th><th scope='col'>Groups</th><th scope='col'>Description</th><th scope='col'>Offer</th><th scope='col'>DateSold</th><th scope='col'>SoldPrice</th></tr></thead>";

   QString data = nullptr;

   if(itemdbcon())
   {
       QSqlQuery query;
       query.prepare("SELECT * FROM items WHERE SoldStatus ='Unsold';");
       if(query.exec())
       {
           while(query.next())
           {
               QString line = "<tbody><tr><th scope='row'>"+query.value(0).toString()+"</th>"
                               "<td>"+query.value(1).toString()+"</td>"

                               "<td>"+query.value(3).toString()+"</td>"
                               "<td>"+query.value(4).toString()+"</td>"

                               "<td>"+query.value(6).toString()+"</td>"
                               "<td>"+query.value(7).toString()+"</td>"
                               "<td>"+query.value(8).toString()+"</td></tr>";

             data = data + line;

           }

           QString dochtml = bank+header+table+thead+data+"</table>"+totalunsold+tail;
           QByteArray datas = dochtml.toUtf8();

           QFileDialog dialog;
           dialog.saveFileContent(datas,"Available_items.html");

       }
   }

}


void report::on_pushButton_2_clicked()
{
    // making html head with css boostrap
    QString header = "<!DOCTYPE html><html> <head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>document</title>'<link rel='stylesheet' type='text/css' href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css'></head><body>";
    QString tail ="</body></html>";
    QString table = "<table class='table table-bordered'>";
    QString thead = "<thead><tr><th scope='col'>Code</th><th scope='col'>Verified</th><th scope='col'>Amount</th><th scope='col'>Description</th><th scope='col'>Expire time</th><th scope='col'>Expired</th><th scope='col'>ReleasedBy</th><th scope='col'>ExpectedAmount</th><th scope='col'>AdminAuth</th><th scope='col'>Date</th></tr></thead>";

   QString data = nullptr;

   if(releasemoneycon())
   {

       // collecting data to insert in html table
       QSqlQuery query;
       query.prepare("SELECT * FROM Rmoney;");
       if(query.exec())
       {
           while(query.next())
           {
               QString line = "<tbody><tr><th scope='row'>"+query.value(0).toString()+"</th>"
                               "<td>"+query.value(1).toString()+"</td>"
                               "<td>"+query.value(2).toString()+"</td>"
                               "<td>"+query.value(3).toString()+"</td>"
                               "<td>"+query.value(4).toString()+"</td>"
                               "<td>"+query.value(5).toString()+"</td>"
                               "<td>"+query.value(6).toString()+"</td>"
                               "<td>"+query.value(7).toString()+"</td>"
                               "<td>"+query.value(8).toString()+"</td>"
                               "<td>"+query.value(9).toString()+"</td>";

             data = data + line;

           }

           QString dochtml = bank+header+table+thead+data+"</table><h4>NOTE: verified colmun: value 1 means code was used and 0 code was not used.</h4>"+tail;
           QByteArray datas = dochtml.toUtf8();

           QFileDialog dialog;
           dialog.saveFileContent(datas,"Released money record.html");

       }
   }
}

