#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    dialogHelp = new DialogHelp;
    dialogHelp->show();
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
