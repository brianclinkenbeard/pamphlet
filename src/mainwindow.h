#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
