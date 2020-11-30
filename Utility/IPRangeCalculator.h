
#ifndef MANINTHEMIRROR_IPRANGECALCULATOR_H
#define MANINTHEMIRROR_IPRANGECALCULATOR_H

#include <string>
#include <vector>

class IPRangeCalculator {
public:
    static std::vector<std::string> calculate_ips(int a, int b, int c, int d, int subnet);
private:
    static void print(unsigned add, std::vector<std::string> &v);
};


#endif //MANINTHEMIRROR_IPRANGECALCULATOR_H
