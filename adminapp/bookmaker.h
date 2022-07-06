#ifndef BOOKMAKER_H
#define BOOKMAKER_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "mysockets.h"

namespace Ui {
class bookmaker;
}

class bookmaker : public QDialog
{
    Q_OBJECT

public:
    explicit bookmaker(QWidget *parent = nullptr);
    ~bookmaker();

public slots:
    void resultmaker();

private slots:
    void on_number_returnPressed();

private:
    Ui::bookmaker *ui;
    mySockets socketcon;
};

#endif // BOOKMAKER_H
