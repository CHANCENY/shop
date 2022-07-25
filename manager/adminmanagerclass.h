#ifndef ADMINMANAGERCLASS_H
#define ADMINMANAGERCLASS_H
#include "databasesconnectionclass.h"


class adminManagerClass: public DataBasesConnectionClass
{
public:
    adminManagerClass();
    adminManagerClass(QString comm);
    int lastHistroy();
    void homeCommandBased();
    void helpFunction();
    void historyCollecting(QString hist, int flag);
    void DatabaseList();
    void openDatabase(QString databasename);
    void showTables();
    void closeDatabase();
    void createTables(QString tablequery);
    void insertingData(QString insertquery);
    void homeCommandBased2(std::string line);
    void updateTableValues(QString updatequery);
    void removeTable(QString droptablequery);
    void deleteInTable(QString deletequery);
    void viewValuesInTable(QString viewquery);
    void newWindow();
    void loginAdmin(QString username, QString password);
    void login();
    void logout();
    void home();


};

#endif // ADMINMANAGERCLASS_H
