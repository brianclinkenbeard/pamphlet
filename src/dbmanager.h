#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QDebug>
#include "customer.h"
#include <vector>
#include<QFile>
#include<QTextStream>
#include"product.h"

class DbManager
{
public:
    static DbManager* getInstance();
    void FileToDb(const QString& path);
    void DbToCustomers();
    void DbToInventory();
    void CustomersToDb();
    std::vector<Customer>& getCustomers();
    void DeleteFromDb(QString name);
    bool isFirstExecution();
    std::vector<Product> getInventory();
    Product searchInInventory(QString itemName);

private:

    static DbManager* db;
    DbManager(const QString& path);
    QSqlDatabase customer_db;
    std::vector<Customer> customers;
    std::vector<Product> inventory;
};
#endif // DBMANAGER_H
