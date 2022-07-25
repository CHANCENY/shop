#ifndef PORTCLASS_H
#define PORTCLASS_H
#include <QString>
#include <QFile>
#include <QTextStream>


class portClass
{
public:
    portClass();

    void declarePortNumber(QString portnumber);
    void clearPortNumber();
    void defaultPort();
    void recieverCommands(QString command);
    void homeLandingFunction();
    void help();
};

#endif // PORTCLASS_H
