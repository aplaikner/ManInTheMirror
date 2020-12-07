
#include "Scanner.h"
#include "Session.h"
#include <future>
#include <QListWidget>
#include "../Utility/IPRangeCalculator.h"


Scanner::Scanner() {
    // initialize SNMP library
    init_snmp("snmpapp");
}

void Scanner::scan(QListWidget *results_list, u_char *community) {
    std::vector<std::thread> threads;
    std::vector<Session> sessions;
    for (const auto &host : hosts) {
        sessions.emplace_back(Session(host, oids));
    }
    threads.reserve(sessions.size());
    for (const auto &session : sessions) {
        threads.emplace_back(std::thread(&Session::start_session, session, results_list, community));
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
    for (auto item : this->oids) {
        delete item;
    }
    this->oids.clear();

    for (auto oid : oids) {
        this->oids.push_back(strdup(oid));
    }
}

const std::vector<const char *> &Scanner::getOids() const {
    return oids;
}

Scanner::~Scanner() {
    for (auto item : oids) {
        delete item;
    }
    oids.clear();
}
