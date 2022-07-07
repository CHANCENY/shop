#include "mysockets.h"
#include <QDir>

mySockets::mySockets(QObject *parent) : QTcpSocket(parent)
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void mySockets::SendingToServer(QByteArray data)
{
    qDebug()<<"connecting ....";
    qDebug()<<" About Send ..."<<data;
    socket->connectToHost("127.0.0.1",8888);
    if(!socket->waitForConnected(3000))
    {
        socket->close();
    }
    else
    {
        qDebug()<<"Sending ..."<<data;
        socket->write(data);
        socket->flush();
        socket->waitForBytesWritten();

    }

}

void mySockets::WriteToFile(QByteArray array)
{
    QDir dir;
    QString filename = dir.absoluteFilePath("RECEIVEDDATA");
    QFile myfile(filename);
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        in<<array;
        myfile.flush();
        myfile.close();
    }
}


void mySockets::readyRead()
{
    QByteArray receivedData;
    receivedData = socket->readAll();
     qDebug()<<"RECEIVED FROM SERVER : "<<receivedData;
    WriteToFile(receivedData);
    socket->close();

}
