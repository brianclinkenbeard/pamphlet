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
    QString rate;

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
        in.readLine();//reads \n
        rate = in.readLine();
        if(in.readLine().toLower()=="key"){
            value = 1;
        }else{
            value = 0;
        }
        in.readLine();//reads the empty line

        qry.prepare("insert into Customer_Info (Company,Street_Address,City,State,Zip,Value) values('"+company+"','"+streetAddress+"','"+city+"','"+ state+"','"+zip+"','"+QString::number(value)+"')");
        if(qry.exec()){
            qDebug()<<"data saved to Customer_Info";
        }
        else{
            qDebug()<<"unable to save data to Customer_Info";
        }
        qry.prepare("insert into Customer_Rating (Company,Interest) values('"+company+"','"+rate+"')");
        if(qry.exec()){
            qDebug()<<"data saved to Customer_Rating";
        }
        else{
            qDebug()<<"unable to save data to Customer_Rating";
        }

    }
    inFile.flush();
    inFile.close();
//    customer_db.close();
}

void DbManager::DbToCustomers()
{
    Customer customer;
    Customer tempCustomer;
    QSqlQuery qry;
    QSqlQuery qry2;
    qry.prepare("SELECT * FROM Customer_Info");

    if(!qry.exec()){
        qDebug()<<"unable to execute query";
    }
    int i = 0;
    while(qry.next())
    {
        customer.setName(qry.value(0).toString());
        customer.setCustomerAddress(qry.value(1).toString(), qry.value(2).toString(), qry.value(3).toString(), qry.value(4).toString());
        customer.setValue(qry.value(5).toInt());
        qry2.prepare("SELECT Interest FROM Customer_Rating WHERE Company = '"+customer.getName()+"'");//to find and select value
        if(!qry2.exec()){
            qDebug()<<"unable to execute query";
        }
        if(qry2.next())//to get the value out of query
            customer.setInterest(qry2.value(0).toString());
        customers.push_back(customer);
        tempCustomer = customers.at(i);
        qDebug()<<tempCustomer.getName();
        qDebug()<<tempCustomer.getCustomerAddress().getCity();
        qDebug()<<tempCustomer.getCustomerAddress().getStreet();
        qDebug()<<tempCustomer.getCustomerAddress().getState();
        qDebug()<<tempCustomer.getCustomerAddress().getZip();
        qDebug()<<"key: "<<QString::number(tempCustomer.getValue());
        qDebug()<<"interest: "<<QString::number(tempCustomer.getInterest());
        i++;
    }
}

std::vector<Customer> DbManager::getCustomers()
{
    return customers;
}
