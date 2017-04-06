#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

struct Address
{
    QString street; // (e.g., 2000 Street Name)
    QString city;
    QString state;
    QString zipcode;
};

enum Interest {HIGH, MEDIUM, LOW};  // Customer's level of interest in our product

class Customer
{
public:
    Customer();
    Customer(QString, Address, Interest, bool);
    Customer(const Customer&);
    void setName(QString);
    void setAddress(Address);
    void setInterest(Interest);
    void setValue(bool);
private:
    QString companyName;
    Address address;
    Interest interest;
    bool value; // if true "key", if false "nice to have"
};

#endif // CUSTOMER_H
