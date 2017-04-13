#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    ui->textBrowser->setText("Please select an option in the context menu to view help.");
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::on_comboBox_currentIndexChanged(int index)
{
    QString helpInfo;
    /* TODO: add help information */
    switch (index) {
    case 0:
        helpInfo = "Please select an option in the context menu to view help.";
        break;
    case 1:
        helpInfo = "[Service Options Help]";
        break;
    case 2:
        helpInfo = "[Maintenance and Pricing Help]";
        break;
    }
    ui->textBrowser->setText(helpInfo);
}
