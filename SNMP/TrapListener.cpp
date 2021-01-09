
#include "TrapListener.h"

static std::mutex trapLock;

TrapListener::TrapListener(QListWidget *trapList) {
    if ((socket_server = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&address_server, 0, sizeof(address_server));
    memset(&address_client, 0, sizeof(address_client));

    address_server.sin_family = AF_INET;
    address_server.sin_addr.s_addr = INADDR_ANY;
    address_server.sin_port = htons(PORT);

    if (bind(socket_server, (const struct sockaddr *) &address_server, sizeof(address_server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    trap_results_list = trapList;
}

void TrapListener::listen() {
    int len_address_client, n;
    len_address_client = sizeof(address_client);
    while (doListen) {
        n = recvfrom(socket_server, (char *) buffer, BUFFER, MSG_WAITALL, (struct sockaddr *) &address_client,
                     (socklen_t *) &len_address_client);

        std::string trapData;
        for (int i = 0; i < n; ++i) {
            char temp[100];
            snprintf(temp, sizeof(temp), "%02x ", (unsigned char) buffer[i]);
            trapData += temp;
        }
        std::string address = inet_ntoa(address_client.sin_addr);
        std::string command = "echo " + trapData + " | tr -d ' '  | xxd -r -p | openssl asn1parse -inform DER -i";
        writeToUI(decodeData(command.c_str(), address));
    }
}

std::string TrapListener::decodeData(const char *cmd, std::string &address) {
    FILE *commandPipe = popen(cmd, "r");
    if (!commandPipe) return "ERROR";
    char localBuffer[5000];
    std::string result;
    while (!feof(commandPipe)) {
        if (fgets(localBuffer, 5000, commandPipe) != nullptr)
            result += localBuffer;
    }
    pclose(commandPipe);
    result.pop_back();
    result.insert(0, "New incoming trap message from: " + address + "\n");
    return result;
}

void TrapListener::writeToUI(const std::string &trap_result) {
    trapLock.lock();
    trap_results_list->addItem(trap_result.c_str());
    trapLock.unlock();
}


