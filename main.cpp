#include <iostream>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <string>
#include "Benchmarking/Timer.h"
#include "Scanner.h"
#include "Session.h"

#define INPUT_IP 1
#define DEVELOPMENT_INFORMATION 1

int main() {
#if DEVELOPMENT_INFORMATION == 1
    std::cout << "WORK IN PROGRESS - DOES NOT REPRESENT THE FINAL PRODUCT" << std::endl;
    std::cout << "Functionality: Get predefined set of information from client running an SNMP agent" << std::endl;
    std::cout << "Tested with SN-NAS\n" << std::endl;
#endif
    Scanner s;
    s.scan();
/*
    std::vector<const char *> request_strings;
    request_strings.emplace_back("system.sysDescr");
    request_strings.emplace_back("system.sysObjectID");
    request_strings.emplace_back("system.sysUpTime");
    request_strings.emplace_back("system.sysContact");
    request_strings.emplace_back("system.sysName");

    Session s((char *) "10.10.30.254", request_strings);
*/

    std::string oof;
    std::cin >> oof;
    return 0;
}
