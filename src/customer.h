#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "address.h"

enum Interest {LOW=0, MEDIUM, HIGH};  // Customer's level of interest in our product

class Customer
{
public:
    Customer();
    Customer(QString, Interest, bool, QString, QString, QString, QString);
    Customer(const Customer&);
    void setName(QString);
    void setCustomerAddress(QString, QString, QString, QString);
    void setInterest(Interest);
    void setInterest(QString);
    void setValue(int);
    QString getName() const;
    Address getCustomerAddress() const;
    Interest getInterest() const;
    int getValue() const;
    bool operator <(const Customer&) const;
    bool operator >(const Customer&) const;
    ~Customer();
private:
    QString companyName;
    Address address;
    Interest interest;
    int value; // if 1 "key", if 0 "nice to have"
};

#endif // CUSTOMER_H
