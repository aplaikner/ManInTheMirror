#include "SNMP/Scanner.h"
#include <QApplication>
#include "UI/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO: Update README with new trap listening functionality
// TODO: Toggle on and off trap listening functionality
// TODO: Solve UDP 162 permission problem by allowing user to choose a port