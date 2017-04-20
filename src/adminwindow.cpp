#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_4_clicked()
{
    std::vector<Customer> customers = DbManager::getInstance()->getCustomers();
    QString keyCustomer;
    QStringList headerTitles;
    headerTitles<<"Company"<<"Street Address"<<"City"<<"State"<<"Zip Code"<<"Key Customer"<<"Customer Rate";
    int rows = customers.size();
    int columns = 7;
    ui->tableWidget_CustomerInfo->setRowCount(rows);
    ui->tableWidget_CustomerInfo->setColumnCount(columns);
    ui->tableWidget_CustomerInfo->setHorizontalHeaderLabels(headerTitles);
    for(int i =0; i<customers.size();i++)
    {
        keyCustomer = "Not Key";
        ui->tableWidget_CustomerInfo->setItem(i, 0, new QTableWidgetItem(customers[i].getName()));
        ui->tableWidget_CustomerInfo->setItem(i, 1, new QTableWidgetItem(customers[i].getCustomerAddress().getStreet()));
        ui->tableWidget_CustomerInfo->setItem(i, 2, new QTableWidgetItem(customers[i].getCustomerAddress().getCity()));
        ui->tableWidget_CustomerInfo->setItem(i, 3, new QTableWidgetItem(customers[i].getCustomerAddress().getState()));
        ui->tableWidget_CustomerInfo->setItem(i, 4, new QTableWidgetItem(customers[i].getCustomerAddress().getZip()));
       if(customers[i].getValue()==1){
           keyCustomer = "Key";
       }
        ui->tableWidget_CustomerInfo->setItem(i, 5, new QTableWidgetItem(keyCustomer));
        ui->tableWidget_CustomerInfo->setItem(i, 6, new QTableWidgetItem(QString::number(customers[i].getInterest())));
    }
}
