
#include "Scanner.h"
#include "Session.h"
#include <iostream>
#include <future>

Scanner::Scanner() {
    // initialize SNMP library
    init_snmp("snmpapp");
    oids.emplace_back("system.sysDescr");
    oids.emplace_back("system.sysObjectID");
    oids.emplace_back("system.sysUpTime");
    oids.emplace_back("system.sysContact");
    oids.emplace_back("system.sysName");
    oids.emplace_back("system.sysLocation");
    oids.emplace_back("ip.ipForwarding");
    oids.emplace_back("ip.ipDefaultTTL");
    oids.emplace_back("ipAddrTable");
    oids.emplace_back("host.hrStorage");
    oids.emplace_back("HostResources");

    hosts.emplace_back((char *) "10.10.30.254");
    hosts.emplace_back((char *) "10.10.30.212");
    hosts.emplace_back((char *) "10.10.30.210");
    hosts.emplace_back((char *) "10.10.30.211");

}

void Scanner::scan() {
    std::vector<Session> sessions;
    std::vector<std::future<void>> f;
    for (auto host : hosts) {
        sessions.emplace_back(Session(host, oids));
    }
    f.reserve(sessions.size());
    for (auto session : sessions) {
        std::thread t(&Session::start_session, &session);
        t.join();
    }
}