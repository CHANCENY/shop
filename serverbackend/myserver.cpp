#include "myserver.h"

myServer::myServer(QObject *parent) :  QTcpServer(parent)
{

}

QString myServer::startServer()
{

    if(!this->listen(QHostAddress::Any,8888))
    {
        qDebug()<<"server not listening ....";
        return nullptr;
    }
    else
    {
          qDebug()<<"server listening ....";
          return "true";
    }
     return nullptr;

}

void myServer::incomingConnection(qintptr handle)
{
    // this vrtual function has been overrider to handle incoming
       // connection

       myClient *client = new myClient(this);
       client->setSocket(handle);

       qDebug()<<handle<<" connection is attempting to connect....";
}

