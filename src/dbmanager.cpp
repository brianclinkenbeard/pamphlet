#include "dbmanager.h"

DbManager* DbManager::db = NULL;

DbManager* DbManager::getInstance()
{
    if (db == NULL) {
        db = new DbManager("pamphletDB.db");
        return db;
    } else {
        return db;
    }
}

DbManager::DbManager(const QString& path)
{
    customer_db = QSqlDatabase::addDatabase("QSQLITE");
    customer_db.setDatabaseName(path);

    if (!customer_db.open()) {
        qDebug() << "Error: connection with database fail";
    }
    else {
        qDebug() << "Database: connection ok";
    }
}
