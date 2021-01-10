
#include "Session.h"
#include <iostream>
#include <QListWidget>

// sets host to scan and OIDs to request
Session::Session(std::string host, std::vector<const char *> oids) : requestedOIDs(oids), ip(host) {}

// mutex for writing to UI
static std::mutex mLock;

// gets session going
void Session::startSession(QListWidget *results_list, u_char *community) {

    // initializes asynchronous session
    snmp_sess_init(&session);

    // sets IP address of host that is to be scanned
    session.peername = (char *) ip.c_str();

    // sets SNMP version number
    session.version = SNMP_VERSION_1;

    // sets SNMPv1 community name used for authentication
    session.community = community;

    // sets length of community string
    session.community_len = strlen(reinterpret_cast<const char *>(session.community));

    // establishes the session asynchronously
    establishedSession = snmp_sess_open(&session);

    if (!establishedSession) {
        // outputs error message and exits if session could not be created
        snmp_sess_perror("Session could not be created", &session);
        exit(1);
    }
    for (int i = 0; i < requestedOIDs.size(); i++) {
        // creates the PDU for the data for request by using GETNEXT
        snmpPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);

        // sets OID length
        lenOID = MAX_OID_LEN;

        // parses OID from vector into OID
        if (!snmp_parse_oid(requestedOIDs.at(i), OID, &lenOID)) {
            // if there is any error (OID does not exist, OID faulty, ...), outputs OID and goes on
            snmp_perror(requestedOIDs.at(i));
        }

        // adds NULL value to end of PDU
        // for SNMPSET PDU put in the value to set the OID to
        snmp_add_null_var(snmpPDU, OID, lenOID);

        // sends the request out asynchronously
        // stores returned data in clientResponse variable
        status = snmp_sess_synch_response(establishedSession, snmpPDU, &clientResponse);

        // processes and checks the clientResponse
        if (status == STAT_SUCCESS && nullptr != clientResponse) {
            // SUCCESS: Continues with writing clientResponse to UI
            // gets variables from clientResponse and iterates through them as long as they are not NULL
            for (variables = clientResponse->variables; variables; variables = variables->next_variable) {
                // creates buffer for variable data
                char buf[1024];
                // snprintf -> writes formatted output to sized buffer
                // writes important variable data to sized buffer
                snprint_variable(buf, sizeof(buf), variables->name, variables->name_length, variables);
                // writes host IP at beginning of message for UI
                std::string message = ip;
                message.append(":");
                // appends scanned data to message for UI
                message.append(buf);
                // locks mutex while writing to UI because of multiple threads working in parallel
                mLock.lock();
                // writes result data to UI by creating new item in QListWidget
                results_list->addItem(message.c_str());
                // unlocks mutex to that other threads can go on writing results to UI
                mLock.unlock();
            }
        } else {
            // FAILURE: prints what went wrong
            if (status == STAT_SUCCESS) {
                // prints out reason for error in packet
                std::cerr << "Error in packet\nReason: " << snmp_errstring(clientResponse->errstat) << std::endl;
            } else {
                // this section is mostly only called if packet times out
                // section is empty for better performance and less verbose output in CLI
            }
        }
        if (clientResponse) {
            // frees clientResponse for next request
            snmp_free_pdu(clientResponse);
        }
    }
    // closes session asynchronously
    snmp_sess_close(establishedSession);
}
