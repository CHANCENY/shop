#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"
#include "adminpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

    void clearuser(QString line);

public slots:
    void validateuser();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::login *ui;
    mySockets socket;
    Adminpage *admin;
};
#endif // LOGIN_H
