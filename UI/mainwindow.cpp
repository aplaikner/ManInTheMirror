#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_checkBox_darkmode_clicked()
{
    this->setStyleSheet("background-color: #0e0d0f; color: white");
    ui->checkBox_rebeccapurple->setChecked(false);
    ui->checkBox_whitemode->setChecked(false);
}

void MainWindow::on_checkBox_rebeccapurple_clicked()
{
    this->setStyleSheet("background-color: #663399; color: black");
    ui->checkBox_darkmode->setChecked(false);
    ui->checkBox_whitemode->setChecked(false);
}

void MainWindow::on_checkBox_whitemode_clicked()
{
    this->setStyleSheet("background-color: white; color: black");
    ui->checkBox_darkmode->setChecked(false);
    ui->checkBox_rebeccapurple->setChecked(false);
}
