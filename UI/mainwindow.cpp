#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../SNMP/TrapListener.h"
#include <thread>
#include <string>
#include "../Utility/IPRangeCalculator.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    // stets up UI
    ui->setupUi(this);

    // adds initial OIDs to list in UI
    ui->listWidget_oids->addItem("sysDescr");
    ui->listWidget_oids->addItem("hrStorage");
    ui->listWidget_oids->addItem("sysUpTime");
    ui->listWidget_oids->addItem("sysContact");
    ui->listWidget_oids->addItem("sysName");
    ui->listWidget_oids->addItem("sysLocation");

    // creates TrapListener object and passes the list where traps are display in UI
    TrapListener t(ui->listWidget_traps);
    // starts trap listener with new thread and detaches it for asynchronous processing of traps
    std::thread(&TrapListener::listen, t).detach();
}

MainWindow::~MainWindow() {
    // deletes dynamically allocated scanner
    delete s;
    // deletes UI
    delete ui;
}

// sets UI theme to white
void MainWindow::on_radioButton_whitemode_clicked() {
    this->setStyleSheet("background-color: white; ");
}

// sets UI theme to darkmode with darker background and white text
void MainWindow::on_radioButton_darkmode_clicked() {
    this->setStyleSheet("background-color: #97949a; color: white");
}

// sets UI theme to rebeccapurple
void MainWindow::on_radioButton_rebeccapurple_clicked() {
    this->setStyleSheet("background-color: #663399; color: white");
}

// toggles between network scanning vs single IP scanning
void MainWindow::on_checkBox_scan_network_range_clicked() {
    // sets activation status of subnet slash label to checked status of checkbox
    ui->label_subnet_slash->setEnabled(ui->checkBox_scan_network_range->isChecked());
    // sets activation status of subnet input line edit to  checked status of checkbox
    ui->lineEdit_subnet_input->setEnabled(ui->checkBox_scan_network_range->isChecked());
    // clears what is currently in subnet input line edit after checkbox isn't checked anymore
    if (!ui->checkBox_scan_network_range->isChecked()) {
        ui->lineEdit_subnet_input->clear();
    }
}

// writes inputted OID to list in UI where all OIDs are displayed
void MainWindow::on_buttonBox_oid_input_accepted() {
    // checks if something is written in OID input line edit
    if (ui->lineEdit_oid_input->text() != "") {
        // adds OID text to list with all OIDs in UI
        ui->listWidget_oids->addItem(ui->lineEdit_oid_input->text());
        // clears line edit after OID has been added to list
        ui->lineEdit_oid_input->clear();
    }
}

// clears OID if user wants to delete it from line edit
void MainWindow::on_buttonBox_oid_input_rejected() {
    // deletes inputted text from line edit
    ui->lineEdit_oid_input->clear();
}

// removes selected OID from OIDs list in UI
void MainWindow::on_pushButton_remove_oid_clicked() {
    qDeleteAll(ui->listWidget_oids->selectedItems());
}

// writes inputted OID to list in UI where all OIDs are displayed
void MainWindow::on_lineEdit_oid_input_returnPressed() {
    // checks if something is written in OID input line edit
    if (ui->lineEdit_oid_input->text() != "") {
        // adds OID text to list with all OIDs in UI
        ui->listWidget_oids->addItem(ui->lineEdit_oid_input->text());
        // clears line edit after OID has been added to list
        ui->lineEdit_oid_input->clear();
    }
}

// checks if user wants to input custom community
void MainWindow::on_checkBox_community_clicked() {
    // sets activation status of line edit for community input to checked status of checkbox
    ui->lineEdit_community->setEnabled(ui->checkBox_community->isChecked());
    // clears what is currently in community input line edit after checkbox isn't checked anymore
    if (!ui->checkBox_community->isChecked()) {
        ui->lineEdit_community->clear();
    }
}

// calculates IPs that are to be scanned and initiates SNMP scan
void MainWindow::on_pushButton_scan_clicked() {
    // clears previous scan results from list in UI
    ui->listWidget_results->clear();
    // checks if user wants to scan network range
    if (ui->checkBox_scan_network_range->isChecked()) {
        // sets hosts in Scanner object to calculated hosts from utility class IPRangeCalculator
        // cals IPRangeCalculator calculateIPs() function that is passed the four parts of the IP and the subnet mask that are read from UI line edit fields
        s->setHosts(
                IPRangeCalculator::calculateIPs(ui->lineEdit_ip_1->text().toInt(), ui->lineEdit_ip_2->text().toInt(),
                                                ui->lineEdit_ip_3->text().toInt(), ui->lineEdit_ip_4->text().toInt(),
                                                ui->lineEdit_subnet_input->text().toInt()));
        // calls function to remove first and last host in this list (netid and broadcast IP) because they don't need to be scanned
        s->removeFirstLastHost();
    } else {
        // does the same thing as if user wanted to scan network range, except it passes /32 subnet mask
        s->setHosts(
                IPRangeCalculator::calculateIPs(ui->lineEdit_ip_1->text().toInt(), ui->lineEdit_ip_2->text().toInt(),
                                                ui->lineEdit_ip_3->text().toInt(), ui->lineEdit_ip_4->text().toInt(),
                                                32));
    }
    // iterates through OIDs in UI list
    for (int row = 0; row < ui->listWidget_oids->count(); ++row) {
        // emplaces back OIDs from UI to backend OIDs list for later use
        oids.emplace_back(strdup(ui->listWidget_oids->item(row)->text().toStdString().c_str()));
    }
    // sets OIDs in Scanner object to those created in last code block
    s->setOids(oids);
    // iterates through OIDs in backend list
    for (auto item : this->oids) {
        // frees data because they have been dynamically allocated
        free((void *) item);
    }
    // clears backend vector for OIDs
    oids.clear();
    // checks if user passed a custom community
    if (ui->checkBox_community->isChecked() && ui->lineEdit_community->text() != "") {
        // sets community to users custom community
        community = (u_char *) ui->lineEdit_community->text().toStdString().c_str();
    } else {
        // defaults to set community to public
        community = (u_char *) "public";
    }
    // initiates scan and passes pointer to UI list where results are to be displayed + community user has chosen
    s->scan(ui->listWidget_results, community);
}

