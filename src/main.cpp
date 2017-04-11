#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DbManager::getInstance()->FileToDb("customerData.txt");

    return a.exec();
}
