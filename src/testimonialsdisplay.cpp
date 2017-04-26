#include "testimonialsdisplay.h"
#include "ui_testimonialsdisplay.h"

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
