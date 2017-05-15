#ifndef PRODUCT_H
#define PRODUCT_H
#include<QString>

/**
 * @brief Product class
 * contains product information and quantity
 */
class Product
{
public:
    /** default constructor */
    Product();
    /** non-default constructor */
    Product(QString initName, /**< product name */
            int initQuantity, /**< quantity of product */
            double initPrice); /**< product price */
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
