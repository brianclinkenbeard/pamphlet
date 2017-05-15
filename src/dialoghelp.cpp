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

/**
 * @brief DialogHelp::on_comboBox_currentIndexChanged
 * Selects help option
 * @param index
 */
void DialogHelp::on_comboBox_currentIndexChanged(int index)
{
    QString helpInfo;
    /* TODO: add help information */
    switch (index) {
    case 0:
        helpInfo = "Please select an option in the context menu to view help.";
        break;
    case 1:
        /* Order a Product */
        helpInfo = "To order a product, enter company information and select a product. If you are not already one of our "
                   "potential customers, please first request a pamphlet. Press the order button to place your order.";
        break;
    case 2:
        /* Request a Pamphlet */
        helpInfo = "To request a pamphlet, simply enter valid information and press the request a pamphlet button.";
        break;
    case 3:
        /* List of Environments */
        helpInfo = "To our service options for an environment, simply select an environment from the drop down menu.";
        break;
     case 4:
        /* Testimonials */
        helpInfo = "To add a testimonial, simply enter a company name and a testimonial and press submit.";
    }
    ui->textBrowser->setText(helpInfo);
}
