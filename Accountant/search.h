#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QDate>
#include <QtSql>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include "database.h"

namespace Ui {
class search;
}

class search : public QDialog, public Database
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
    void searching();

private:
    Ui::search *ui;
};

#endif // SEARCH_H
