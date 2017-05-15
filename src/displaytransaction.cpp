#include "displaytransaction.h"
#include "ui_displaytransaction.h"

DisplayTransaction::DisplayTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayTransaction)
{
    ui->setupUi(this);
    userIndex = -1;
}

/**
 * @brief displaytransaction::DisplayTransaction
 * creates display using customer vector to view a customer's transactions of our products in a table
 * @param UserIndex
 */
DisplayTransaction::DisplayTransaction(int UserIndex):
    ui(new Ui::DisplayTransaction)
{
    ui->setupUi(this);

    /* set header labels */
    ui->TransactionTable->setColumnCount(4);
    ui->TransactionTable->setHorizontalHeaderLabels(QString("Product;Price;Quantity;Total Spent").split(";"));
    ui->TransactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    userIndex = UserIndex;
    std::vector<Customer>& customers = DbManager::getInstance()->getCustomers();

    /* set customer label to the customer name */
    ui->customer_label->setText(customers.at(userIndex).getName());

    QSqlQuery qry;
    std::vector<Product> products = DbManager::getInstance()->getInventory();

    if(userIndex != -1){
        ui->TransactionTable->setRowCount(products.size());
        for(unsigned int i = 0; i < products.size(); i++){
            ui->TransactionTable->setItem(i, 0, new QTableWidgetItem(products.at(i).getName()));
            ui->TransactionTable->setItem(i, 1, new QTableWidgetItem("$"+QString::number(products.at(i).getPrice())));
            qry.prepare("SELECT "+products.at(i).getName()+" FROM Transactions WHERE Company = '"+customers.at(userIndex).getName()+"'");
            if(!qry.exec())
                qDebug()<<"not able to read from Transactions for display Transactions";
            qry.next();
            ui->TransactionTable->setItem(i, 2, new QTableWidgetItem(qry.value(0).toString()));
            ui->TransactionTable->setItem(i, 3, new QTableWidgetItem("$"+QString::number((products.at(i).getPrice())*(qry.value(0).toInt()))));
        }

    }
}

DisplayTransaction::~DisplayTransaction()
{
    delete ui;
}
