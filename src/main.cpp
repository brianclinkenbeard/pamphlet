#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DbManager::getInstance()->FileToDb(":/res/customerData.txt");
    DbManager::getInstance()->DbToCustomers();

    return a.exec();
}
