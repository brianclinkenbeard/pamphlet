#include "testimonialsdisplay.h"
#include "ui_testimonialsdisplay.h"
#include "dbmanager.h"

TestimonialsDisplay::TestimonialsDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestimonialsDisplay)
{
    ui->setupUi(this);
}

TestimonialsDisplay::~TestimonialsDisplay()
{
    delete ui;
}

void TestimonialsDisplay::on_submit_button_clicked()
{
    if (ui->customer_edit->text().isEmpty() || ui->testimonial_textedit->toPlainText().isEmpty()) {
        ui->submit_label->setText("One or more field is empty.");
        return;
    } else {
        DbManager::getInstance()->addTestimonial(ui->customer_edit->text(), ui->testimonial_textedit->toPlainText());
        ui->submit_label->setText("Success");
    }
}
