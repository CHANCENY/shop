#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"
#include "accountant.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow, public Database
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void saveuser(QString username, QString password);
    void writeLock(QString lock);



public slots:
    void validateaccountant();
    void lockingTimer();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::Login *ui;
    mySockets socket;
    Accountant *accountpage;
};
#endif // LOGIN_H
