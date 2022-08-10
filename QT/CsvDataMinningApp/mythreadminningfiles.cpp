#include "mythreadminningfiles.h"

MythreadMinningFiles::MythreadMinningFiles()
{

}

void MythreadMinningFiles::run()
{
   int sizes = this->filesToProcess.size();
   this->total = sizes;

   for(int i = 0; i < sizes; i++)
   {

       this->currentposition = i;
       QString path = this->filesToProcess[i];
       if(path != nullptr){
           //write to display
           this->fileBeingProcced(path);
           this->writingValuesProgressing(QString::number(sizes),QString::number(i+1));


           //call to open and read data
           this->ReadFileData(path);
           this->processingDataFromFile();

       }
       if(!this->listMadeFromDataRead.isEmpty()){

           this->constructData();

           this->listMadeFromDataRead.clear();
           this->dataReadFromFile.clear();

       }
   }

   this->removeExtraCommaEnd();


}

void MythreadMinningFiles::ReadFileData(QString path)
{
    QDir dir;
    QString filename = dir.absoluteFilePath(path);

    //reading data from file
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()){
        this->dataReadFromFile = file.readAll();
        file.close();
    }
}

void MythreadMinningFiles::constructData()
{

    int sizeList = this->listMadeFromDataRead.size();

    for(int i = 0; i < sizeList; i++)
    {

        //collecting one videos with its data at once
        QStringList content = this->listMadeFromDataRead[i].split(';');

        QStringList list = content;

        if(!list.isEmpty())
        {
             QString arraymade = this->makingArray(list);

             this->writingFileAppend(arraymade += ",");
        }


    }

}

QString MythreadMinningFiles::makingArray(QStringList data)
{
   QString dataLine ="{";
   QString listCategory = "Category:[";

   if(!data.isEmpty())
   {
       int sizes = data.size();

       for(int i = 0; i < sizes; i++)
       {
           if(i == 1)
           {
               QString line = "Title:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 0)
           {
               QString line = "LinkVideo:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 2)
           {
               QString line = "Duration:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 3)
           {
               QString line = "ThumbImage:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 4)
           {
               QString line = "Iframe:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 6)
           {
               QString line = "Unknown:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 7)
           {
               QString line = "Id:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 8)
           {
               QString line = "Type:"; line += "'"+data[i]+"',"; dataLine += line;
           }
           if(i == 9)
           {
               QString line = "Quality:"; line += "'"+data[i]+"',"; dataLine += line;
           }

           if(i == 5)
           {
               QString line = data[i];
               QStringList lists = line.split(',');


               for(int j = 0; j < lists.size(); j++)
               {

                   if(j < lists.size()){
                       QString line = "'"+lists[j]+"'";
                       listCategory = listCategory +line+",";
                   }
                   if(j == lists.size() - 1){

                       QString line = "'"+lists[j]+"'";
                       listCategory = listCategory +line+"]";
                   }
               }
           }
       }
      return  dataLine += listCategory +"}";
   }

   return nullptr;
}

void MythreadMinningFiles::getFileNames(QStringList li, QString savingFileName)
{
    this->filesToProcess = li;
    this->fileToBeMadeSaving = savingFileName;
}

void MythreadMinningFiles::processingDataFromFile()
{
    //making list of videos with they attached data
   QStringList list = this->dataReadFromFile.split("\r\n");

   foreach(QString line, list)
   {
       if(line != nullptr)
       {
            this->listMadeFromDataRead .append(line.trimmed());
       }
   }

}

void MythreadMinningFiles::writingFileAppend(QString line)
{
    QDir dir;
    QString filename = dir.absoluteFilePath(this->fileToBeMadeSaving);
    QFile myfile(filename);


    myfile.open(QIODevice::WriteOnly|QIODevice::Append|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream writing(&myfile);
        writing<<line+"\n";
        myfile.flush();
        myfile.close();
    }
}

void MythreadMinningFiles::writingValuesProgressing(QString totalfile, QString onNumber)
{
    QFile myfile("temp1");
    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream in(&myfile);
        in<<totalfile<<","<<onNumber;
        myfile.flush();
        myfile.close();

    }
}

void MythreadMinningFiles::fileBeingProcced(QString file)
{
    QFileInfo info(file);

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

void MythreadMinningFiles::removeExtraCommaEnd()
{
    QString data = nullptr;
    QDir dir1;
    QString filename1 = dir1.absoluteFilePath(this->fileToBeMadeSaving);
    QFile myfile1(filename1);


    myfile1.open(QIODevice::ReadOnly);
    if(myfile1.isOpen())
    {
        QTextStream reads(&myfile1);
        data = reads.readAll();
        myfile1.close();
    }

    QString data2 = nullptr;
    if(data != nullptr)
    {
      data = data.trimmed();

     for(int i = 0; i < data.size(); i++){

         if(i < data.size() - 1 && data[i] != '\n')
         {
             data2 += data[i];
         }
         if(i == data.size() - 1){
             data2 += " ";
         }
     }
    }

    if(data2 != nullptr)
    {


    QDir dir;
    QString filename = dir.absoluteFilePath(this->fileToBeMadeSaving);
    QFile myfile(filename);


    myfile.open(QIODevice::WriteOnly|QFile::Text);
    if(myfile.isOpen())
    {
        QTextStream writing(&myfile);
        writing<<data2;
        myfile.flush();
        myfile.close();
    }
  }
}
