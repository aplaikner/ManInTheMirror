
#include "Scanner.h"
#include "Session.h"
#include <iostream>
#include <future>
#include "Utility/IPRangeCalculator.h"


Scanner::Scanner() {
    // initialize SNMP library
    init_snmp("snmpapp");
    oids.emplace_back("system.sysDescr");
    //oids.emplace_back("system.sysObjectID");
    //oids.emplace_back("system.sysUpTime");
    //oids.emplace_back("system.sysContact");
    //oids.emplace_back("system.sysName");
    //oids.emplace_back("system.sysLocation");
    //oids.emplace_back("ip.ipForwarding");
    //oids.emplace_back("ip.ipDefaultTTL");
    //oids.emplace_back("host.hrStorage");
    //oids.emplace_back("HostResources");
    oids.emplace_back("ipAddrTable");

    hosts = IPRangeCalculator::calculate_ips(10, 10, 30, 0, 24);
    hosts.erase(hosts.begin());
    hosts.erase(hosts.end());

}

void Scanner::scan() {
    std::vector<std::thread> threads;
    std::vector<Session> sessions;
    for (auto host : hosts) {
        sessions.emplace_back(Session(host, oids));
    }
    threads.reserve(sessions.size());
    for (auto session : sessions) {
        session.start_session();
        //threads.emplace_back(std::thread(&Session::start_session, &session));
    }
/*
    for (auto &t : threads) {
        t.join();
    }
*/
}