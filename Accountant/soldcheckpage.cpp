#include "soldcheckpage.h"
#include "ui_soldcheckpage.h"

soldcheckpage::soldcheckpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::soldcheckpage)
{
    ui->setupUi(this);
    checkingpart();
}

soldcheckpage::~soldcheckpage()
{
    delete ui;
}

void soldcheckpage::todaycheck()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList prices, names, originalprice;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE datesold='"+dates+"' AND SoldStatus='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
                names.append(query.value(0).toString());
                prices.append(query.value(8).toString());
                originalprice.append(query.value(1).toString());
            }

            int sizes = prices.size();

            //calculate total amount
            double total = 0;
            for(int i=0; i < sizes; i++)
            {
               total = total + prices[i].toDouble() ;
            }

            if(total != 0)
            {
               int percentage = total / 100;

               if(percentage > 100)
               {
                   ui->progressBar->setValue(1);
                   ui->valueper->setText("1 %");
               }
               else{
                   ui->progressBar->setValue(percentage);
                   ui->valueper->setText(QString::number(percentage)+" %");
               }
            }
            else
            {
                ui->progressBar->setValue(100);
                ui->valueper->setText("100 % ");
            }
            ui->totalamount->setText(QString::number(total));
            ui->solditemtotal->setText(QString::number(sizes));

            QStringList itemandprice;

            for(int i =0; i < sizes; i++)
            {
                itemandprice.append(names[i]+"  |Sold At:"+prices[i]+"  |Orignal price:"+originalprice[i]);
                itemandprice.append(" ");
            }
            ui->comboBox->addItems(itemandprice);
        }

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery *query1 = new QSqlQuery(mydb);
            query1->prepare("SELECT * FROM items WHERE datesold = '"+dates+"';");
            if(query1->exec())
            {

                model->setQuery(*query1);
                ui->tableView->setModel(model);

                ui->note->setText("Note: The total amount is sum of all items sold today ");
            }

    }

}

void soldcheckpage::allcheck()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList prices, names,originalprice;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items WHERE SoldStatus='Sold';");
        if(query.exec())
        {
            while(query.next())
            {
                names.append(query.value(0).toString());
                prices.append(query.value(8).toString());
                originalprice.append(query.value(1).toString());
            }

            int sizes = prices.size();

            //calculate total amount
            double total = 0;
            for(int i=0; i < sizes; i++)
            {
               total = total + prices[i].toDouble();
            }

            if(total != 0)
            {
               int percentage = total / 100;
               if(percentage > 100)
               {
                   ui->progressBar->setValue(1);
                   ui->valueper->setText("1 %");
               }
               else{
                   ui->progressBar->setValue(percentage);
                   ui->valueper->setText(QString::number(percentage)+" %");
               }
            }
            else
            {
                ui->progressBar->setValue(100);
                ui->valueper->setText("100 % ");
            }


            ui->totalamount->setText(QString::number(total));
            ui->solditemtotal->setText(QString::number(sizes));

            QStringList itemandprice;

            for(int i =0; i < sizes; i++)
            {
                itemandprice.append(names[i]+"    | Sold At: "+prices[i]+"    | Orignal price: "+originalprice[i]);
                itemandprice.append(" ");
            }
            ui->comboBox->addItems(itemandprice);
        }

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery *query1 = new QSqlQuery(mydb);
            query1->prepare("SELECT * FROM items WHERE SoldStatus='Sold';");
            if(query1->exec())
            {

                model->setQuery(*query1);
                ui->tableView->setModel(model);

                ui->note->setText("Note: The total amount is sum of all items sold");
            }

    }

}

void soldcheckpage::checkingpart()
{
    ui->groupBox_2->setVisible(true);
    QString line = nullptr;
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        line = in.readAll();
        myfile.close();
    }

    if(line == "today")
    {
       todaycheck();
    }
    else if(line == "all")
    {
        allcheck();
    }
    else if(line == "exp")
    {
        expected();
    }

}

void soldcheckpage::expected()
{
    QDate date = QDate::currentDate();
    QString dates = date.toString("dd-MM-yy");

    QStringList prices, names;

    if(itemdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM items;");
        if(query.exec())
        {
            while(query.next())
            {
                names.append(query.value(0).toString());
                prices.append(query.value(1).toString());
            }

            int sizes = prices.size();

            //calculate total amount
            double total = 0;
            for(int i=0; i < sizes; i++)
            {
               total = total + prices[i].toDouble();
            }

            if(total != 0)
            {
               int percentage = total / 100;
               if(percentage > 100)
               {
                   ui->progressBar->setValue(1);
                   ui->valueper->setText("1 %");
               }
               else{
                   ui->progressBar->setValue(percentage);
                   ui->valueper->setText(QString::number(percentage)+" %");
               }
            }
            else
            {
                ui->progressBar->setValue(100);
                ui->valueper->setText("100 % ");
            }


            ui->totalamount->setText(QString::number(total));
            ui->solditemtotal->setText(QString::number(sizes));

           ui->groupBox_2->setVisible(false);

        }

            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery *query1 = new QSqlQuery(mydb);
            query1->prepare("SELECT * FROM items;");
            if(query1->exec())
            {

                model->setQuery(*query1);
                ui->tableView->setModel(model);

                ui->note->setText("Note: This is Expected amount after selling all items");
            }

    }
}
