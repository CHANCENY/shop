#ifndef NEWEMPLOYEES_H
#define NEWEMPLOYEES_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"
#include "databases.h"
#include <QTimer>

namespace Ui {
class newEmployees;
}

class newEmployees : public QDialog, public Databases
{
    Q_OBJECT

public:
    explicit newEmployees(QWidget *parent = nullptr);
    ~newEmployees();
    bool checkUsername(QString username);

public slots:
    void result();

private slots:
    void on_pushButton_2_clicked();

    void on_selectphoto_clicked();

private:
    Ui::newEmployees *ui;
    mySockets sockets;
};

#endif // NEWEMPLOYEES_H
