
#include "Scanner.h"
#include "Session.h"
#include <future>
#include <QListWidget>
#include "../Utility/IPRangeCalculator.h"


Scanner::Scanner() {
    // initialize SNMP library
    init_snmp("snmpapp");
}

// set up threads and sessions so that an IP or subnet can be scanned
void Scanner::scan(QListWidget *results_list, u_char *community) {
    // vector to store each thread that works on a session
    std::vector<std::thread> threads;
    // vector to store all sessions
    std::vector<Session> sessions;
    for (const auto &host : hosts) {
        // store sessions in vector
        sessions.emplace_back(Session(host, oids));
    }
    // reserve space in threads vector --> less resizing(copying)
    threads.reserve(sessions.size());
    for (const auto &session : sessions) {
        // start every thread and give it a session to work on
        threads.emplace_back(std::thread(&Session::start_session, session, results_list, community));
    }
    for (auto &t : threads) {
        // detach each thread so it can work independently
        t.detach();
    }
}

// set hosts that are to be scanned later on
void Scanner::setHosts(const std::vector<std::string> &hosts) {
    Scanner::hosts = hosts;
}

// getter for hosts
const std::vector<std::string> &Scanner::getHosts() const {
    return hosts;
}

// remove netid and broadcast ip from hosts because they don't need to be scanned
void Scanner::removeFirstLastHost() {
    hosts.erase(hosts.begin());
    hosts.erase(hosts.end());
}

// set OIDs that are requested later on when scanning
void Scanner::setOids(const std::vector<const char *> &oids) {
    // free each oid in oids vector (has to be done because they are dynamically allocated using strdup())
    for (auto item : this->oids) {
        free((void *) item);
    }
    // clear pointers in oids vector
    this->oids.clear();

    for (auto oid : oids) {
        // duplicate OIDs into vector (dynamically allocated)
        this->oids.push_back(strdup(oid));
    }
}

// getter for OIDs
const std::vector<const char *> &Scanner::getOids() const {
    return oids;
}

Scanner::~Scanner() {
    for (auto item : oids) {
        // free each oid in oids vector (has to be done because they are dynamically allocated using strdup())
        free((void *) item);
    }
    // clear pointers in oids vector
    oids.clear();
}
