
#ifndef MANINTHEMIRROR_SESSION_H
#define MANINTHEMIRROR_SESSION_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <mutex>
#include <thread>
#include <QListWidget>

class Session {
    // holds information about who we're going to be talking to.
    // one object will be filled with information, the other is a pointer returned by the library
    struct snmp_session session;
    void *establishedSession;

    // holds information we're going to send to the remote host.
    struct snmp_pdu *snmpPDU;
    // contains information host is going to send back
    netsnmp_pdu *clientResponse;

    // holds the variables we want to manipulate via SNMP
    struct variable_list *variables;

    //  OID holds the location of the information which we want to retrieve
    oid OID[MAX_OID_LEN];
    size_t lenOID = MAX_OID_LEN;

    int status;

    // holds clients IP
    std::string ip;

    // stores OIDs that are requested later on
    std::vector<const char *> requestedOIDs;
public:
    Session(std::string host, std::vector<const char*> oids);
    void startSession(QListWidget *results_list, u_char *community);

};


#endif //MANINTHEMIRROR_SESSION_H
