#ifndef EXEPEDITURE_H
#define EXEPEDITURE_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QtSql>
#include <QDir>
#include <QString>
#include "database.h"
#include "mysockets.h"
#include <QTimer>

namespace Ui {
class Exepediture;
}

class Exepediture : public QDialog, public Database
{
    Q_OBJECT

public:
    explicit Exepediture(QWidget *parent = nullptr);
    ~Exepediture();
    bool checkcode(QString code);
    bool accountcheck(QString password);
    void releaseMoney(QString amount, QString code, QString  desc);

public slots:
    void resultexp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Exepediture *ui;
    mySockets socketing;
};

#endif // EXEPEDITURE_H
