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
    void on_displayInfoButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
