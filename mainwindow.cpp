#include <QScrollBar>
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
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddAlert_clicked()
{
    int pos = ui->tableView->verticalScrollBar()->value();
    alert_model.add_alert();
    if (pos > 0)
    {
        ui->tableView->verticalScrollBar()->setValue(pos + 1);
    }
}

void MainWindow::on_btnClearAll_clicked()
{
    alert_model.clear_all();
}
