#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*read from file todatabase only if it is the first time*/
   if(DbManager::getInstance()->isFirstExecution())
        DbManager::getInstance()->FileToDb(":/res/customerData.txt");
    DbManager::getInstance()->DbToInventory();
    DbManager::getInstance()->DbToCustomers();

    MainWindow w;
    w.show();


    return a.exec();
}
