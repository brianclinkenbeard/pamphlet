#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "address.h"

enum Interest {HIGH, MEDIUM, LOW};  // Customer's level of interest in our product

class Customer
{
public:
    Customer();
    Customer(QString, Interest, bool, QString, QString, QString, QString);
    Customer(const Customer&);
    void setName(QString);
    void setCustomerAddress(QString, QString, QString, QString);
    void setInterest(Interest);
    void setValue(bool);
    ~Customer();
private:
    QString companyName;
    Address address;
    Interest interest;
    bool value; // if true "key", if false "nice to have"
};

#endif // CUSTOMER_H
