#ifndef SHOPACTIVITYCLASS_H
#define SHOPACTIVITYCLASS_H

#include <QtSql>
#include <QDir>
#include "databasesclass.h"


class shopActivityClass: public databasesClass
{
public:
    shopActivityClass();
    QByteArray collectAvaiableItems(QString line);
    QByteArray sellingupdate(QString line);
    QByteArray allcollectionitems(QString line);
    QByteArray allcollectionbook(QString line);
    QByteArray savingiteminshop(QString line);
    QByteArray changecollect(QString barcode);
    QByteArray expeditures(QString line);


};

#endif // SHOPACTIVITYCLASS_H
