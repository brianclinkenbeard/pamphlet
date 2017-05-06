#include "addcustomer.h"
#include "ui_addcustomer.h"
#include"dbmanager.h"
#include"customer.h"
#include<algorithm>
AddCustomer::AddCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
}

AddCustomer::AddCustomer(AdminWindow *initParentWindow) :
    ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
    parentWindow = initParentWindow;
}

AddCustomer::~AddCustomer()
{
    delete ui;
}

void AddCustomer::on_pushButton_clicked()
{
    /*getCustomer returns cstomer vector by reference so that the changes are applied to the original vector
     * if getCustomer return vector by value, then it returns a copy. if new customer is pushed back to this copy,
     * the changed are not applied to original customer vector,
     *  so it is unchanged when: DbManager::getInstance()->getCustomers()
     */
    //DBCustomers variable should be reference since getCustomer returns by reference
    std::vector<Customer>& DBCustomers = DbManager::getInstance()->getCustomers();
   if(ui->lineEdit_key->text()!="0" && ui->lineEdit_key->text()!="1"){
        ui->label_message->setText("Not a valid value for key, please enter 0, or 1");
        return;
    }
   if(ui->lineEdit_Interest->text()!="0" && ui->lineEdit_Interest->text()!="1"&& ui->lineEdit_Interest->text()!="2" && ui->lineEdit_Interest->text()!=""){
        ui->label_message->setText("Not a valid value for Interest, please enter 0: not interested,  1: somewhat interested, 2: very interested");
        return;
    }
    Customer customer;
    customer.setName( ui->lineEdit_companyName->text());
    customer.setCustomerAddress(ui->lineEdit_streetAddress->text(),ui->lineEdit_city->text(), ui->lineEdit_state->text(),ui->lineEdit_zip->text());
    customer.setValue(ui->lineEdit_key->text().toInt());//add: check if not 0 or 1 ...
    customer.setInterest((Interest)ui->lineEdit_Interest->text().toInt());
    for(unsigned int i = 0; i<DBCustomers.size();i++)
    {
        if(DBCustomers[i].getName().toLower()==customer.getName().toLower()){
            ui->label_message->setText("Not able to add the customer: repeated customer");
            return;
        }
    }
    if(customer.getName()=="" ||ui->lineEdit_streetAddress->text()==""||ui->lineEdit_city->text()==""||ui->lineEdit_state->text()==""||ui->lineEdit_zip->text()==""||ui->lineEdit_key->text()=="" ){
        ui->label_message->setText("Not able to add the customer: required field(s) is empty");
        return;
    }
    DBCustomers.push_back(customer);

    ui->lineEdit_companyName->clear();
    ui->lineEdit_streetAddress->clear();
    ui->lineEdit_city->clear();
    ui->lineEdit_state->clear();
    ui->lineEdit_zip->clear();
    ui->lineEdit_Interest->clear();
    ui->lineEdit_key->clear();
    ui->label_message->setText("Customer Added Successfully");

    parentWindow->showCustomers((bool)parentWindow->sortBoxIndex());
}
