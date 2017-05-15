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
        if (QSysInfo::productType() == "osx" || QSysInfo::productType() == "macos") {
            db  = new DbManager("../../../pamphletDB.db");
        } else {
            db = new DbManager("pamphletDB.db");
        }
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
        qry.prepare("insert into Transactions (Company,W, X, Y, Z) values('"+company+"','"+QString::number(0)+"','"+QString::number(0)+"','"+QString::number(0)+"','"+QString::number(0)+"')");
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
    QSqlQuery qry;
    QSqlQuery qry2;
    QSqlQuery qry3;
  //  DbToInventory();
    qry.prepare("SELECT * FROM Customer_Info");

    if(!qry.exec()){
        qDebug()<<"unable to execute query";
    }
    int i =0;
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
        qry3.prepare("SELECT W, X, Y, Z FROM Transactions WHERE Company = '"+customer.getName()+"'");
        if(!qry3.exec()){
            qDebug()<<"unable to execute query";
        }
        Product product1;
        Product product2;
        Product product3;
        Product product4;
        if(qry3.next()){//to get the value out of query

            product1 = searchInInventory("W");
            product1.setQuantity(qry3.value(0).toInt());
            product2 = searchInInventory("X");
            product2.setQuantity(qry3.value(1).toInt());
            product3 = searchInInventory("Y");
            product3.setQuantity(qry3.value(2).toInt());
            product4 = searchInInventory("Z");
            product4.setQuantity(qry3.value(3).toInt());
        }
       /* customer.addProduct(product1);
        customer.addProduct(product2);
        customer.addProduct(product3);
        customer.addProduct(product4);*///why it does not work when customer is pushed to customers by not changing the size of products???
        customers.push_back(customer);
        (*(customers.begin()+i)).addProduct(product1);
        (*(customers.begin()+i)).addProduct(product2);
        (*(customers.begin()+i)).addProduct(product3);
        (*(customers.begin()+i)).addProduct(product4);
        qDebug()<<customers.at(i).getName();
        qDebug()<<customers.at(i).getProducts().size();//size should be 4
        i++;
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
}

std::vector<Customer>& DbManager::getCustomers()
{
    return customers;
}

void DbManager::CustomersToDb()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
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
        qry3.prepare("insert into Transactions (Company,W, X, Y, Z) values('"+it->getName()+"','"+QString::number(0)+"','"+QString::number(0)+"','"+QString::number(0)+"','"+QString::number(0)+"')");
        qry3.exec();
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
    QSqlQuery qry3;
    qry1.prepare("DELETE FROM Customer_Info WHERE Company = '"+name+"'");
    qry1.exec();
    qry2.prepare("DELETE FROM Customer_Rating WHERE Company = '"+name+"'");
    qry2.exec();
    qry3.prepare("DELETE FROM Transactions WHERE Company = '"+name+"'");
    qry3.exec();

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

bool DbManager::addTestimonial(QString customer, QString testimonial)
{
    QSqlQuery qry;

    if (!customer_db.open()) {
        qDebug() << "Failed to connect with database.";
        return false;
    }

    qry.prepare("INSERT INTO Testimonials (Company, Testimonial) VALUES(:Company,:Testimonial)");

    qry.bindValue(":Company", customer);
    qry.bindValue(":Testimonial", testimonial);

    if (qry.exec()) {
        qDebug() << "Successfully executed query";
        return true;
    } else {
        qDebug() << "Unable to execute query";
        return false;
    }
}

/**
 * @brief DbManager::getTestimonials
 * Returns a formatted string of testimonials.
 * @return
 */
QString DbManager::getTestimonials()
{
    QSqlQuery qry;

    /** check if database is open */
    if (!customer_db.open()) {
        qDebug() << "Failed to connect with database.";
        return "Error";
    }

    QStringList testimonials;
    QStringList companies;

    qry.prepare("SELECT * FROM Testimonials");
    qry.exec();

    /** get testimonials from database */
    int tCount = 0;
    while (qry.next()) {
        companies << qry.value(0).toString();
        testimonials << qry.value(1).toString();
        tCount++;
    };

    QString tString;

    /** format the testimonials */
    for (int i = 0; i < tCount; ++i) {
        /* this is a stupid way of formatting this but oh well */
        tString.append("\"");
        tString.append(testimonials.at(i));
        tString.append("\"\n\t—");
        tString.append(companies.at(i));
        /* dont add newlines on last element */
        if (i < tCount - 1)
            tString.append("\n\n");
    }

    /** return the testimonial string */
    return tString;
}
