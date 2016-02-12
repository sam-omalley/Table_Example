#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&alert_model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                0, QHeaderView::Fixed);
    ui->tableView->setColumnWidth(0, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddAlert_clicked()
{
    alert_model.add_alert();
}

void MainWindow::on_btnClearAll_clicked()
{
    alert_model.clear_all();
}
