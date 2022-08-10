#include "result.h"
#include "ui_result.h"
#include <QtSql>

result::result(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::result)
{
    ui->setupUi(this);


    QString line = nullptr;

    QDir dir;
    QString filename = dir.absoluteFilePath("query.txt");
    QFile myfile(filename);

    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream out(&myfile);
        line = out.readAll();
        myfile.close();


        if(line != nullptr)
        {

         QStringList list = line.split('-');

         QString com = nullptr;

         for(int i = 0; i < list.last().length(); i++)
         {
             if(list.last().at(i) == '#')
             {
                 com = com + ' ';
             }
             else
             {
                 com = com + list.last()[i];
             }
         }
        qDebug()<<com;
         this->queryView(com, list[0]);
        }

    }
}

result::~result()
{
    delete ui;
}

void result::queryView(QString queryview, QString databasename)
{
  setWindowTitle(databasename);
  if(databasename != nullptr && queryview != nullptr)
  {
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(databasename);
    if(mydb.open())
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *query1 = new QSqlQuery(mydb);
        query1->prepare(queryview);
        if(query1->exec())
        {

          model->setQuery(*query1);
          ui->tableView->setModel(model);

       }
    }

  }
}

