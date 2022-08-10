#ifndef MINING_H
#define MINING_H

#include <QMainWindow>
#include <QFile>
#include "mythreadminningfiles.h"
#include <QTimer>
#include "csvformatting.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Mining; }
QT_END_NAMESPACE

class Mining : public QMainWindow
{
    Q_OBJECT

public:
    Mining(QWidget *parent = nullptr);
    ~Mining();

    void setStyleFile();
    void readInstruction();
    bool checkSavingFile(QString path);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

public slots:
    void progressing();
    void fileBeingProcessed();
    void waitingforResponse();

private:
    Ui::Mining *ui;
    QStringList filePaths;
    QString savingFileName;

    QTimer *progress;
    QTimer *fileposition;
    MythreadMinningFiles *mythread;
    CsvFormatting *myCsvformator;
    QTimer *csvF;
};
#endif // MINING_H
