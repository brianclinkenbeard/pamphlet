#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include "dbmanager.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void on_logoutButton_clicked();

    void on_sortBox_currentIndexChanged(int index);

private:
    /* helper function */
    void showCustomers(bool);
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
