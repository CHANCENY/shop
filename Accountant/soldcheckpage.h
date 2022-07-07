#ifndef SOLDCHECKPAGE_H
#define SOLDCHECKPAGE_H

#include <QDialog>
#include <QDate>
#include <QtSql>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include "database.h"

namespace Ui {
class soldcheckpage;
}

class soldcheckpage : public QDialog, public Database
{
    Q_OBJECT

public:
    explicit soldcheckpage(QWidget *parent = nullptr);
    ~soldcheckpage();
    void todaycheck();
    void allcheck();
    void checkingpart();
    void expected();

private:
    Ui::soldcheckpage *ui;
};

#endif // SOLDCHECKPAGE_H
