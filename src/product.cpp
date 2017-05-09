#include "product.h"

Product::Product():name(""), quantity(0), price(0.0)
{}

Product::Product(QString Name, int Quantity, double Price)
{
    name = Name;
    quantity = Quantity;
    price = Price;
}

void Product::setName(QString Name)
{
    name = Name;
}

void Product::setPrice(double Price)
{
    price = Price;
}

void Product::setQuantity(int Quantity)
{
    quantity = Quantity;
}

QString Product::getName()
{
    return name;
}

double Product::getPrice()
{
    return price;
}

int Product::getQuantity()
{
    return quantity;
}
