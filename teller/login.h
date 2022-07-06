#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mysockets.h"
#include "tellerhome.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

    void logInNow(QString username, QString passwrd);
    void saveduserfound(QString line);


public slots:
    void readfile();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::Login *ui;
    mySockets  socket;
    TellerHome *teller;
};
#endif // LOGIN_H
