
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
    void *ss;

    // holds information we're going to send to the remote host.
    struct snmp_pdu *pdu;
    // contains information host is going to send back
    netsnmp_pdu *response;

    // holds the variables we want to manipulate via SNMP
    struct variable_list *vars;

    //  anOID holds the location of the information which we want to retrieve
    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;

    int status;

    // holds clients IP
    std::string ip;

    // stores OIDs that are requested later on
    std::vector<const char *> request_strings;
public:
    Session(std::string host, std::vector<const char*> oids);
    void start_session(QListWidget *results_list, u_char *community);

};


#endif //MANINTHEMIRROR_SESSION_H
