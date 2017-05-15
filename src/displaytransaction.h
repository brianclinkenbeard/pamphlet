#ifndef DISPLAYTRANSACTION_H
#define DISPLAYTRANSACTION_H

#include <QDialog>
#include"customer.h"
#include"dbmanager.h"

namespace Ui {
class DisplayTransaction;
}

class DisplayTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayTransaction(QWidget *parent = 0);
    /** non-default constructor */
    explicit DisplayTransaction(int serIndex); /**< index of customer */
    ~DisplayTransaction();

private:
    Ui::DisplayTransaction *ui;
    int userIndex;
};

#endif // DISPLAYTRANSACTION_H
