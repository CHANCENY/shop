#include "csvformatting.h"

static int let = 0;

CsvFormatting::CsvFormatting(QObject *parent)
    : QThread{parent}
{

}

void CsvFormatting::run()
{
    int counter = 0;

    if(!this->csvFiles.isEmpty())
    {
        int sizes = this->csvFiles.size();

        for(int i = 0; i < sizes; i++)
        {
            this->writeNames(this->csvFiles[i]);
            QString data =this->readingCsvFile(this->csvFiles[i]);
            if(data != nullptr)
            {
                if(this->writingTextFile(data,this->csvFiles[i]))
                {
                    this->writeStatus(QString::number(sizes),QString::number(i));
                    counter++;
                }
            }
        }
    }

    if(counter == this->csvFiles.size())
    {
        this->writeResponse(this->tempPath);

    }
}

QString CsvFormatting::readingCsvFile(QString path)
{
    QDir dir;
    QString filename = dir.absoluteFilePath(path);
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen())
    {
        QString line = myfile.readAll();
        myfile.close();
        return line;
    }
    return nullptr;
}

bool CsvFormatting::writingTextFile(QString data, QString orignalpath)
{
    QFileInfo info(orignalpath);
    QString temppath = info.baseName()+QString::number(let)+".txt";

    QFile myfile(temppath);
    myfile.open(QIODevice::WriteOnly|QIODevice::Append|QFile::Text);
    if(myfile.isOpen())
    {

        QTextStream out(&myfile);
        out<<data;
        myfile.flush();
        myfile.close();

        this->tempPath += temppath+"\n";
        return true;
    }
    return false;
}

void CsvFormatting::writeResponse(QString temppath)
{
    QFile myfile("temp3");
    myfile.open(QIODevice::WriteOnly);
    if(myfile.isOpen())
    {
        myfile.write(temppath.toLocal8Bit());
        myfile.flush();
        myfile.close();
    }
}

void CsvFormatting::writeStatus(QString total, QString current)
{
    QFile myfile("temp1");
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        in<<total<<","<<current;
        myfile.flush();
        myfile.close();

    }
}

void CsvFormatting::writeNames(QString name)
{
    QFileInfo info(name);

    QFile myfile("temp2");
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        in<<info.fileName();
        myfile.flush();
        myfile.close();

    }
}

void CsvFormatting::removingEnd()
{

}


void CsvFormatting::getFileCsv(QStringList li)
{
   this->csvFiles = li;
}
