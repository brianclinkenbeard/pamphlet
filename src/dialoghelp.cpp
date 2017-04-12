#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "Service Options"){
        ui->textBrowser->setText("About Service Options");
    }else if(arg1 == "Maitenance with pricing"){
        ui->textBrowser->setText("About Maitenance and pricing");
    }
}
