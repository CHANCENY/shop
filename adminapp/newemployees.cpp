#include "newemployees.h"
#include "ui_newemployees.h"
#include <QMessageBox>


QString profilepicture = nullptr;
QString uasernamemadenow = nullptr;



newEmployees::newEmployees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newEmployees)
{
    ui->setupUi(this);


}

newEmployees::~newEmployees()
{
    delete ui;
}

bool newEmployees::checkUsername(QString username)
{
    if(employdbcon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM employees WHERE username ='"+username+"';");
        if(query.exec())
        {
            while(query.next())
            {
                if(query.value(1).toString() == username)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void newEmployees::result()
{
    QDir dir2;
    QString line = nullptr;
    QString filenames = dir2.absoluteFilePath("RECEIVEDDATA");
    QFile myfile1(filenames);
    myfile1.open(QIODevice::ReadOnly);
    if(myfile1.isOpen())
    {
        QTextStream in(&myfile1);
        line = in.readAll();
        myfile1.close();
    }


    if(line == "true")
    {
      QMessageBox::information(this,"Account Creation","You have successfully created account");
    }
    else
    {
         QMessageBox::information(this,"Account Creation","Account creation failed!");
    }

}

void newEmployees::on_pushButton_2_clicked()
{
    QString name = ui->name->text();
    QString username = ui->username->text();
    QString title = ui->title->currentText();
    QString pass1 = ui->password1->text();
    QString pass2 = ui->password2->text();

    // make sure not emepty and processed

    if(name != nullptr && username != nullptr && title != nullptr && pass1 != nullptr && pass2 != nullptr)
    {
      if(checkUsername(username))
      {
          if(pass1 == pass2)
          {
              QString line = "CreateAccountUser,"+name+","+username+","+title+","+pass1+","+profilepicture;
              QByteArray data;
              data.append(line.toStdString());
              uasernamemadenow = username;
              sockets.SendingToServer(data);
              QTimer::singleShot(1000,this,SLOT(result()));

          }
          else
          {
              ui->message->setText("Passwords don't match check passwords");
          }

      }
      else
      {
          ui->message->setText("Username already exist try another one");
      }
    }
    else
    {
        ui->message->setText("Fill in all field and submit!");
    }
}


void newEmployees::on_selectphoto_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Choice profile",QDir::homePath(),"Image *.jpg *.jpeg *.png");
    if(filename != nullptr)
    {
        QStringList list = filename.split('/');
        ui->photo->setText(list.last());
       profilepicture = filename;
    }
}

