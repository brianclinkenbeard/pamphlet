#include "dbmanager.h"

DbManager* DbManager::db = NULL;

DbManager::DbManager(const QString& path):customers()
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

DbManager* DbManager::getInstance()
{
    if(db == NULL){
        db  = new DbManager("pamphletDB.db");
        return db;
    }else{
        return db;
    }
}

void DbManager::FileToDb(const QString& path)
{
    //int commaIndex;
    QString company;
    QString streetAddress;
    QString city;
    QString state;
    QString zip;//TEXT in the table for starting zero(s), can be changed to integer
    int value;

    QFile inFile(path);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"Could not open the file.";
        return;
    }
    QSqlQuery qry;
    QTextStream in(&inFile);

    if (!customer_db.open()) {
        qDebug() << "Error: connection with database fail";
        return;
    }
    QString tempCity;
    while(!in.atEnd()){
        company = in.readLine();
        streetAddress = in.readLine();
        in.operator>>(city);
        while(city[city.size()-1] != ',')
        {
            in.operator>>(tempCity);
            city = city +" "+ tempCity;
        }
        in.operator >>(state);
        in.operator >>(zip);
        in.readLine();
        in.readLine();
        if(in.readLine().toLower()=="key"){
            value = 1;
        }else{
            value = 0;
        }
        in.readLine();

        qry.prepare("insert into Customer_Info (Company,Street_Address,City,State,Zip,Value) values('"+company+"','"+streetAddress+"','"+city+"','"+ state+"','"+zip+"','"+QString::number(value)+"')");
     //    qry.prepare("insert into CustomerInfo (Street) values('"+streetAddress+"')");
        if(qry.exec()){
            qDebug()<<"data saved to data base";
        }
        else{
            qDebug()<<"unable to execute query";
        }

    }
    inFile.flush();
    inFile.close();
//    customer_db.close();
}

void DbManager::DbToCustomers()
{
    QString company;
    Customer customer;
    Customer tempCustomer;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Customer_Info");
    if(qry.exec()){
        qDebug()<<"able to execute query";
    }
    else{
        qDebug()<<"unable to execute query";
    }
    int i = 0;
    while(qry.next())
    {
        customer.setName(qry.value(0).toString());
        customer.setCustomerAddress(qry.value(1).toString(), qry.value(2).toString(), qry.value(3).toString(), qry.value(4).toString());
        customer.setValue(qry.value(5).toInt());
        //customer.setInterest(qry.value().toString());
        customers.push_back(customer);
        tempCustomer = customers.at(i);
        qDebug()<<tempCustomer.getName();
        qDebug()<<tempCustomer.getCustomerAddress().getCity();
        qDebug()<<tempCustomer.getCustomerAddress().getStreet();
        qDebug()<<tempCustomer.getCustomerAddress().getState();
        qDebug()<<tempCustomer.getCustomerAddress().getZip();
        qDebug()<<QString::number(tempCustomer.getValue());
        i++;
    }

}
