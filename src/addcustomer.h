#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>
#include "adminwindow.h"


namespace Ui {
class AddCustomer;
}

class AddCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomer(QWidget *parent = 0);
    AddCustomer(AdminWindow *initParentWindow);
    ~AddCustomer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddCustomer *ui;
    AdminWindow *parentWindow;
};

#endif // ADDCUSTOMER_H
