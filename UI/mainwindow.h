#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
