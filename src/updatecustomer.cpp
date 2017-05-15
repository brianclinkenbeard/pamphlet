#include "updatecustomer.h"
#include "ui_updatecustomer.h"
#include"dbmanager.h"
#include"customer.h"
#include <algorithm>
#include <QMessageBox>
UpdateCustomer::UpdateCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateCustomer)
{
    ui->setupUi(this);
    parentWindow = NULL;
    fillEdits(0);
}

UpdateCustomer::UpdateCustomer(int index, AdminWindow *parent) :
    parentWindow(parent),
    ui(new Ui::UpdateCustomer)
{
    ui->setupUi(this);

    try {
        if (index < 0) {
            throw index;
        } else {
            qDebug() << "Update customer index is " << index;
            fillEdits(index);
        }
    } catch (int e) {
        qDebug() << "Selected customer index is " << e << ". Value must be greater than 0. Setting the selected index to 0...";
        fillEdits(0);
    }
}

/**
 * @brief UpdateCustomer::fillEdits
 * fill lineedits for easy editing
 * @param cIndex
 */
void UpdateCustomer::fillEdits(int cIndex)
{
    /* validate price */
    ui->lineEdit_keyCust->setValidator(new QIntValidator(0, 1, this));
    ui->lineEdit_Interest->setValidator(new QIntValidator(0, 2, this));

    std::vector<Customer> customers = DbManager::getInstance()->getCustomers();
    std::sort(customers.begin(), customers.end());

    /* save name for deleting later */
    name = customers.at(cIndex).getName();

    /** fill in lineedits from vector */
    ui->lineEdit_customerName->setText(name);
    ui->lineEdit_Interest->setText(QString::number(static_cast<int>(customers.at(cIndex).getInterest())));
    ui->lineEdit_keyCust->setText(QString::number(customers.at(cIndex).getValue()));
    Address cAddress = customers.at(cIndex).getCustomerAddress();
    ui->lineEdit_City->setText(cAddress.getCity());
    ui->lineEdit_StreetAddress->setText(cAddress.getStreet());
    ui->lineEdit_State->setText(cAddress.getState());
    ui->lineEdit_zipCode->setText(cAddress.getZip());
}

UpdateCustomer::~UpdateCustomer()
{
    delete ui;
}

/**
 * @brief UpdateCustomer::on_update_button_clicked()
 * old values from customer are deleted and replaced with updated values
 * @param name
 */
void UpdateCustomer::on_update_button_clicked()
{
    DbManager::getInstance()->DeleteFromDb(name);

    /* DBCustomers variable should be reference since getCustomer returns by reference */
    std::vector<Customer>& DBCustomers = DbManager::getInstance()->getCustomers();
    Customer customer;

    /* check if company name is empty before checking for repetition */
    if (ui->lineEdit_customerName->text().isEmpty()) {
        ui->label_message->setText("One or more required field is empty");
        return;
    } else {
        customer.setName(ui->lineEdit_customerName->text());
    }

    /* delete old customer */
    for(unsigned int i = 0; i<DBCustomers.size();i++)
    {
        if (DBCustomers[i].getName().toLower()== name.toLower()) {
            DBCustomers.erase(DBCustomers.begin() + i);
        }
    }

    /* check if required field is empty */
    if (customer.getName().isEmpty() || ui->lineEdit_StreetAddress->text().isEmpty() || ui->lineEdit_City->text().isEmpty() || ui->lineEdit_State->text().isEmpty() || ui->lineEdit_zipCode->text().isEmpty()) {
        ui->label_message->setText("One or more required field is empty");
        return;
    } else {
        customer.setCustomerAddress(ui->lineEdit_StreetAddress->text(), ui->lineEdit_City->text(), ui->lineEdit_State->text(), ui->lineEdit_zipCode->text());
    }

    /* not key and medium interest by default */
    customer.setValue(ui->lineEdit_keyCust->text().toInt());
    customer.setInterest(static_cast<Interest>(ui->lineEdit_keyCust->text().toInt()));

    DBCustomers.push_back(customer);

    ui->lineEdit_customerName->clear();
    ui->lineEdit_StreetAddress->clear();
    ui->lineEdit_City->clear();
    ui->lineEdit_State->clear();
    ui->lineEdit_zipCode->clear();
    ui->lineEdit_keyCust->clear();
    ui->lineEdit_Interest->clear();
    parentWindow->showCustomers(parentWindow->sortBoxIndex());
    ui->label_message->setText("Success");
}
