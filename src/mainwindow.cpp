#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoghelp.h"
#include "adminlogin.h"
#include "testimonialsdisplay.h"
#include"displaytransaction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap image(":/res/pic1.jpg");
    ui->label_image->setPixmap(image);
    QPixmap image2(":/res/pic2.jpg");
    ui->label_backGround->setPixmap(image2);
    QPixmap image3(":/res/pic3.jpg");
    ui->label_logo->setPixmap(image3);

    /* mailto for email label */
    ui->email_label->setOpenExternalLinks(true);
    userIndex = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHelp_triggered()
{
    DialogHelp *helpWindow = new DialogHelp;
    helpWindow->show();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString osInfo;
    switch (index) {
    case 0:
        osInfo = "Select an operating system to explore security opportunities we offer.";
        break;
    case 1:
        osInfo = "Top level protection of all your data against hackers, viruses, and many other types of malware for Windows Software.";
        break;
    case 2:
        osInfo = "Top level protection of all your data against hackers and everything else that tries interfering with your data for Mac Software.";
        break;
    case 3:
        osInfo = "Top level protection of all your data against hackers and malicious malware for Linux Software.";
        break;
    }
    ui->osinfo_browser->setText(osInfo);
}

void MainWindow::on_loginButton_clicked()
{
    AdminLogin *loginWindow = new AdminLogin;
    loginWindow->show();
    this->close();
}

void MainWindow::on_pushButton_viewMore_clicked()
{
    TestimonialsDisplay *testDis = new TestimonialsDisplay;
    testDis->show();
}

void MainWindow::on_Purchase_clicked()
{
    bool found = false;
    std::vector<Customer>& customers = DbManager::getInstance()->getCustomers();
    unsigned int i;
    for (i =0; i<customers.size(); i++)
    {
        if(customers.at(i).getName() == ui->lineEdit_customerName->text())
        {
            found = true;
            userIndex = i;
            break;
        }
    }
    if(found){
        if(ui->lineEdit_quantity->text().toInt()<=5 && ui->lineEdit_quantity->text().toInt()>0)
        {
            Product product = DbManager::getInstance()->searchInInventory(ui->listOfProducts->currentText());
            product.setQuantity(ui->lineEdit_quantity->text().toInt());
            customers.at(i).addProduct(product);
            ui->label_errorMessage->setStyleSheet("color:green");
            ui->label_errorMessage->setText("Successful purchase");
            QSqlQuery qry;
            qry.prepare("UPDATE Transactions SET "+ui->listOfProducts->currentText()+" = "+QString::number(customers.at(i).getQuantityOf(ui->listOfProducts->currentText()))+" WHERE Company = '"+customers.at(i).getName()+"'");
            if(!qry.exec())
                qDebug()<<"unable to exec";
        }else{
            ui->label_errorMessage->setStyleSheet("color:red");

            if (ui->lineEdit_quantity->text().toInt() < 1) {
                ui->label_errorMessage->setText("Quantity must be greater than 0.");
            }
            if (ui->lineEdit_quantity->text().toInt() > 5) {
                ui->label_errorMessage->setText("Quantity must be fewer than 5.");
            }
        }
    }else{
        ui->label_errorMessage->setStyleSheet("color:red");
        ui->label_errorMessage->setText("Invalid customer");
    }
    ui->lineEdit_customerName->clear();
    ui->lineEdit_quantity->clear();
}
