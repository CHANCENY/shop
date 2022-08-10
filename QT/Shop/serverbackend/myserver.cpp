#include "myserver.h"

myServer::myServer(QObject *parent) :  QTcpServer(parent)
{

}

QString myServer::startServer()
{

    int port = portFinder().toInt();

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug()<<"server not listening ....";
        return nullptr;
    }
    else
    {
          qDebug()<<"----SERVER LISTENING AT PORT "<<port;
          return "true";
    }
     return nullptr;

}

QString myServer::portFinder()
{
  QDir dir;
  QString filename = dir.absoluteFilePath("PORT");

  QFile myfile(filename);
  myfile.open(QIODevice::ReadOnly);
  if(myfile.isOpen())
  {
      QTextStream in(&myfile);
      return in.readAll();
  }
  return nullptr;
}

void myServer::incomingConnection(qintptr handle)
{
    // this vrtual function has been overrider to handle incoming
       // connection

       myClient *client = new myClient(this);
       client->setSocket(handle);

       qDebug()<<handle<<" connection established successfully....";
}

