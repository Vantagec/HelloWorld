#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <array>

struct IPAddress {
    std::array<int, 4> address;
    int first_byte;
    int second_byte;
    int third_byte;
    int fourth_byte;
};

bool compareIPAddresses(const IPAddress& ip1, const IPAddress& ip2) {
    return ip1.address < ip2.address;
}

int main() {
    std::vector<IPAddress> ipAddresses;

    std::string line;
    while (std::getline(std::cin, line)) {
        size_t pos = line.find('\t');
        if (pos != std::string::npos) {
            IPAddress ip;
            std::istringstream iss(line.substr(0, pos));
            char dot;
            iss >> ip.first_byte >> dot >> ip.second_byte >> dot >> ip.third_byte >> dot >> ip.fourth_byte;
            ip.address = {ip.first_byte, ip.second_byte, ip.third_byte, ip.fourth_byte};
            ipAddresses.push_back(ip);
        }
    }

    std::sort(ipAddresses.begin(), ipAddresses.end(), compareIPAddresses);

    for (const auto& ip : ipAddresses) {
        std::cout << ip.first_byte << '.' << ip.second_byte << '.' << ip.third_byte << '.' << ip.fourth_byte << std::endl;
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.first_byte == 1) {
            std::cout << ip.first_byte << '.' << ip.second_byte << '.' << ip.third_byte << '.' << ip.fourth_byte << std::endl;
        }
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.first_byte == 46 && ip.second_byte == 70) {
            std::cout << ip.first_byte << '.' << ip.second_byte << '.' << ip.third_byte << '.' << ip.fourth_byte << std::endl;
        }
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.address[0] == 46) {
            std::cout << ip.first_byte << '.' << ip.second_byte << '.' << ip.third_byte << '.' << ip.fourth_byte << std::endl;
        }
    }

    return 0;
}
