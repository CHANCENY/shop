#ifndef TELLERHOME_H
#define TELLERHOME_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "mysockets.h"
#include "dbcon.h"

namespace Ui {
class TellerHome;
}

class TellerHome : public QMainWindow, public DBCon
{
    Q_OBJECT

public:
    explicit TellerHome(QWidget *parent = nullptr);
    ~TellerHome();

    void setTellerInfo();
    void deleteitems();



public slots:
    void clockingout();
    void updatefromserver();
    void updatelocaldb();
    void soldfeedback();

private slots:

    void on_lineEdit_returnPressed();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_cartlist_currentTextChanged(const QString &currentText);

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    Ui::TellerHome *ui;
    mySockets socks;
};

#endif // TELLERHOME_H
