#ifndef ACCOUNTANT_H
#define ACCOUNTANT_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtSql>
#include <QDir>
#include <QString>
#include "database.h"
#include "stockwindow.h"
#include "soldcheckpage.h"
#include "search.h"
#include "exepediture.h"
#include "report.h"
#include "mysockets.h"

namespace Ui {
class Accountant;
}

class Accountant : public QMainWindow, public Database
{
    Q_OBJECT

public:
    explicit Accountant(QWidget *parent = nullptr);
    ~Accountant();
    void setAccountantInfo();
    void checkmonthlyrate();
    void checktwoweeks();
    void checkweek();
    void checktody();
    QString setProfilephoto();

public slots:
    void accountbook();
    void findinghighsoldandless();
    void rating();
    void updateFroServerForItems();
    void itemupdatelocal();


private slots:
    void on_todaybutton_4_clicked();

    void on_todaybutton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_search_returnPressed();

    void on_todaybutton_3_clicked();

    void on_todaybutton_2_clicked();

    void on_addprofile_clicked();

private:
    Ui::Accountant *ui;
    Stockwindow *stock;
    soldcheckpage *sold;
    search *searchs;
    Exepediture *exp;
    report *rep;
    mySockets socket;
};

#endif // ACCOUNTANT_H
