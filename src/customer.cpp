#include "customer.h"

Customer::Customer()
{

}

Customer::Customer(QString initStreet, QString initCity, QString initState, QString initZip)
{

}

Customer::Customer(QString name, Interest initInterest, bool initValue) :
    companyName(name),
    interest(initInterest),
    value(initValue) {}

void Customer::setName(QString name)
{
    companyName = name;
}

void Customer::setAddress(Address initAddress)
{

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

}






