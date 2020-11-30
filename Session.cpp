
#include "Session.h"
#include <iostream>

Session::Session(std::string host, std::vector<const char *> oids) : request_strings(oids), ip(host) {

}


void Session::start_session() {

    /*
     * Initialize a "session" that defines who we're going to talk to
     */

    // set up defaults
    snmp_sess_init(&session);


    session.peername = (char *) ip.c_str();


    // set SNMP version number
    session.version = SNMP_VERSION_1;

    // set SNMPv1 community name used for authentication
    session.community = (u_char *) "public";
    session.community_len = strlen(reinterpret_cast<const char *>(session.community));
    //snmp_set_do_debugging(1);
    // Establish the session
    ss = snmp_open(&session);

    //1000000 vs 100000
    //ss->timeout = 200000;
    //ss->retries = 3;

    if (!ss) {
        snmp_sess_perror("Session not created", &session);
        exit(1);
    }
    for (int i = 0; i < request_strings.size(); ++i) {
        // Create the PDU for the data for our request
        // We're going to GET the system.sysDescr.0 node
        pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
        anOID_len = MAX_OID_LEN;

        if (!snmp_parse_oid(request_strings.at(i), anOID, &anOID_len)) {
            snmp_perror(request_strings.at(i));
            //exit(1);
        }

        snmp_add_null_var(pdu, anOID, anOID_len);

        // Send the request out
        status = snmp_synch_response(ss, pdu, &response);

        // Process the response
        if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
            // SUCCESS: Print the result variables

            for (vars = response->variables; vars; vars = vars->next_variable) {
                // Mutex? If data is later on stored in vector anyway then Mutex is a must
                std::cout << ip << ":";
                print_variable(vars->name, vars->name_length, vars);
            }
        } else {
            // FAILURE: print what went wrong!
            if (status == STAT_SUCCESS) {
                std::cerr << "Error in packet\nReason: " << snmp_errstring(response->errstat) << std::endl;
            } else {
                snmp_sess_perror("snmpget", ss);
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
    snmp_close(ss);
}
