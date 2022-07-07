#include "shopactivityclass.h"
#include <QDate>

shopActivityClass::shopActivityClass()
{

}

QByteArray shopActivityClass::collectAvaiableItems(QString line)
{
   if(itemsdb())
   {
       QSqlQuery query;
       query.prepare(line);
       if(query.exec())
       {
           QByteArray data;

           while(query.next())
           {
               QString line = query.value(0).toString()+"@"+
                              query.value(1).toString()+"@"+
                              query.value(2).toString()+"@"+
                              query.value(3).toString()+"@"+
                              query.value(4).toString()+"@"+
                              query.value(5).toString()+"@"+
                              query.value(6).toString()+";";

               data.append(line.toLocal8Bit());
           }

           return data;
       }
   }
   return "none";
}

QByteArray shopActivityClass::sellingupdate(QString line)
{
   if(line != nullptr)
   {
       QStringList list = line.split(';');
       QString barcode = list[0];
       QString price = list[1];
       QString total = list.last();


       QStringList codes = barcode.split('@');
       QStringList prices = price.split('@');

       int sizes = codes.size() - 1;
       int counter = 0;

       qDebug()<<codes;
       qDebug()<<prices;

       if(itemsdb())
       {
         QSqlQuery query;
         QDate date = QDate::currentDate();
         QString dates = date.toString("dd-MM-yy");

         for(int i = 0; i < sizes; i++)
         {
             query.prepare("UPDATE items SET SoldStatus ='Sold', datesold='"+dates+"', soldprice='"+prices[i]+"' WHERE barcode='"+codes[i]+"';");
             if(query.exec())
             {
                 counter++;
             }
         }
       }

       if(counter == sizes)
       {
           if(bookshopcon())
           {
               QSqlQuery query;
                QString bal = nullptr, name = nullptr, number = nullptr;
               query.prepare("SELECT * FROM book;");
               if(query.exec())
               {


                   while(query.next())
                   {
                       bal = query.value(1).toString();
                       name = query.value(0).toString();
                       number = query.value(2).toString();
                   }

                   double balance  = bal.toDouble();
                   double amountin = total.toDouble();
                   balance = balance + amountin;

                   bal = QString::number(balance);

               }

               if(bal != nullptr)
               {
                   query.prepare("UPDATE book SET bookbalance='"+bal+"' WHERE booknumber ='"+number+"' AND bookname='"+name+"';");
                   if(query.exec())
                   {
                       counter += 2;
                   }
               }
           }
       }


       if(counter > sizes)
       {
           return "true";
       }


   }
   return "false";
}

QByteArray shopActivityClass::allcollectionitems(QString line)
{
     QByteArray data;

    if(itemsdb())
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
                               query.value(4).toString()+"@"+
                               query.value(5).toString()+"@"+
                               query.value(6).toString()+"@"+
                               query.value(7).toString()+"@"+
                               query.value(8).toString()+";";

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

QByteArray shopActivityClass::allcollectionbook(QString line)
{
    if(bookshopcon())
    {
        QSqlQuery query;
        query.prepare(line);
        if(query.exec())
        {
            QByteArray data;

            while(query.next())
            {
                QString line = query.value(0).toString()+"@"+
                               query.value(1).toString()+"@"+
                               query.value(2).toString();

                data.append(line.toLocal8Bit());
            }

            return data;
        }
    }
    return "none";
}

QByteArray shopActivityClass::savingiteminshop(QString line)
{
    QStringList item = line.split('/');
    QString offers = "No";
    if(item.at(4) != "No offer")
    {
       offers = "Yes";
    }
 if(item.size() > 0)
 {
    if(itemsdb())
    {
      QSqlQuery query;
      query.prepare("SELECT * FROM items WHERE barcode='"+item.at(2)+"';");
      if(query.exec())
      {
          QString line = nullptr;
          qDebug()<<"here reaced 1";
          while(query.next())
          {
            line = query.value(0).toString();
          }

          if(line == nullptr)
          {
              qDebug()<<"here reaced 3";
              query.prepare("INSERT INTO items(name,price,barcode,groups,description,SoldStatus,offer) VALUES('"+item.at(0)+"','"+item.at(1)+"','"+item.at(2)+"','"+item.at(3)+"','"+item.at(4)+"','Unsold','"+offers+"');");
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


QByteArray shopActivityClass::changecollect(QString barcode)
{
    if(itemsdb())
    {
        QString name, price,code,groups,descrip;
        QByteArray data;

      QSqlQuery query;
      query.prepare("SELECT * FROM items WHERE barcode='"+barcode+"';");
      if(query.exec())
      {

          while(query.next())
          {
              name =query.value(0).toString();
              price = query.value(1).toString();
              code = query.value(2).toString();
              groups = query.value(3).toString();
              descrip = query.value(4).toString();


          }
      }

      query.prepare("DELETE FROM items WHERE barcode='"+barcode+"';");
      query.exec();

      data.append(name.toStdString());
      data.append("@"+price.toStdString());
      data.append("@"+code.toStdString());
      data.append("@"+groups.toStdString());
      data.append("@"+descrip.toStdString());
      return data;

    }
    return "none";
}

QByteArray shopActivityClass::expeditures(QString line)
{
    bool done = false;
   // QString amount, QString code, QString  desc

    QStringList list = line.split('@');
    QString amount = list.at(0);
    QString code = list.at(1);
    QString desc = list.at(2);
    QString fullname = list.at(3);


    QString balance = nullptr, name = nullptr, number = nullptr;

    QString expectedamount = nullptr, verified = nullptr, exp = nullptr;

    if(releasemoney())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM Rmoney WHERE code='"+code+"';");
        if(query.exec())
        {
            while(query.next())
            {
                expectedamount = query.value(7).toString();
                verified = query.value(1).toString();
                exp = query.value(5).toString();
            }
        }
    }

    if(expectedamount == amount)
    {
        if(verified == "0")
        {
            if(exp == "false")
            {
                if(bookshopcon())
                {
                    QSqlQuery query;
                    query.prepare("SELECT * FROM book;");
                    if(query.exec())
                    {
                      while(query.next())
                      {
                          balance = query.value(1).toString();
                          name = query.value(0).toString();
                          number = query.value(2).toString();
                      }

                      double bala = balance.toDouble();
                      double amou = amount.toDouble();
                      balance = QString::number(bala);

                      if(bala > 100 && bala > amou && amou < bala - 100)
                      {
                          bala = bala - amou;
                          query.prepare("UPDATE book SET bookbalance='"+QString::number(bala)+"' WHERE bookname='"+name+"' AND booknumber='"+number+"';");
                          if(query.exec())
                          {
                             done = true;
                          }
                      }
                    }
                }

                if(done == true)
                {
                    QDate date = QDate::currentDate();
                    QString dates = date.toString("dd-MM-yy");
                    if(releasemoney())
                    {
                        QSqlQuery query;
                        query.prepare("UPDATE Rmoney SET verified ='1', amount='"+amount+"', description ='"+desc+"', exp ='true', ReleasedBy='"+fullname+"', Date='"+dates+"' WHERE code ='"+code+"';");
                        if(query.exec())
                        {

                            QString line = "Money has been withdrawn from Account: "+name+" Account number: "+number+" and Balance: "+balance;
                            return line.toLocal8Bit();
                        }
                    }
                }

            }
            else
            {
                return "This code is expired "+code.toLocal8Bit();
            }
        }
        else
        {
          return "The code is already used! "+code.toLocal8Bit();
        }
    }
    else
    {
      if(amount > expectedamount)
      {
          return "Failed Your amount is greater than expected amount to withdraw with this code"+code.toLocal8Bit();
      }
      else
      {
          return "Failed Your amount is less than expected amount to withdraw with this code"+code.toLocal8Bit();
      }
    }

    return "none";
}
















