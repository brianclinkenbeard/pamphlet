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
    showCustomers(false);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_logoutButton_clicked()
{
   MainWindow *main = new MainWindow;
   main->show();
   this->close();
}

void AdminWindow::on_sortBox_currentIndexChanged(int index)
{
    bool key;
    index == 0 ? key = false : key = true;
    showCustomers(key);
}

void AdminWindow::showCustomers(bool keyOnly)
{
    std::vector<Customer> DBCustomers = DbManager::getInstance()->getCustomers();
    std::vector<Customer> customers;
    QString keyCustomer;

    /* clear table */
    ui->tableWidget_CustomerInfo->setRowCount(0);

    for (unsigned int i = 0; i < DBCustomers.size(); ++i) {
        /* only add key customers if onlyKey is true */
        if (!keyOnly || (keyOnly && DBCustomers.at(i).getValue() == 1)) {
                customers.push_back(DBCustomers.at(i));
        }
    }

    /* sort customers by name */
    std::sort (customers.begin(), customers.end());

    for (unsigned int i = 0; i < customers.size(); ++i) {
        /* readable key customer value */
        customers.at(i).getValue() == 1 ? keyCustomer = "Key" : keyCustomer = "Not Key";

        /* new row at the index of the total row count */
        ui->tableWidget_CustomerInfo->insertRow(i);

        /* fill info */
        ui->tableWidget_CustomerInfo->setItem(i, 0, new QTableWidgetItem(customers.at(i).getName()));
        ui->tableWidget_CustomerInfo->setItem(i, 1, new QTableWidgetItem(customers.at(i).getCustomerAddress().getStreet()));
        ui->tableWidget_CustomerInfo->setItem(i, 2, new QTableWidgetItem(customers.at(i).getCustomerAddress().getCity()));
        ui->tableWidget_CustomerInfo->setItem(i, 3, new QTableWidgetItem(customers.at(i).getCustomerAddress().getState()));
        ui->tableWidget_CustomerInfo->setItem(i, 4, new QTableWidgetItem(customers.at(i).getCustomerAddress().getZip()));
        ui->tableWidget_CustomerInfo->setItem(i, 5, new QTableWidgetItem(keyCustomer));
        ui->tableWidget_CustomerInfo->setItem(i, 6, new QTableWidgetItem(QString::number(customers.at(i).getInterest())));
    }
}
