#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class settings; }
QT_END_NAMESPACE

class settings : public QMainWindow
{
    Q_OBJECT

public:
    settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void on_set_clicked();
    void on_ipaddress_returnPressed();

private:
    Ui::settings *ui;
};
#endif // SETTINGS_H
