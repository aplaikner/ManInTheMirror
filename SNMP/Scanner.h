
#ifndef MANINTHEMIRROR_SCANNER_H
#define MANINTHEMIRROR_SCANNER_H

#include <vector>
#include <string>
#include <QListWidget>

class Scanner {
    std::vector<const char *> oids;
public:
    const std::vector<const char *> &getOids() const;

public:
    void setOids(const std::vector<const char *> &oids);

private:
    std::vector<std::string> hosts;
public:
    const std::vector<std::string> &getHosts() const;

public:
    void setHosts(const std::vector<std::string> &hosts);
    void removeFirstLastHost();

public:
    Scanner();
    ~Scanner();
    void scan(QListWidget *results_list, u_char *community);
};


#endif //MANINTHEMIRROR_SCANNER_H
