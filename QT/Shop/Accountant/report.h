#ifndef REPORT_H
#define REPORT_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QtSql>
#include <QDir>
#include <QString>
#include "database.h"

namespace Ui {
class report;
}

class report : public QMainWindow, public Database
{
    Q_OBJECT

public:
    explicit report(QWidget *parent = nullptr);
    ~report();
    void fullsold();
    void lesssold();
    void available();
    void collectbook();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::report *ui;
};

#endif // REPORT_H
