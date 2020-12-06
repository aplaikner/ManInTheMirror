
#ifndef MANINTHEMIRROR_SESSION_H
#define MANINTHEMIRROR_SESSION_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <mutex>
#include <thread>
#include <QListWidget>

class Session {
    // Holds information about who we're going to be talking to.
    // One object will be filled with information, the other is a pointer returned by the library
    struct snmp_session session;
    void *ss;

    // Holds information we're going to send to the remote host.
    // The second one contains information they are going to send back
    struct snmp_pdu *pdu;
    netsnmp_pdu *response;

    // This will hold the variables we want to manipulate via SNMP
    struct variable_list *vars;

    // AN OID is going to hold the location of the information which we want to retrieve
    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;

    int status;

    // Points to IP of Client
    std::string ip;

    // Vector with OIDs
    std::vector<const char *> request_strings;
public:
    Session(std::string host, std::vector<const char*> oids);
    void start_session(QListWidget *results_list, u_char *community);

};


#endif //MANINTHEMIRROR_SESSION_H
