#include <iostream>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <string>
#include "Benchmarking/Timer.h"
#include "SNMP/Scanner.h"
#include "SNMP/Session.h"
#include "Utility/IPRangeCalculator.h"
#include <QApplication>
#include "UI/mainwindow.h"


#define DEVELOPMENT_INFORMATION 0
#define SCAN 0

int main(int argc, char *argv[]) {
#if DEVELOPMENT_INFORMATION == 1
    std::cout << "WORK IN PROGRESS - DOES NOT REPRESENT THE FINAL PRODUCT" << std::endl;
    std::cout << "Functionality: Get predefined set of information from client running an SNMP agent" << std::endl;
    std::cout << "Tested with SN-NAS\n" << std::endl;
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO: Implement changing community string in UI