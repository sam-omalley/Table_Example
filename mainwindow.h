#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alert_model.h"

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
    void on_btnAddAlert_clicked();

    void on_btnClearAll_clicked();

private:
    Ui::MainWindow *ui;
    Alert_Model alert_model;
};

#endif // MAINWINDOW_H
