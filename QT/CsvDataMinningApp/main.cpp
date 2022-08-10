#include "mining.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mining w;
    a.setWindowIcon(QIcon(":/icons/style/logo1.ico"));
    w.show();
    return a.exec();
}
