#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include "../SNMP/Scanner.h"
#include <string>
#include "../Utility/IPRangeCalculator.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete s;
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
    if (!ui->checkBox_scan_network_range->isChecked()){
        ui->lineEdit_subnet_input->clear();
    }
}

void MainWindow::on_buttonBox_oid_input_accepted()
{
    if(ui->lineEdit_oid_input->text()!=""){
        ui->listWidget_oids->addItem(ui->lineEdit_oid_input->text());
        ui->lineEdit_oid_input->clear();
    }
}

void MainWindow::on_buttonBox_oid_input_rejected()
{
    ui->lineEdit_oid_input->clear();
}

void MainWindow::on_pushButton_remove_oid_clicked()
{
    qDeleteAll(ui->listWidget_oids->selectedItems());
}

void MainWindow::on_lineEdit_oid_input_returnPressed()
{
    if(ui->lineEdit_oid_input->text()!=""){
        ui->listWidget_oids->addItem(ui->lineEdit_oid_input->text());
        ui->lineEdit_oid_input->clear();
    }

}

void MainWindow::on_pushButton_scan_clicked()
{
    ui->listWidget_results->clear();
    if(ui->checkBox_scan_network_range->isChecked()){
        s->setHosts(IPRangeCalculator::calculate_ips(ui->lineEdit_ip_1->text().toInt(), ui->lineEdit_ip_2->text().toInt(), ui->lineEdit_ip_3->text().toInt(), ui->lineEdit_ip_4->text().toInt(), ui->lineEdit_subnet_input->text().toInt()));
        s->removeFirstLastHost();
    }else{
        s->setHosts(IPRangeCalculator::calculate_ips(ui->lineEdit_ip_1->text().toInt(), ui->lineEdit_ip_2->text().toInt(), ui->lineEdit_ip_3->text().toInt(), ui->lineEdit_ip_4->text().toInt(), 32));
    }
    for (int row = 0; row < ui->listWidget_oids->count(); ++row)
    {
        oids.emplace_back(strdup(ui->listWidget_oids->item(row)->text().toStdString().c_str()));
    }
    s->setOids(oids);
    for(auto item : oids){
        delete item;
    }
    oids.clear();
    if(ui->checkBox_community->isChecked() && ui->lineEdit_community->text()!= ""){
        community = (u_char *)ui->lineEdit_community->text().toStdString().c_str();
    }else{
        community = (u_char *)"public";
    }
    s->scan(ui->listWidget_results, community);
}

void MainWindow::on_checkBox_community_clicked()
{
    ui->lineEdit_community->setEnabled(ui->checkBox_community->isChecked());
    if(!ui->checkBox_community->isChecked()){
        ui->lineEdit_community->clear();
    }
}
