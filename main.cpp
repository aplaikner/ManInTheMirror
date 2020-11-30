#include <iostream>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <string>
#include "Benchmarking/Timer.h"
#include "Scanner.h"
#include "Session.h"
#include "Utility/IPRangeCalculator.h"

#define INPUT_IP 1
#define DEVELOPMENT_INFORMATION 1

int main() {
#if DEVELOPMENT_INFORMATION == 1
    std::cout << "WORK IN PROGRESS - DOES NOT REPRESENT THE FINAL PRODUCT" << std::endl;
    std::cout << "Functionality: Get predefined set of information from client running an SNMP agent" << std::endl;
    std::cout << "Tested with SN-NAS\n" << std::endl;
#endif
    {
        Timer t;
        Scanner s;
        s.scan();
    }

    return 0;
}
