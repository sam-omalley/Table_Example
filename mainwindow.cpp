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

    connect(
        &alert_model,
        SIGNAL(
            rowsInserted(const QModelIndex &, int, int)),
        this,
        SLOT(
            model_row_inserted(const QModelIndex &, int, int)));
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

void MainWindow::model_row_inserted(
        const QModelIndex parent, int start, int end)
{
    int pos = ui->tableView->verticalScrollBar()->value();
    if (pos > 0)
    {
        ui->tableView->verticalScrollBar()->setValue(pos + (end - start) + 1);
    }
}
