#ifndef MYSOCKETS_H
#define MYSOCKETS_H

#include <QTcpSocket>
#include <QObject>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QDebug>


class mySockets : public QTcpSocket
{
    Q_OBJECT
public:
    explicit mySockets(QObject *parent = 0);
    //void startSocket();
    void SendingToServer(QByteArray data);
    void WriteToFile(QByteArray array);

    // login page functions


public slots:
    void readyRead();


private:
    QTcpSocket *socket;

};


#endif // MYSOCKETS_H
