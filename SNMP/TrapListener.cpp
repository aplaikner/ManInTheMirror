
#include "TrapListener.h"

static std::mutex trapLock;

// sets up socket server and receives pointer to trap result list in UI
TrapListener::TrapListener(QListWidget *trapList) {
    // sets local results list to point to UI result list
    trapResultsList = trapList;

    // creates socket with IPv4, UDP and default protocol for address family
    if ((socketServer = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        // outputs error message if socket could not be created
        perror("FAILURE: SOCKET CREATION");
        // exits program
        exit(1);
    }

    // initiates storage for server address struct
    bzero((char *) &addressServer, sizeof(addressServer));
    // initiates storage for client address struct
    bzero((char *) &addressClient, sizeof(addressClient));

    // sets server address family to IPv4
    addressServer.sin_family = AF_INET;
    // sets server to accept data from any IP address
    addressServer.sin_addr.s_addr = INADDR_ANY;
    // sets port servers listens on using htons -> host to network short -> standardised form
    addressServer.sin_port = htons(PORT);

    // binds server socket with its corresponding server address and also passes length of server address
    if (bind(socketServer, (const struct sockaddr *) &addressServer, sizeof(addressServer)) < 0) {
        // outputs error message if server socket could not be bound
        perror("FAILURE: BINDING");
        // exits program
        exit(1);
    }
}

// starts listening for incoming trap messages and decodes them
void TrapListener::listen() {
    int lenAddressClient, receivedDataSize;
    // writes length of client address into variable
    lenAddressClient = sizeof(addressClient);
    // listens until doListen is false
    while (doListen) {
        // waits for data to come in and writes it to variable
        // function needs socket servers file descriptor, buffer where data is to be stored, buffer size,
        // flag to wait for full request, address of client and size of address client struct
        receivedDataSize = recvfrom(socketServer, (char *) receivedData, BUFFER, MSG_WAITALL,
                                    (struct sockaddr *) &addressClient,
                                    (socklen_t *) &lenAddressClient);
        // stores data received from trap in string form
        std::string trapData;
        // iterates through buffer as long as i is smaller than size of received message
        for (int i = 0; i < receivedDataSize; ++i) {
            char temp[100];
            // writes formatted output to sized temp buffer
            // output is written in hex form with at least 2 digits (if there is less than 2 digits per block, a 0 is preceded)
            snprintf(temp, sizeof(temp), "%02x ", (unsigned char) receivedData[i]);
            // appends temporary data to variable that stores entire trap message
            trapData += temp;
        }
        // stores address of client who wrote message
        std::string address = inet_ntoa(addressClient.sin_addr);
        // composes command to decode ASN1 DER string
        std::string command = "echo " + trapData + " | tr -d ' '  | xxd -r -p | openssl asn1parse -inform DER -i";
        // executes decoding command and writes human readable result to UI result list
        writeToUI(decodeData(command.c_str(), address));
    }
}

// decodes ASN1 DER string to human readable form using openssl
std::string TrapListener::decodeData(const char *command, std::string &address) {
    // opens pipe to console with command and mode "r"
    // with mode "r" the file descriptor of the returned stream is the readable end of the pipe
    FILE *executionPipe = popen(command, "r");
    // if pipe could not be opened return error message
    if (!executionPipe) return "FAILURE: DECODING";
    char localBuffer[5000];
    // resulting string is written into this variable
    std::string result;
    // until while loop iterator is not at end of file continue reading
    while (!feof(executionPipe)) {
        // gets data from pipe stream and writes it into buffer until stream data is not nullptr
        if (fgets(localBuffer, 5000, executionPipe) != nullptr)
            // appends temporary buffer to results string
            result += localBuffer;
    }
    // closes pipe
    pclose(executionPipe);
    // removes last character (else an empty line is displayed in UI)
    result.pop_back();
    // inserts string and clients IP into message
    result.insert(0, "New incoming trap message from: " + address + "\n");
    return result;
}

// writes decoded data to UI list
void TrapListener::writeToUI(const std::string &trap_result) {
    // locks mutex
    trapLock.lock();
    // adds new item to trap results list and writes decoded trap message into it
    trapResultsList->addItem(trap_result.c_str());
    // unlocks mutex
    trapLock.unlock();
}


