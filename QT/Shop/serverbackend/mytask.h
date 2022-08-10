#ifndef MYTASK_H
#define MYTASK_H

#include <QRunnable>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "validateuser.h"
#include "shopactivityclass.h"
#include "adminclass.h"


class mytask :  public QObject, public QRunnable, public validateuser, public shopActivityClass, public AdminClass
{
    Q_OBJECT
public:
    mytask();
    void TaskGivenFile();
    void DecisionPath();
    void PassDataTosend(QByteArray arr);
    QByteArray Sending();
;
signals:
    void Result(QByteArray number);

protected:
    void run();

private:
    QByteArray data;
};

#endif // MYTASK_H
