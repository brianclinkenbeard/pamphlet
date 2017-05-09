#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*read from file todatabase only if it is the first time*/
   if(DbManager::getInstance()->isFirstExecution())
        DbManager::getInstance()->FileToDb(":/res/customerData.txt");

    DbManager::getInstance()->DbToCustomers();
    DbManager::getInstance()->DbToInventory();
    return a.exec();
}
