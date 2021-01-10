
#include "Scanner.h"
#include "Session.h"
#include <future>
#include <QListWidget>
#include "../Utility/IPRangeCalculator.h"


Scanner::Scanner() {
    // initializes SNMP library
    init_snmp("snmpapp");
}

// sets up threads and sessions so that an IP or subnet can be scanned
void Scanner::scan(QListWidget *results_list, u_char *community) {
    // stores each thread that works on a session
    std::vector<std::thread> threads;
    // stores all sessions
    std::vector<Session> sessions;
    for (const auto &host : hosts) {
        // creates sessions in vector
        sessions.emplace_back(Session(host, oids));
    }
    // reserves space in threads vector --> less resizing(copying)
    threads.reserve(sessions.size());
    for (const auto &session : sessions) {
        // starts every thread and gives it a session to work on
        threads.emplace_back(std::thread(&Session::startSession, session, results_list, community));
    }
    for (auto &t : threads) {
        // detaches each thread so it can work independently
        t.detach();
    }
}

// sets hosts that are to be scanned later on
void Scanner::setHosts(const std::vector<std::string> &hosts) {
    Scanner::hosts = hosts;
}

// gets hosts
const std::vector<std::string> &Scanner::getHosts() const {
    return hosts;
}

// removes netid and broadcast IP from hosts because they don't need to be scanned
void Scanner::removeFirstLastHost() {
    hosts.erase(hosts.begin());
    hosts.erase(hosts.end());
}

// sets OIDs that are requested later on when scanning
void Scanner::setOids(const std::vector<const char *> &oids) {
    // frees each oid in oids vector (has to be done because they are dynamically allocated using strdup())
    for (auto item : this->oids) {
        free((void *) item);
    }
    // clears pointers in oids vector
    this->oids.clear();

    for (auto oid : oids) {
        // duplicates OIDs into vector (dynamically allocated)
        this->oids.push_back(strdup(oid));
    }
}

// gets OIDs
const std::vector<const char *> &Scanner::getOids() const {
    return oids;
}

Scanner::~Scanner() {
    for (auto item : oids) {
        // frees each oid in oids vector (has to be done because they are dynamically allocated using strdup())
        free((void *) item);
    }
    // clears pointers in oids vector
    oids.clear();
}
