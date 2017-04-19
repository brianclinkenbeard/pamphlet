#include "customer.h"

Customer::Customer()
{
    interest = LOW;
}
Customer::Customer(const Customer & otherCustomer)
{
    companyName = otherCustomer.companyName;
    interest = otherCustomer.interest;
    value = otherCustomer.value;
    address = otherCustomer.address;
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

void Customer::setInterest(QString initInterest)
{
    if(initInterest == "very interested"){
        interest = HIGH;
    }
    else if("somewhat interested" == initInterest){
        interest = MEDIUM;
    }
    else if(initInterest == "not interested"){
        interest = LOW;
    }
}

void Customer::setValue(int initValue)
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

int Customer::getValue()
{
    return value;
}

Customer::~Customer()
{

}






