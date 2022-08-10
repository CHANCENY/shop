#ifndef MYTHREADMINNINGFILES_H
#define MYTHREADMINNINGFILES_H

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDir>

class MythreadMinningFiles : public QThread
{
public:
    MythreadMinningFiles();
    void run();
    void ReadFileData(QString path);
    void constructData();
    QString makingArray(QStringList data);
    void getFileNames(QStringList li, QString savingFileName);
    void processingDataFromFile();
    void writingFileAppend(QString line);
    void writingValuesProgressing(QString totalfile, QString onNumber);
    void fileBeingProcced(QString file);
    void removeExtraCommaEnd();

private:
    QString dataReadFromFile;
    QStringList listMadeFromDataRead;
    QString fileToBeMadeSaving;
    QStringList filesToProcess;

    int total;
    int currentposition;

};

#endif // MYTHREADMINNINGFILES_H
