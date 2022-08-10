#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
#include <QFile>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class result; }
QT_END_NAMESPACE

class result : public QDialog
{
    Q_OBJECT

public:
    result(QWidget *parent = nullptr);
    ~result();

    void queryView(QString queryview, QString databasename);

private:
    Ui::result *ui;
};
#endif // RESULT_H
