
#include "IPRangeCalculator.h"

// gets IP address and subnet and shifts it bitwise to then convert it to a unsigned integer and calculate IPs in range
std::vector<std::string> IPRangeCalculator::calculateIPs(int x, int y, int z, int w, int subnet) {
    // stores IPs that are later calculated and returned
    std::vector<std::string> ips;
    // converts given address to unsigned integer by shifting bits
    unsigned address = (1 << 24) * x + (1 << 16) * y + (1 << 8) * z + w;
    // calculates tail
    unsigned tail = 1 << (32 - subnet);
    // calculates first address in range as unsigned integer
    unsigned network = address / tail * tail;
    // calculates last address in range as unsigned integer
    unsigned broadcast = (address / tail + 1) * tail - 1;
    {
        // reserves space in vector to avoid reallocating and copying later on
        ips.reserve(4096);
        // sets address to first address as unsigned integer and counts up until the broadcast address as unsigned integer is reached
        for (unsigned add = network; add <= broadcast; add++) {
            // calls function that converts unsigned integer number to actual IP string
            convertToIP(add, ips);
        }
    }
    // returns vector with IPs to calling function
    return ips;
}

// converts previously calculated unsigned integer to actual IP address
void IPRangeCalculator::convertToIP(unsigned int add, std::vector<std::string> &v) {
    // shifts bit by 8 places to get an octet
    auto octet = (1 << 8);
    // calculates least significant part of IP by doing modulo operation with given unsigned int and octet
    unsigned w = add % octet;
    // divides given unsigned int by octet to remove block corresponding to least significant part of the IP address
    add /= octet;
    // calculates second least significant part of IP by doing modulo operation with given unsigned int and octet
    unsigned z = add % octet;
    // divides given unsigned int by octet to remove block corresponding to second least significant part of the IP address
    add /= octet;
    // calculates third least significant part of IP by doing modulo operation with given unsigned int and octet
    unsigned y = add % octet;
    // divides given unsigned int by octet to remove block corresponding to third least significant part of the IP address
    add /= octet;
    // sets most significant part of IP to remaining unsigned int
    unsigned x = add;
    // emplaces back string with different parts of IP and adds points between each part
    v.emplace_back(std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + "." + std::to_string(w));
}
