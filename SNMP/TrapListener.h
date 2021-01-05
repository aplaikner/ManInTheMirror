
#ifndef MANINTHEMIRROR_TRAPLISTENER_H
#define MANINTHEMIRROR_TRAPLISTENER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>


#define PORT 162
#define BUFFER 1024

#include <QListWidget>
#include <mutex>

class TrapListener {
    int doListen = true;
    int socket_server;
    char buffer[BUFFER]{};
    sockaddr_in address_server{}, address_client{};
private:
    std::string executeDecodingCommand(const char *cmd, std::string &address);

    QListWidget *trap_results_list;

    void writeToUI(const std::string &trap_result);

public:
    explicit TrapListener(QListWidget *trapList);

    void listen();

};

#endif //MANINTHEMIRROR_TRAPLISTENER_H


