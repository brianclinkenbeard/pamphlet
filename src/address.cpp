#include "address.h"

Address::Address()
{

}

Address::Address(QString initStreet, QString initCity, QString initState, QString initZip) :
    street(initStreet),
    city(initCity),
    state(initState),
    zipcode(initZip) {}

void Address::setAddress(QString initStreet, QString initCity, QString initState, QString initZip)
{
    street = initStreet;
    city = initCity;
    state = initState;
    zipcode = initZip;
}

void Address::setStreet(QString initStreet)
{
    street = initStreet;
}

void Address::setCity(QString initCity)
{
    city = initCity;
}

void Address::setState(QString initState)
{
    state = initState;
}

void Address::setZip(QString initZip)
{
    zipcode = initZip;
}

Address::~Address()
{

}
