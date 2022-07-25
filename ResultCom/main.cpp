#include "result.h"
#include <QString>
#include <QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString line = nullptr;
    for(int i = 0; i < argc; i++)
    {
      line = line + argv[i];
    }



    if(line != nullptr)
    {
        QStringList list = line.split("exe");
        line = list.last();
         qDebug()<<line;


       QDir dir;
       QString filename = dir.absoluteFilePath("query.txt");
       QFile myfile(filename);

       myfile.open(QIODevice::WriteOnly|QFile::Text);
       if(myfile.isOpen())
       {
           QTextStream out(&myfile);
           out<<line;
           myfile.flush();
           myfile.close();
       }

       result w;
       w.show();



    }
    result w;
    w.show();
    return a.exec();
}
