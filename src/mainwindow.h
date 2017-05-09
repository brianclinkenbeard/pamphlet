#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionHelp_triggered();

    void on_comboBox_currentIndexChanged(int index);

    void on_loginButton_clicked();

    void on_pushButton_viewMore_clicked();

    void on_Purchase_clicked();

    void on_DisplayPurchases_clicked();

private:
    int userIndex;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
