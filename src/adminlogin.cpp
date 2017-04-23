#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "mainwindow.h"
#include "adminwindow.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_password_edit_returnPressed()
{
   const QString ADMIN_USERNAME = "A";
   const QString ADMIN_PASSWORD = "A";

   if (ui->username_edit->text() == ADMIN_USERNAME && ui->password_edit->text() == ADMIN_PASSWORD) {
       AdminWindow *adminWindow = new AdminWindow;
       adminWindow->show();
       this->close();
   } else {
       ui->error_label->setText("Incorrect Login");
   }
}

void AdminLogin::on_username_edit_returnPressed()
{
    on_password_edit_returnPressed();
}

void AdminLogin::on_backButton_clicked()
{
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
    this->close();
}
