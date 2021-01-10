
#ifndef MANINTHEMIRROR_IPRANGECALCULATOR_H
#define MANINTHEMIRROR_IPRANGECALCULATOR_H

#include <string>
#include <vector>

class IPRangeCalculator {
public:
    // gets IP address and subnet and shifts it bitwise to then convert it to an unsigned integer and calculate IPs in range
    static std::vector<std::string> calculateIPs(int a, int b, int c, int d, int subnet);
private:
    // converts previously calculated unsigned integer to actual IP address
    static void calcToIP(unsigned add, std::vector<std::string> &v);
};


#endif //MANINTHEMIRROR_IPRANGECALCULATOR_H
