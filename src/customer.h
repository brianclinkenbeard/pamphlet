#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"product.h"
#include "address.h"
#include<vector>

enum Interest {LOW=0, MEDIUM, HIGH};  // Customer's level of interest in our product

/**
 * @brief Customer data class
 * Contains customer name, address, and interest information.
 */
class Customer
{
public:
    /** Default constructor */
    Customer();
    /** non-default constructor */
    Customer(QString name, /**< customer name */
             Interest initInterest, /**< Interest in products */
             bool key, /**< Key customer boolean */
             QString,
             QString,
             QString,
             QString);
    /** copy constructor */
    Customer(const Customer&);
    void setName(QString);
    void setCustomerAddress(QString, QString, QString, QString);
    void setInterest(Interest);
    void setInterest(QString);
    void setValue(int);
    QString getName() const;
    Address getCustomerAddress() const;
    Interest getInterest() const;
    int getValue() const;
    /** compares QStrings for sorting */
    bool operator <(const Customer&) const;
    bool operator >(const Customer&) const;
    void addProduct(Product item);
    int getQuantityOf(QString productName);
    std::vector<Product>& getProducts();
    virtual void print() {};
    ~Customer();
private:
    QString companyName;
    Address address;
    Interest interest;
    int value; // if 1 "key", if 0 "nice to have"
    std::vector<Product> products;
};

#endif // CUSTOMER_H
