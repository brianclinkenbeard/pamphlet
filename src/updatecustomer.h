#ifndef UPDATECUSTOMER_H
#define UPDATECUSTOMER_H

#include <QDialog>
#include "adminwindow.h"

namespace Ui {
class UpdateCustomer;
}

class UpdateCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCustomer(QWidget *parent = 0);
    explicit UpdateCustomer(int, AdminWindow*);
    ~UpdateCustomer();

private slots:
    void on_update_button_clicked();

private:
    /* helper function */
    void fillEdits(int);
    AdminWindow *parentWindow;
    QString name;
    Ui::UpdateCustomer *ui;
};

#endif // UPDATECUSTOMER_H
