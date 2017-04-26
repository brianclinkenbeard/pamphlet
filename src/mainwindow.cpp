#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoghelp.h"
#include "adminlogin.h"
#include "testimonialsdisplay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* mailto for email label */
    ui->email_label->setOpenExternalLinks(true);
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
        osInfo = "[Windows Opportunities]";
        break;
    case 2:
        osInfo = "[macOS Opportunities]";
        break;
    case 3:
        osInfo = "[GNU/Linux Opportunities]";
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
