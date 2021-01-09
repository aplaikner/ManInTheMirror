
#ifndef MANINTHEMIRROR_TRAPLISTENER_H
#define MANINTHEMIRROR_TRAPLISTENER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>

// defines port for sever to listen for traps
#define PORT 162
// sets buffer size for traps
#define BUFFER 1024

#include <QListWidget>
#include <mutex>

class TrapListener {
    int doListen = true;
    // sets variable for server running on socket
    int socket_server;
    // sets buffer where trap data is stored
    char buffer[BUFFER]{};
    // sets variables for server and client addresses
    sockaddr_in address_server{}, address_client{};
private:
    // decodes trap data to human readable form
    std::string decodeData(const char *cmd, std::string &address);

    // points to UI list where data is to be shown
    QListWidget *trap_results_list;

    // writes data to list in UI
    void writeToUI(const std::string &trap_result);

public:
    // constructor that gets pointer to UI list
    explicit TrapListener(QListWidget *trapList);

    // listens for new incoming traps
    void listen();
};

#endif //MANINTHEMIRROR_TRAPLISTENER_H


