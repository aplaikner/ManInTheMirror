#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_radioButton_whitemode_clicked()
{
    this->setStyleSheet("background-color: white; ");
}

void MainWindow::on_radioButton_darkmode_clicked()
{
    this->setStyleSheet("background-color: #97949a; color: white");
}


void MainWindow::on_radioButton_rebeccapurple_clicked()
{
    this->setStyleSheet("background-color: #663399; color: white");
}

void MainWindow::on_checkBox_scan_network_range_clicked()
{
    ui->label_subnet_slash->setEnabled(ui->checkBox_scan_network_range->isChecked());
    ui->lineEdit_subnet_input->setEnabled(ui->checkBox_scan_network_range->isChecked());
}
