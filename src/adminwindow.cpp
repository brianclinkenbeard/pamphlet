#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    /* headers */
    QStringList headerTitles;
    headerTitles<<"Company"<<"Street Address"<<"City"<<"State"<<"Zip Code"<<"Key Customer"<<"Customer Rate";
    ui->tableWidget_CustomerInfo->setColumnCount(headerTitles.size());
    ui->tableWidget_CustomerInfo->setHorizontalHeaderLabels(headerTitles);

    /* make columns fit window */
    ui->tableWidget_CustomerInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* generate list */
    on_displayInfoButton_clicked();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_displayInfoButton_clicked()
{
    std::vector<Customer> customers = DbManager::getInstance()->getCustomers();
    QString keyCustomer;

    int rows = customers.size();
    ui->tableWidget_CustomerInfo->setRowCount(rows);


    for (unsigned int i = 0; i < customers.size(); ++i) {
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

void AdminWindow::on_logoutButton_clicked()
{
   MainWindow *main = new MainWindow;
   main->show();
   this->close();
}
