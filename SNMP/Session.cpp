
#include "Session.h"
#include <iostream>
#include <QListWidget>

Session::Session(std::string host, std::vector<const char *> oids) : request_strings(oids), ip(host) {

}

static std::mutex mlock;

void Session::start_session(QListWidget *results_list, u_char *community) {

    /*
     * Initialize a "session" that defines who we're going to talk to
     */

    // set up defaults
    snmp_sess_init(&session);


    session.peername = (char *) ip.c_str();


    // set SNMP version number
    session.version = SNMP_VERSION_1;

    // set SNMPv1 community name used for authentication
    session.community = community;

    session.community_len = strlen(reinterpret_cast<const char *>(session.community));

    // Establish the session
    ss = snmp_sess_open(&session);


    if (!ss) {
        snmp_sess_perror("Session not created", &session);
        exit(1);
    }
    for (int i = 0; i < request_strings.size(); ++i) {
        // Create the PDU for the data for our request
        pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
        anOID_len = MAX_OID_LEN;

        if (!snmp_parse_oid(request_strings.at(i), anOID, &anOID_len)) {
            snmp_perror(request_strings.at(i));
        }

        snmp_add_null_var(pdu, anOID, anOID_len);

        // Send the request out
        status = snmp_sess_synch_response(ss, pdu, &response);

        // Process the response
        if (status == STAT_SUCCESS && nullptr != response) {
            // SUCCESS: Continue with writing response to UI
            for (vars = response->variables; vars; vars = vars->next_variable) {
                char buf[1024];
                snprint_variable(buf, sizeof(buf), vars->name, vars->name_length, vars);
                std::string message = ip.c_str();
                message.append(":");
                message.append(buf);
                mlock.lock();
                results_list->addItem(message.c_str());
                mlock.unlock();
            }
        } else {
            // FAILURE: print what went wrong!
            if (status == STAT_SUCCESS) {
                std::cerr << "Error in packet\nReason: " << snmp_errstring(response->errstat) << std::endl;
            } else {
                //std::cout << ip << ("Error with response") << std::endl;

            }
        }
        // Clean up:
        // 1) Free the response
        if (response) {
            snmp_free_pdu(response);
        }
    }
    // Final clean up:
    // 2) close the session
    snmp_sess_close(ss);
}
