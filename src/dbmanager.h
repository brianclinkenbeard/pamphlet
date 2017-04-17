#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QDebug>
#include "customer.h"
#include <vector>
#include<QFile>
#include<QTextStream>

class DbManager
{
public:
    static DbManager* getInstance();
    void FileToDb(const QString& path);
    void DbToCustomers();

private:

    static DbManager* db;
    DbManager(const QString& path);
    QSqlDatabase customer_db;
    std::vector<Customer> customers;
};
#endif // DBMANAGER_H
