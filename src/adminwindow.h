#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>
#include "dbmanager.h"
#include"displaytransaction.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();
    void showCustomers(bool);
    int sortBoxIndex();

private slots:
    void on_logoutButton_clicked();

    void on_sortBox_currentIndexChanged(int index);

    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_transactionsButton_clicked();

private:

    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
