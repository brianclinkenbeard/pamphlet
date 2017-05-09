#ifndef PRODUCT_H
#define PRODUCT_H
#include<QString>


class Product
{
public:
    Product();
    Product(QString, int, double);
    void setName(QString);
    void setPrice(double);
    void setQuantity(int);
    QString getName();
    double getPrice();
    int getQuantity();
private:
    QString name;
    int quantity;
    double price;
};

#endif // PRODUCT_H
