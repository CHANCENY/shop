#ifndef CSVFORMATTING_H
#define CSVFORMATTING_H

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDir>

class CsvFormatting : public QThread
{
public:
    explicit CsvFormatting(QObject *parent = nullptr);

    void run();
    QString readingCsvFile(QString path);
    bool writingTextFile(QString data, QString orignalpath);
    void writeResponse(QString temppath);
    void writeStatus(QString total, QString current);
    void writeNames(QString name);
    void removingEnd();

    void getFileCsv(QStringList li);

private:
    QStringList csvFiles;
    QString tempPath;


};

#endif // CSVFORMATTING_H
