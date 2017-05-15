#ifndef UPDATECUSTOMER_H
#define UPDATECUSTOMER_H

#include <QDialog>

namespace Ui {
class UpdateCustomer;
}

class UpdateCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCustomer(QWidget *parent = 0);
    ~UpdateCustomer();

private slots:
    void on_pushButton_Select_clicked();

private:
    Ui::UpdateCustomer *ui;
};

#endif // UPDATECUSTOMER_H
