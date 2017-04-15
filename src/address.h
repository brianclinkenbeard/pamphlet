#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>

class Address
{
public:
    Address();
    Address(QString, QString, QString, QString);
    void setAddress(QString, QString, QString, QString);
    void setStreet(QString);
    void setCity(QString);
    void setState(QString);
    void setZip(QString);
    QString getStreet();
    QString getCity();
    QString getState();
    QString getZip();
    ~Address();
private:
    QString street; // (e.g., 2000 Street Name)
    QString city;
    QString state;
    QString zipcode;
};

#endif // ADDRESS_H
