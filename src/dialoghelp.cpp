#include "dialoghelp.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_comboBox_activated(const QString &arg1)
{
    qDebug()<<arg1;
    if (arg1 == "Service Options"){
        ui->textBrowser->setText("About Service Option");
    }else if(arg1 == "Maintenance plan with pricing"){
        ui->textBrowser->setText("About Maintenace Plan and Pricing");
    }
}
