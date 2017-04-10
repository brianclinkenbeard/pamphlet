#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QDebug>
#include "customer.h"
#include <vector>

class DbManager
{
public:
    static DbManager* getInstance();
private:
    DbManager(const QString& path);
    static DbManager* db;
    QSqlDatabase customer_db;
    std::vector<Customer> customers;
};

#endif // DBMANAGER_H
