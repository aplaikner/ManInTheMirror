#include "SNMP/Scanner.h"
#include <QApplication>
#include "UI/mainwindow.h"

int main(int argc, char *argv[]) {
    // construct QApplication
    QApplication a(argc, argv);
    // create main window to show in UI
    MainWindow w;
    // show main window
    w.show();
    // startup application
    return QApplication::exec();
}

// TODO: Toggle on and off trap listening functionality
// TODO: Solve UDP 162 permission problem by allowing user to choose a port