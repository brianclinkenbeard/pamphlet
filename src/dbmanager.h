#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql>
#include <QDebug>
#include "customer.h"
#include <vector>
#include<QFile>
#include<QTextStream>
#include"product.h"

/**
 * @brief DB Manager
 * Manages database and includes operations to read, write and edit the SQLite file
 */
class DbManager
{
public:
    /** singleton */
    static DbManager* getInstance();
    /** reads from database */
    void FileToDb(const QString& path); /**< path to database file */
    /** writes to customer vector from database */
    void DbToCustomers();
    void DbToInventory();
    void CustomersToDb();
    std::vector<Customer>& getCustomers();
    void DeleteFromDb(QString name);
    bool isFirstExecution();
    std::vector<Product> getInventory();
    Product searchInInventory(QString itemName);
    bool addTestimonial(QString, QString);
    QString getTestimonials();

private:
    std::vector<Customer> customers;
    static DbManager* db;
    DbManager(const QString& path);
    QSqlDatabase customer_db;

    std::vector<Product> inventory;
};
#endif // DBMANAGER_H
