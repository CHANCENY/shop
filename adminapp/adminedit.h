#ifndef ADMINEDIT_H
#define ADMINEDIT_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"
#include "databases.h"
#include <QTimer>

namespace Ui {
class adminedit;
}

class adminedit : public QDialog, public Databases
{
    Q_OBJECT

public:
    explicit adminedit(QWidget *parent = nullptr);
    ~adminedit();

public slots:
    void result();

private slots:
    void on_selectphoto_clicked();

    void on_username_textChanged(const QString &arg1);

    void on_name_textChanged(const QString &arg1);

    void on_commitchange_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::adminedit *ui;
    mySockets sock;
};

#endif // ADMINEDIT_H
