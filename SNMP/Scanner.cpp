
#include "Scanner.h"
#include "Session.h"
#include <iostream>
#include <future>
#include <QListWidget>
#include "../Utility/IPRangeCalculator.h"


Scanner::Scanner() {
    // initialize SNMP library
    init_snmp("snmpapp");

    //oids.emplace_back("system.sysDescr");
    //oids.emplace_back("system.sysObjectID");
    //oids.emplace_back("system.sysUpTime");
    //oids.emplace_back("system.sysContact");
    //oids.emplace_back("system.sysName");
    //oids.emplace_back("system.sysLocation");
    //oids.emplace_back("ip.ipForwarding");
    //oids.emplace_back("ip.ipDefaultTTL");
    //oids.emplace_back("host.hrStorage");
    //oids.emplace_back("HostResources");
    //oids.emplace_back("ipAddrTable");
}

void Scanner::scan(QListWidget *pWidget) {
    std::vector<std::thread> threads;
    std::vector<Session> sessions;
    for (const auto &host : hosts) {
        sessions.emplace_back(Session(host, oids));
    }
    threads.reserve(sessions.size());
    for (const auto &session : sessions) {
        //session.start_session();
        threads.emplace_back(std::thread(&Session::start_session, session, pWidget));
    }

    for (auto &t : threads) {
        t.detach();
    }
}

void Scanner::setHosts(const std::vector<std::string> &hosts) {
    Scanner::hosts = hosts;
}

const std::vector<std::string> &Scanner::getHosts() const {
    return hosts;
}

void Scanner::removeFirstLastHost() {
    hosts.erase(hosts.begin());
    hosts.erase(hosts.end());
}

void Scanner::setOids(const std::vector<const char *> &oids) {
    Scanner::oids = oids;
}

const std::vector<const char *> &Scanner::getOids() const {
    return oids;
}
