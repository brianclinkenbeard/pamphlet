#include "displaytransaction.h"
#include "ui_displaytransaction.h"

DisplayTransaction::DisplayTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayTransaction)
{
    ui->setupUi(this);
    userIndex = -1;
}
DisplayTransaction::DisplayTransaction(int UserIndex):
    ui(new Ui::DisplayTransaction)
{
    ui->setupUi(this);
    userIndex = UserIndex;
    QSqlQuery qry;
    std::vector<Customer>& customers = DbManager::getInstance()->getCustomers();
    std::vector<Product> products = DbManager::getInstance()->getInventory();
    if(userIndex != -1){
        ui->TransactionTable->setRowCount(products.size());
        ui->TransactionTable->setColumnCount(4);
        ui->TransactionTable->setHorizontalHeaderLabels(QString("Product;Price;Quantity;Total Spent").split(";"));
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
