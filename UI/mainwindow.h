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


    void on_checkBox_scan_network_range_clicked();

    void on_radioButton_whitemode_clicked();

    void on_radioButton_darkmode_clicked();

    void on_radioButton_rebeccapurple_clicked();

    void on_buttonBox_oid_input_accepted();

    void on_buttonBox_oid_input_rejected();

    void on_pushButton_remove_oid_clicked();

    void on_lineEdit_oid_input_returnPressed();

    void on_pushButton_scan_clicked();

    void on_checkBox_community_clicked();

private:
    Ui::MainWindow *ui;
    Scanner *s = new Scanner;
    std::vector<const char *> oids;
    u_char *community;
};

#endif // MAINWINDOW_H
