#include "customer.h"

Customer::Customer()
{

}

Customer::Customer(QString name, Interest initInterest, bool initValue, QString initStreet, QString initCity, QString initState, QString initZip) :
    address(initStreet, initCity, initState, initZip)
{
    companyName = name;
    interest = initInterest;
    value = initValue;
}

void Customer::setName(QString name)
{
    companyName = name;
}

void Customer::setCustomerAddress(QString initStreet, QString initCity, QString initState, QString initZip)
{
    address.setAddress(initStreet, initCity, initState, initZip);
}

void Customer::setInterest(Interest initInterest)
{
    interest = initInterest;
}

void Customer::setValue(bool initValue)
{
    value = initValue;
}
QString Customer::getName()
{
    return companyName;
}

Address Customer::getCustomerAddress()
{
    return address;
}

Interest Customer::getInterest()
{
    return interest;
}

bool Customer::getValue()
{
    return value;
}

Customer::~Customer()
{

}






