#include "validateuser.h"

validateuser::validateuser()
{
  qDebug()<<"Validating User Employee";
}

QByteArray validateuser::loginuser(QString username, QString password)
{
   if(emmployeescon())
   {
       QSqlQuery query;
       query.prepare("SELECT * FROM employees WHERE username ='"+username+"' AND password ='"+password+"';");
       if(query.exec())
       {

           while(query.next())
           {
               if(username == query.value(1).toString() && password == query.value(3).toString() && query.value(2).toString() == "Teller")
               {
                QString username = query.value(1).toString();
                QString name = query.value(0).toString();
                QString profile = query.value(4).toString();
                QString title = query.value(2).toString();
                
                this->userfound.append("true,");
                this->userfound.append(name.toStdString());
                this->userfound.append(","+username.toStdString());
                this->userfound.append(","+title.toStdString());
                this->userfound.append(","+profile.toStdString());
                
                return this->userfound;

               }
           }

       }
   }
   return "false";
}

QByteArray validateuser::loginaccountant(QString username, QString password)
{
    if(emmployeescon())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM employees WHERE username ='"+username+"' AND password ='"+password+"';");
        if(query.exec())
        {

            while(query.next())
            {
                if(username == query.value(1).toString() && password == query.value(3).toString() && query.value(2).toString() == "Accountant")
                {
                 QString username = query.value(1).toString();
                 QString name = query.value(0).toString();
                 QString profile = query.value(4).toString();
                 QString title = query.value(2).toString();

                 this->userfound.append("true,");
                 this->userfound.append(name.toStdString());
                 this->userfound.append(","+username.toStdString());
                 this->userfound.append(","+title.toStdString());
                 this->userfound.append(","+profile.toStdString());

                 return this->userfound;

                }
            }

        }
    }
    return "false";
}

QByteArray validateuser::loginadmin(QString username, QString password)
{
   if(emmployeescon())
   {
       QByteArray data;
       QSqlQuery query;
       query.prepare("SELECT * FROM employees WHERE username ='"+username+"' AND password ='"+password+"';");
       if(query.exec())
       {
           while(query.next())
           {
               if(query.value(1).toString() == username && query.value(3).toString() == password && query.value(2).toString() == "Admin")
               {
                   QString username = query.value(1).toString();
                   QString name = query.value(0).toString();
                   QString profile = query.value(4).toString();
                   QString title = query.value(2).toString();

                   this->userfound.append("true,");
                   this->userfound.append(name.toStdString());
                   this->userfound.append("@"+username.toStdString());
                   this->userfound.append("@"+title.toStdString());
                   this->userfound.append("@"+profile.toStdString());

                   return this->userfound;
               }
           }
       }
   }
   return "false";
}
