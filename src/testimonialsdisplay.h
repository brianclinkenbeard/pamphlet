#ifndef TESTIMONIALSDISPLAY_H
#define TESTIMONIALSDISPLAY_H

#include <QDialog>

namespace Ui {
class TestimonialsDisplay;
}

class TestimonialsDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit TestimonialsDisplay(QWidget *parent = 0);
    ~TestimonialsDisplay();

private slots:
    /**
     * @brief on_submit_button_clicked
     * fill in submission fields for easy customer testimonial interaction
     */
    void on_submit_button_clicked();

private:
    Ui::TestimonialsDisplay *ui;
};

#endif // TESTIMONIALSDISPLAY_H
