
#ifndef MANINTHEMIRROR_SCANNER_H
#define MANINTHEMIRROR_SCANNER_H

#include <vector>
#include <string>

class Scanner {
    std::vector<const char *> oids;
    std::vector<std::string> hosts;

public:
    Scanner();
    void scan();
};


#endif //MANINTHEMIRROR_SCANNER_H
