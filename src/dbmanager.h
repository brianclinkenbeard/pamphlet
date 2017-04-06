#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QDebug>

class DbManager
{
public:
    DbManager(const QString& path);
private:
    QSqlDatabase customer_db;
};

#endif // DBMANAGER_H
