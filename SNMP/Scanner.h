
#ifndef MANINTHEMIRROR_SCANNER_H
#define MANINTHEMIRROR_SCANNER_H

#include <vector>
#include <string>
#include <QListWidget>


class Scanner {
    // vector to store OIDs later used for scanning
    std::vector<const char *> oids;

public:
    // get OIDs
    const std::vector<const char *> &getOids() const;

public:
    // set OIDs that are requested later on when scanning
    void setOids(const std::vector<const char *> &oids);

private:
    // vector to store each host that is scanned later
    std::vector<std::string> hosts;

public:
    // get for hosts
    const std::vector<std::string> &getHosts() const;

public:
    // set hosts that are to be scanned later on
    void setHosts(const std::vector<std::string> &hosts);

public:
    // remove netid and broadcast ip from hosts because they don't need to be scanned
    void removeFirstLastHost();

public:
    Scanner();

    ~Scanner();

    // set up threads and sessions so that an IP or subnet can be scanned
    void scan(QListWidget *results_list, u_char *community);
};


#endif //MANINTHEMIRROR_SCANNER_H
