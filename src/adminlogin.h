#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QWidget>

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = 0);
    ~AdminLogin();

private slots:
    void on_password_edit_returnPressed();

    void on_backButton_clicked();

    void on_username_edit_returnPressed();

private:
    Ui::AdminLogin *ui;
};

#endif // ADMINLOGIN_H
