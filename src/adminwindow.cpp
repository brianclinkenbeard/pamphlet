#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include"addcustomer.h"

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

    /* hide vertical header and select entire rows */
    ui->tableWidget_CustomerInfo->verticalHeader()->hide();
    ui->tableWidget_CustomerInfo->setSelectionBehavior(QAbstractItemView::SelectRows);

    /* nothing selected by default */
    selected = -1;

    /* generate list */
    showCustomers(false);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_logoutButton_clicked()
{
   DbManager::getInstance()->CustomersToDb();//saving changes of vector to database
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
    qDebug()<<DBCustomers.size();
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

void AdminWindow::on_tableWidget_CustomerInfo_itemClicked(QTableWidgetItem *item)
{
    selected = item->row();
    qDebug() <<"item row:"<< selected;
}

void AdminWindow::on_deleteButton_clicked()
{
    /* if nothing is selected, exit */
    if (selected == -1) {
        /* TODO: Dialog box? */
        qDebug() << "Nothing is selected to delete. Please select an element.";
        return;
    }

    /* deleting from database */
    QString name = ui->tableWidget_CustomerInfo->item(selected, 0)->text();
    qDebug()<<"name of item: "<<name;
    DbManager::getInstance()->DeleteFromDb(name);

    /* deleting from vector */
    std::vector<Customer>& customers = DbManager::getInstance()->getCustomers();
    for (unsigned int i =0; i<customers.size(); i++) {
        if (customers.at(i).getName() == name) {
            customers.erase(customers.begin()+i);
            /* clear selection */
            selected = -1;
            /* refresh list */
            showCustomers(ui->sortBox->currentIndex());
        }
    }
}


void AdminWindow::on_addButton_clicked()
{
    AddCustomer* addCustomerWindow = new AddCustomer(this);
    addCustomerWindow->show();
}

int AdminWindow::sortBoxIndex()
{
    return ui->sortBox->currentIndex();
}

void AdminWindow::on_transactionsButton_clicked()
{
    /* if nothing is selected, exit */
    if (selected == -1) {
        /* TODO: Dialog box? */
        qDebug() << "Nothing is selected to delete. Please select an element.";
        return;
    }
    QString name = ui->tableWidget_CustomerInfo->item(selected, 0)->text();
    std::vector<Customer> customers = DbManager::getInstance()->getCustomers();
    for(unsigned int i = 0; i<customers.size();i++)
    {
        if(customers.at(i).getName()==name){
            DisplayTransaction* TransactionWindow = new DisplayTransaction(i);
            TransactionWindow->show();
            break;
        }

    }
}
