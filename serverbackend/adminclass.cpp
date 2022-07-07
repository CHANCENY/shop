#include "adminclass.h"

AdminClass::AdminClass()
{

}

QByteArray AdminClass::employeesTable(QString line)
{
     QByteArray data;

    if(emmployeescon())
    {
        QSqlQuery query;
        query.prepare(line);
        if(query.exec())
        {


            while(query.next())
            {
                QString line = query.value(0).toString()+"@"+
                               query.value(1).toString()+"@"+
                               query.value(2).toString()+"@"+
                               query.value(3).toString()+"@"+
                               query.value(4).toString()+";";

                data.append(line.toLocal8Bit());
            }
        }
    }

    if(bookshopcon())
    {
       data.append("#");

       QSqlQuery query;
       query.prepare("SELECT * FROM book;");
       if(query.exec())
       {


           while(query.next())
           {
               QString line = query.value(0).toString()+"@"+
                              query.value(1).toString()+"@"+
                              query.value(2).toString();

               data.append(line.toLocal8Bit());
           }
       }
    }

    if(releasemoney())
    {
        data.append("#");

        QSqlQuery query;
        query.prepare("SELECT * FROM Rmoney;");
        if(query.exec())
        {


            while(query.next())
            {
                QString line = query.value(0).toString()+"@"+
                               query.value(1).toString()+"@"+
                               query.value(2).toString()+"@"+
                               query.value(3).toString()+"@"+
                               query.value(4).toString()+"@"+
                               query.value(5).toString()+"@"+
                               query.value(6).toString()+"@"+
                               query.value(7).toString()+"@"+
                               query.value(8).toString()+"@"+
                               query.value(9).toString()+";";

                data.append(line.toLocal8Bit());
            }

            return data;
        }
    }
    return "none";
}

QByteArray AdminClass::createBook(QString name, QString number)
{
   if(bookshopcon())
   {
       bool done = false;
       QSqlQuery query;
       query.prepare("INSERT INTO book(bookname,booknumber) VALUES('"+name+"','"+number+"');");
       if(query.exec())
       {
          done = true;
       }

       if(done == true)
       {
           QString line = nullptr;

           query.prepare("SELECT * FROM book WHERE booknumber='"+number+"';");
           if(query.exec())
           {
               while(query.next())
               {
                 line = query.value(0).toString()+","+query.value(2).toString();
               }

               if(line != nullptr)
               {
                   QStringList list = line.split(',');
                   if(list[0] == name && list.last() == number)
                   {
                     QString l = "true,"+line;
                     QByteArray data;
                     data.append(l.toStdString());
                     return data;
                   }
               }
           }
       }
   }
   return "false";
}

QByteArray AdminClass::changeUserInfo(QString obj)
{
   if(obj != nullptr)
   {
       QStringList list = obj.split('@');

       if(emmployeescon())
       {
           QSqlQuery query;
           query.prepare("UPDATE employees SET name='"+list[0]+"', username='"+list[1]+"', title='"+list[2]+"', password='"+list[3]+"', photo='"+list[4]+"' WHERE  username ='"+list[1]+"';");
           if(query.exec())
           {
               return "true";
           }
       }
   }
   return "false";
}

QByteArray AdminClass::deleteUser(QString username, QString password)
{
  if(emmployeescon())
  {
      QSqlQuery query;
      query.prepare("SELECT * FROM employees WHERE username ='"+username+"' AND password='"+password+"';");
      if(query.exec())
      {
          while(query.next())
          {
              if(query.value(1).toString() == username && query.value(3).toString() == password)
              {
                  query.prepare("DELETE FROM employees WHERE username ='"+username+"' AND password ='"+password+"';");
                  if(query.exec())
                  {
                      return "true";
                  }
              }
          }
      }
  }
  return "false";
}

QByteArray AdminClass::creatingAccountUser(QString name, QString username, QString title, QString password, QString photo)
{
   if(emmployeescon())
   {
       QSqlQuery query;
       query.prepare("INSERT INTO employees VALUES('"+name+"','"+username+"','"+title+"','"+password+"','"+photo+"');");
       if(query.exec())
       {
           return "true";
       }
   }
   return "false";
}

QByteArray AdminClass::releasingMoneyAuth(QString code, QString verified, QString expire, QString exp, QString amountex, QString admin)
{
  if(releasemoney())
  {
      QSqlQuery query;
      query.prepare("INSERT INTO Rmoney(code,verified,expire,exp,ExpectedAmount,AdminAuth) VALUES('"+code+"','"+verified+"','"+expire+"','"+exp+"','"+amountex+"','"+admin+"');");
      if(query.exec())
      {
          return "true";
      }
  }
  return "false";
}

QByteArray AdminClass::expiringcode(QString line)
{
    QStringList list = line.split('@');
    line = list[0]+", "+list[1];
    if(releasemoney())
    {
        QSqlQuery query;
        query.prepare(line);
        if(query.exec())
        {
            return "true";
        }
    }
    return "false";
}
