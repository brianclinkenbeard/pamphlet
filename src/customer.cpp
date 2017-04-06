#include "customer.h"

Customer::Customer()
{
    address = new Address();
    Interest = HIGH;
    value = false;
}

Customer::Customer(QString initStreet, QString initCity, QString initState, QString initZip) :
    Address(initStreet, initCity, initState, initZip)
{
    Customer.address.street = initStreet;
    Customer.address.city = initCity;
    Customer.address.state = initState;
    Customer.address.zipcode = initZip;
}

Customer::Customer(QString name, Interest initInterest, bool initValue) :
    companyName(name),
    interest(initInterest),
    value(initValue) {}

void Customer::setName(QString name)
{
    companyName = name;
}

void Customer::setAddress(QString initStreet, QString initCity, QString initState, QString initZip)
{
    Customer.address.street = initStreet;
    Customer.address.city = initCity;
    Customer.address.state = initState;
    Customer.address.zipcode = initZip;
}

void Customer::setInterest(Interest initInterest)
{
    interest = initInterest;
}

void Customer::setValue(bool initValue)
{
    value = initValue;
}

Customer::~Customer()
{
    delete address;
}






