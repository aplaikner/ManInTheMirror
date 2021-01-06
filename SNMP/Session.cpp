
#include "Session.h"
#include <iostream>
#include <QListWidget>

// set host to scan and OIDs to request
Session::Session(std::string host, std::vector<const char *> oids) : request_strings(oids), ip(host){}

// declare mutex for writing to UI
static std::mutex mlock;

// get session going
void Session::start_session(QListWidget *results_list, u_char *community) {

    // initialize asynchronous session
    snmp_sess_init(&session);

    // set IP address of host that is to be scanned
    session.peername = (char *) ip.c_str();

    // set SNMP version number
    session.version = SNMP_VERSION_1;

    // set SNMPv1 community name used for authentication
    session.community = community;

    // set length of community string
    session.community_len = strlen(reinterpret_cast<const char *>(session.community));

    // establish the session asynchronously
    ss = snmp_sess_open(&session);

    if (!ss) {
        // output error message and exit if session could not be created
        snmp_sess_perror("Session not created", &session);
        exit(1);
    }
    for (int i = 0; i < request_strings.size(); i++) {
        // create the PDU for the data for request by using GETNEXT
        pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);

        // set OID length
        anOID_len = MAX_OID_LEN;

        // parse OID from vector into anOID
        if (!snmp_parse_oid(request_strings.at(i), anOID, &anOID_len)) {
            // if there is any error (OID does not exist, OID faulty, ...), output OID and go on
            snmp_perror(request_strings.at(i));
        }

        // add NULL value to end of PDU
        // for SNMPSET PDU put in the value to set the OID to
        snmp_add_null_var(pdu, anOID, anOID_len);

        // Send the request out asynchronously
        // store returned data in response variable
        status = snmp_sess_synch_response(ss, pdu, &response);

        // process and check the response
        if (status == STAT_SUCCESS && nullptr != response) {
            // SUCCESS: Continue with writing response to UI
            // get variables from response and iterate through them as long as they are not NULL
            for (vars = response->variables; vars; vars = vars->next_variable) {
                // create buffer for variable data
                char buf[1024];
                // snprintf -> write formatted output to sized buffer
                // write important variable data to sized buffer
                snprint_variable(buf, sizeof(buf), vars->name, vars->name_length, vars);
                // write host IP at beginning of message for UI
                std::string message = ip;
                message.append(":");
                // append scanned data to message for UI
                message.append(buf);
                // lock mutex while writing to UI because of multiple threads working in parallel
                mlock.lock();
                // write result data to UI by creating new item in QListWidget
                results_list->addItem(message.c_str());
                // unlock mutex to that other threads can go on writing results to UI
                mlock.unlock();
            }
        } else {
            // FAILURE: print what went wrong!
            if (status == STAT_SUCCESS) {
                // print out reason for error in packet
                std::cerr << "Error in packet\nReason: " << snmp_errstring(response->errstat) << std::endl;
            } else {
                // call this section mostly only if packet times out
                // section is empty for better performance and less verbose output in CLI
            }
        }
        // free response for next request
        if (response) {
            snmp_free_pdu(response);
        }
    }
    // close session asynchronously
    snmp_sess_close(ss);
}
