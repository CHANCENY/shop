#include "mining.h"
#include "ui_mining.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

static int pro = 0;

Mining::Mining(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mining)
{
    ui->setupUi(this);
    ui->progressBar_2->setMaximum(100);
    ui->progressBar_2->setTextVisible(false);
    ui->progressBar->setTextVisible(true);

   this->setStyleFile();
    this->readInstruction();
    ui->pushButton_2->setVisible(false);

    progress = new QTimer(this);
    fileposition = new QTimer(this);
    csvF = new QTimer(this);
    connect(progress,SIGNAL(timeout()),this,SLOT(progressing()));
    connect(fileposition,SIGNAL(timeout()),this,SLOT(fileBeingProcessed()));
    connect(csvF,SIGNAL(timeout()),this,SLOT(waitingforResponse()));

}

Mining::~Mining()
{
    delete ui;
}

void Mining::setStyleFile()
{   
    QFile myfile(":/sty/style/MacOs.txt");
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen()){
        QString line = myfile.readAll();
        myfile.close();      
        if(line != nullptr){
            setStyleSheet(line);
        }
    }
}

void Mining::readInstruction()
{
   QFile myfile(":/sty/style/Instruction.txt");
   myfile.open(QIODevice::ReadOnly);
   if(myfile.isOpen()){

       QString inst = myfile.readAll();

       if(inst != nullptr)
       {
           ui->instructions->setText(inst);
       }
   }
}

bool Mining::checkSavingFile(QString path)
{
   if(path != nullptr)
   {
       QFileInfo info(path);

       if(info.suffix() == "txt")
       {
           if(info.size() != 0)
           {
               QMessageBox::warning(0,"Warning","The saving file selected is not empty please select txt file which is empty");
               this->savingFileName = nullptr;
               return false;
           }
           return true;
       }
       else
       {
           QMessageBox::warning(0,"File type","Saving File Type is not allowed");
           this->savingFileName = nullptr;
       }
   }
   else
   {
       QMessageBox::warning(0,"warning","You have not selected saving file");
   }
   return false;
}

void Mining::on_pushButton_clicked()
{

    //collection files from computer file system
    QStringList pathsFile = QFileDialog::getOpenFileNames(0,"CHOOSE FILES TO PROCESS",QDir::homePath(),"*.txt");

    //check if files collected
    if(!pathsFile.isEmpty())
    {
        savingUploadAgain:

        //taking file name where to save data
        QString savingFile = QFileDialog::getOpenFileName(0,"SELECT FILE TO SAVE PROCESSED DATA",QDir::homePath(),"*.txt");

       if(this->checkSavingFile(savingFile))
       {
        //check if file taken
        if(savingFile != nullptr)
        {
            QFileInfo info;
            for(int i = 0; i < pathsFile.size(); i++){

               //show file to be processed in box
               info.setFile(pathsFile[i]);
               ui->listWidget->addItem(info.fileName());
            }

            info.setFile(savingFile);
            ui->savingfile->setText("Saving data: "+info.fileName());
            this->filePaths = pathsFile;
            this->savingFileName = savingFile;
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setVisible(true);
        }
      }
      else{
            goto savingUploadAgain;
         }
    }

}

void Mining::on_pushButton_2_clicked()
{
    if(!this->filePaths.isEmpty() && this->savingFileName != nullptr){

        mythread = new MythreadMinningFiles;
        mythread->getFileNames(this->filePaths,this->savingFileName);
        mythread->start();

        ui->pushButton_2->setIcon(QIcon(":/sty/style/data-processing.png"));
        ui->pushButton_2->setText("Progressing in progress...");
        ui->status->setText("processing...");
        this->progress->start(1000);
        this->fileposition->start(2000);
        ui->pushButton_2->setEnabled(false);

    }
}

void Mining::progressing()
{
    ui->progressBar_2->setTextVisible(true);
    QDir dir;
    QString filename = dir.absoluteFilePath("temp1");
    QString line = nullptr;

    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly);
    if(myfile.isOpen()){

        line = myfile.readAll();
        myfile.close();
    }


    if(line != nullptr){
        QStringList list = line.split(',');

        int total = list.first().toInt();
        int current = list.last().toInt();

        ui->progressBar->setMaximum(total);
        ui->progressBar->setValue(current);


        if(this->mythread->isFinished()){

            ui->pushButton_2->setIcon(QIcon(":/sty/style/start.png"));
            ui->pushButton_2->setText("Start processing");
            ui->pushButton_2->setVisible(true);
            ui->pushButton_2->setEnabled(true);
            ui->status->setText("Finished Files"+list.first()+" of "+list.last());
            ui->pushButton->setEnabled(true);
             ui->progressBar_2->setTextVisible(false);
             pro = 0;
            this->savingFileName.clear();
            ui->listWidget->clear();
            this->progress->stop();
            this->fileposition->stop();
            QFile::remove("temp1");

            foreach(QString del, this->filePaths)
            {
                QFile::remove(del);
            }

            ui->progressBar_2->setValue(100);
            if(ui->progressBar_2->value() == 100)
            {
                 this->filePaths.clear();
                QMessageBox::information(0,"Finished alert","Processing of your data has finished");
            }

        }        
    }

    if(mythread->isRunning()){
        ui->progressBar_2->setValue(pro);
        pro++;
        if(pro == 100){
            pro = 0;
        }
    }
}

void Mining::fileBeingProcessed()
{
    QDir dir;
    QString file = dir.absoluteFilePath("temp2");
    QString line = nullptr;

    QFile myfile(file);
    myfile.open(QIODevice::ReadOnly);

    if(myfile.isOpen()){

       line = myfile.readAll();
       myfile.close();
    }

    QFile::remove("temp2");

    if(line != nullptr)
        ui->filebeing->setText("File: "+line);
}

void Mining::waitingforResponse()
{
    QDir dir;
    QString file = dir.absoluteFilePath("temp3");
    QString line = nullptr;

    QFile myfile(file);
    myfile.open(QIODevice::ReadOnly);

    if(myfile.isOpen()){

       line = myfile.readAll();
       myfile.close();
    }

     QFile::remove("temp3");
    if(line != nullptr)
    {

       csvF->stop();
       QStringList list = line.split('\n');
       foreach(QString li, list)
       {
           if(li != nullptr){
             this->filePaths.append(li.trimmed());
           }
       }
      ui->listWidget->addItems(this->filePaths);
      QString saving = QFileDialog::getOpenFileName(0,"SELECT SAVING FILE",QDir::homePath(),"*.txt");
      if(saving != nullptr)
      {
         if(this->checkSavingFile(saving))
         {
             this->savingFileName = saving;
             ui->pushButton_2->setVisible(true);
             ui->pushButton_2->setEnabled(true);
         }

      }
    }

}

void Mining::on_pushButton_3_clicked()
{
    QStringList csvFiles = QFileDialog::getOpenFileNames(0,"SELECT CSV FILES",QDir::homePath(),"*.csv");
    if(!csvFiles.isEmpty())
    {
       myCsvformator = new CsvFormatting;
       myCsvformator->getFileCsv(csvFiles);
       myCsvformator->start();
       csvF->start(1000);
    }
}

