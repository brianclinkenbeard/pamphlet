#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QDebug>
#include "customer.h"
#include <vector>

class DbManager
{
public:
    DbManager(const QString& path);
    static DbManager* getInstance();
private:
    static DbManager* db;
    QSqlDatabase customer_db;
    std::vector<Customer> customers;
};

#endif // DBMANAGER_H
