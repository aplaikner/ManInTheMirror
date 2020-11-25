#include <iostream>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>
#include <string>

#define INPUT_IP 0
#define DEVELOPMENT_INFORMATION 0

int main() {
#if DEVELOPMENT_INFORMATION == 1
    std::cout << "WORK IN PROGRESS - DOES NOT REPRESENT THE FINAL PRODUCT" << std::endl;
    std::cout << "Functionality: Get predefined set of information from client running an SNMP agent" << std::endl;
    std::cout << "Tested with SN-NAS\n" << std::endl;
#endif

    // Holds information about who we're going to be talking to.
    // One object will be filled with information, the other is a pointer returned by the library
    struct snmp_session session, *ss;

    // Holds information we're going to send to the remote host.
    // The second one contains information they are going to send back
    struct snmp_pdu *pdu;
    struct snmp_pdu *response;

    // This will hold the variables we want to manipulate via SNMP
    struct variable_list *vars;

    // AN OID is going to hold the location of the information which we want to retrieve
    oid anOID[MAX_OID_LEN];
    size_t anOID_len = MAX_OID_LEN;

    int status;
    char *ip = new char;

    std::vector<const char *> request_strings;
    request_strings.emplace_back("system.sysDescr");
    request_strings.emplace_back("system.sysObjectID");
    request_strings.emplace_back("system.sysUpTime");
    request_strings.emplace_back("system.sysContact");
    request_strings.emplace_back("system.sysName");
    request_strings.emplace_back("system.sysLocation");
    request_strings.emplace_back("system.sysORLastChange");
    request_strings.emplace_back("ip.ipForwarding");
    request_strings.emplace_back("ip.ipDefaultTTL");
    request_strings.emplace_back("ipAddrTable");
    request_strings.emplace_back("host.hrStorage");
    request_strings.emplace_back("HostResources");

#if INPUT_IP == 1
    std::cout << "Input target IP:";
    std::cin >> ip;
#else
    ip = "10.10.30.254";
#endif
    // initialize SNMP library
    init_snmp("snmpapp");

    /*
     * Initialize a "session" that defines who we're going to talk to
     */

    // set up defaults
    snmp_sess_init(&session);
    session.peername = ip;


    // set SNMP version number
    session.version = SNMP_VERSION_1;

    // set SNMPv1 community name used for authentication
    session.community = (u_char *) "public";
    session.community_len = strlen(reinterpret_cast<const char *>(session.community));

    // Establish the session
    ss = snmp_open(&session);

    if (!ss) {
        snmp_sess_perror("ack", &session);
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

    return 0;
}
