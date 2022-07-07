#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QDialog>
#include <QtSql>
#include "database.h"
#include <QString>
#include "mysockets.h"

namespace Ui {
class Stockwindow;
}

class Stockwindow : public QDialog, Database
{
    Q_OBJECT

public:
    explicit Stockwindow(QWidget *parent = nullptr);
    ~Stockwindow();
    QString generateBarcode();
    void savingItem(QStringList item);
    QString totalavailableitem();
    void changecollect(QString barcode);

public slots:
    void resultofsaving();
    void resultofchanges();


private slots:
    void on_barcodebutton_clicked();

    void on_saveitem_clicked();

    void on_changebutton_clicked();

private:
    Ui::Stockwindow *ui;
    mySockets sock;
};

#endif // STOCKWINDOW_H
