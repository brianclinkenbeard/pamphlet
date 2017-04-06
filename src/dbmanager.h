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
private:
    QSqlDatabase customer_db;
    std::vector<Customer> customers;
};

#endif // DBMANAGER_H
