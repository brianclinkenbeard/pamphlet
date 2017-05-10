#include "customer.h"

Customer::Customer():products()
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
    address(initStreet, initCity, initState, initZip), products()
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
QString Customer::getName() const
{
    return companyName;
}

Address Customer::getCustomerAddress() const
{
    return address;
}

Interest Customer::getInterest() const
{
    return interest;
}

int Customer::getValue() const
{
    return value;
}

/* compare strings for std::sort */
bool Customer::operator <(const Customer& compareCustomer) const
{
    return (getName() < compareCustomer.getName());
}

bool Customer::operator >(const Customer& compareCustomer) const
{
    return (getName() > compareCustomer.getName());
}

void Customer::addProduct(Product item)
{
    bool found = false;
    /*if the item is repeated*/
    for(unsigned int i=0; i<products.size();i++){
        if (products.at(i).getName()==item.getName()){
            products.at(i).setQuantity(item.getQuantity()+products.at(i).getQuantity());
            found = true;
            break;
        }
    }
    /*if the item is not repeated*/
    if(!found)
        products.push_back(item);

}

std::vector<Product>& Customer::getProducts()
{
    return products;
}

int Customer::getQuantityOf(QString productName)
{
    unsigned int i;
    for( i=0; i<products.size();i++)
    {
        if(products.at(i).getName() == productName)
            break;
    }
    return products.at(i).getQuantity();
}

Customer::~Customer()
{

}








