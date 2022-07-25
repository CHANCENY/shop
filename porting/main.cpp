#include <QCoreApplication>
#include <iostream>
#include <string>
#include "portclass.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    portClass ports;

        for(int i = -1; i < argc; i++)
        {
            if(argv[i+1] == nullptr)
            {
                ports.homeLandingFunction();

            }
            else
            {
              ports.recieverCommands(argv[i+1]);

            }

        }


   return a.exec();



}
