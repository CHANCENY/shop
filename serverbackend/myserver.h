#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QString>
#include "myclient.h"


class myServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myServer(QObject *parent = 0);
       QString startServer();

protected:
    void incomingConnection(qintptr handle);

private:

};

#endif // MYSERVER_H
