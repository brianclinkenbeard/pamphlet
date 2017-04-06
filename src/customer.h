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
    Customer(QString, QString, QString, QString);
    Customer(QString, Interest, bool);
    Customer(const Customer&);
    void setName(QString);
    void setAddress(QString, QString, QString, QString);
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
