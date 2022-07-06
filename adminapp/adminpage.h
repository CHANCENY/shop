#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"
#include "databases.h"
#include "bookmaker.h"
#include "adminedit.h"
#include "newemployees.h"
#include <QDateTime>

namespace Ui {
class Adminpage;
}

class Adminpage : public QMainWindow, public Databases
{
    Q_OBJECT

public:
    explicit Adminpage(QWidget *parent = nullptr);
    ~Adminpage();
    void admininfo();
    void checkBookIfExist();
    QString generateCode();

public slots:
    void getEmployeesUpdateFromServer();
    void localupdateemployees();
    void bookMakerResponse();

    void countingExpire();
    void timing();


private slots:
    void on_bookbutton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_searchresulttable_clicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::Adminpage *ui;
    mySockets sock;
    bookmaker *book;
    adminedit *edit;
    newEmployees *employer;
};

#endif // ADMINPAGE_H
