
#ifndef MANINTHEMIRROR_SCANNER_H
#define MANINTHEMIRROR_SCANNER_H

#include <vector>

class Scanner {
    std::vector<const char *> oids;
    std::vector<char *> hosts;

public:
    Scanner();
    void scan();
};


#endif //MANINTHEMIRROR_SCANNER_H
