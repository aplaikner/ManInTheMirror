
#include "IPRangeCalculator.h"

std::vector<std::string> IPRangeCalculator::calculate_ips(int x, int y, int z, int w, int subnet) {
    std::vector<std::string> ips;
    unsigned address = (1 << 24) * x + (1 << 16) * y + (1 << 8) * z + w;
    unsigned tail = 1 << (32 - subnet);
    unsigned network = address / tail * tail;
    unsigned broadcast = (address / tail + 1) * tail - 1;
    {
        ips.reserve(16777216);
        for (unsigned add = network; add <= broadcast; ++add) {
            print(add, ips);
        }
    }
    return ips;
}

void IPRangeCalculator::print(unsigned int add, std::vector<std::string> &v) {
    auto octet = (1 << 8);
    unsigned w = add % octet;
    add /= octet;
    unsigned z = add % octet;
    add /= octet;
    unsigned y = add % octet;
    add /= octet;
    unsigned x = add;
    v.emplace_back(std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + "." + std::to_string(w));
}
