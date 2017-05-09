#include "dbmanager.h"

DbManager* DbManager::db = NULL;

DbManager::DbManager(const QString& path):customers(), inventory()
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

        /*
         * location[0] - "[city]"
         * location[1] - "[state] [zip]"
         */
        QStringList location = in.readLine().split(", ");
        city = location[0];
        state = location[1].section(" ", 0, 0);
        zip = location[1].section(" ", 1, 1);

        rate = in.readLine();

        in.readLine().toLower() == "key" ? value = 1 : value = 0;

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
   /*     tempCustomer = customers.at(i);
        qDebug()<<tempCustomer.getName();
        qDebug()<<tempCustomer.getCustomerAddress().getCity();
        qDebug()<<tempCustomer.getCustomerAddress().getStreet();
        qDebug()<<tempCustomer.getCustomerAddress().getState();
        qDebug()<<tempCustomer.getCustomerAddress().getZip();
        qDebug()<<"key: "<<QString::number(tempCustomer.getValue());
        qDebug()<<"interest: "<<QString::number(tempCustomer.getInterest());*/
    }
}

void DbManager::DbToInventory()
{
    Product product;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Inventory");
    if(!qry.exec())
    {
        qDebug()<<"Unable to read from invetory table";
    }
    while(qry.next())
    {
        product.setName(qry.value(0).toString());
        product.setPrice(qry.value(1).toDouble());
        inventory.push_back(product);
    }
    /*
    for(unsigned int i = 0; i<inventory.size(); i++)
    {
        qDebug()<<inventory.at(i).getName();
        qDebug()<<inventory.at(i).getPrice();
    }*/
}

std::vector<Customer>& DbManager::getCustomers()
{
    return customers;
}

void DbManager::CustomersToDb()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    if (!customer_db.open()) {
        qDebug() << "Error: connection with database fail";
        return;
    }

    for(std::vector<Customer>::iterator it =customers.begin(); it<customers.end(); it++)
    {
        /*saving to customer info table*/
        qry1.prepare("insert into Customer_Info (Company,Street_Address,City,State,Zip,Value) values('"+it->getName()+"','"+it->getCustomerAddress().getStreet()+"','"+it->getCustomerAddress().getCity()+"','"+ it->getCustomerAddress().getState()+"','"+it->getCustomerAddress().getZip()+"','"+QString::number(it->getValue())+"')");
        qry1.exec();

        /*saving to custmer rating table*/
        QString interest;
        switch (it->getInterest())
        {
            case 0:
                interest = "not interested";
                break;
            case 1:
                interest = "somewhat interested";
                break;
            case 2:
                interest = "very interested";
        }

        qry2.prepare("insert into Customer_Rating (Company, Interest) values('"+it->getName()+"', '"+interest+"')");
        qry2.exec();
    }
}

bool DbManager::isFirstExecution()
{
    QSqlQuery qry;
    bool value;
    qry.prepare("SELECT First FROM First_Execution");
    if(!qry.exec()){
        qDebug()<<"unable to execute query";
    }
    if(qry.next())
        value = qry.value(0).toBool();
    if(value){
        qry.prepare("UPDATE First_Execution SET First = "+QString::number(0));
        if(!qry.exec())
            qDebug()<<"could not change the value of first";
    }
    return value;

}

void DbManager::DeleteFromDb(QString name)
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    qry1.prepare("DELETE FROM Customer_Info WHERE Company = '"+name+"'");
    qry1.exec();
    qDebug()<<"name in function db: "<<name;
    qry2.prepare("DELETE FROM Customer_Rating WHERE Company = '"+name+"'");
    if(qry2.exec()){
        qDebug()<<"data deleted from Customer_rating";
    }
    else{
        qDebug()<<"unable to exec qry";
    }
}

std::vector<Product> DbManager::getInventory()
{
    return inventory;
}

Product DbManager::searchInInventory(QString itemName)
{
    unsigned int i;
    for (i = 0; i<inventory.size(); i++)
    {
        if(itemName == inventory.at(i).getName())
            break;
    }
    return inventory.at(i);
}
