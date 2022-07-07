#include "search.h"
#include "ui_search.h"

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    searching();
}

search::~search()
{
    delete ui;
}

void search::searching()
{
    QString linesearch = nullptr;
    QDir dir;
    QString filename = dir.absoluteFilePath("TEMPDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        linesearch = in.readAll();
        myfile.close();
    }

    if(itemdbcon())
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *query1 = new QSqlQuery(mydb);
        query1->prepare("SELECT * FROM items WHERE name='"+linesearch+"';");
        if(query1->exec())
        {

            model->setQuery(*query1);
            ui->tableView->setModel(model);

        }
    }
}
