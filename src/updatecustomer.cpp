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
}

UpdateCustomer::~UpdateCustomer()
{
    delete ui;
}

void UpdateCustomer::on_pushButton_Select_clicked()
{
    QString customer_selection;
    customer_selection = ui->lineEdit_customerName->text();

//    std::vector<Customer>& DBCustomers = DbManager::getInstance()->getCustomers();
//    Customer customer;
//    /*check if customer is not repeated*/
//    bool found = false;
//    for(unsigned int i = 0; i<DBCustomers.size();i++)
//    {
//        if(DBCustomers[i].getName().toLower() == ui->lineEdit_customerName->text().toLower())
//        {
//            found = true;
//            if (!(ui->lineEdit_StreetAddress == ""))
//            {
//                DBCustomers[i].setCustomerAddress(ui->lineEdit_StreetAddress->text())
//            }
//        }
//        if (!found)
//        {
//            ui->label_message->setText("Customer not found");
//        }
//    }

}
