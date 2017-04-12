#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_pushButton_viewMore_clicked()
{
    showTestimonials = new Testimonials;
    showTestimonials->show();
}
