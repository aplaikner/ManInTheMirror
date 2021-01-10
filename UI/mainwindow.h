#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../SNMP/Scanner.h"
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    // toggles between network scanning vs single IP scanning
    void on_checkBox_scan_network_range_clicked();

    // sets UI theme to white
    void on_radioButton_whitemode_clicked();

    // sets UI theme to darkmode with darker background and white text
    void on_radioButton_darkmode_clicked();

    // sets UI theme to rebeccapurple
    void on_radioButton_rebeccapurple_clicked();

    // writes inputted OID to list in UI where all OIDs are displayed
    void on_buttonBox_oid_input_accepted();

    // clears OID if user wants to delete it from line edit
    void on_buttonBox_oid_input_rejected();

    // removes selected OID from OIDs list in UI
    void on_pushButton_remove_oid_clicked();

    // writes inputted OID to list in UI where all OIDs are displayed
    void on_lineEdit_oid_input_returnPressed();

    // calculates IPs that are to be scanned and initiates SNMP scan
    void on_pushButton_scan_clicked();

    // checks if user wants to input custom community
    void on_checkBox_community_clicked();

private:
    // points to UI
    Ui::MainWindow *ui;
    // creates new Scanner object
    Scanner *s = new Scanner;
    // stores OIDs in backend
    std::vector<const char *> oids;
    // stores community string
    u_char *community;
};

#endif // MAINWINDOW_H
