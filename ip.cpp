#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct IPAddress {
    std::string address;
    int first_byte;
    int second_byte;
    int third_byte;
    int fourth_byte;
};

bool compareIPAddresses(const IPAddress& ip1, const IPAddress& ip2) {
    if (ip1.first_byte != ip2.first_byte) {
        return ip1.first_byte > ip2.first_byte;
    } else if (ip1.second_byte != ip2.second_byte) {
        return ip1.second_byte > ip2.second_byte;
    } else if (ip1.third_byte != ip2.third_byte) {
        return ip1.third_byte > ip2.third_byte;
    } else {
        return ip1.fourth_byte > ip2.fourth_byte;
    }
}

int main() {
    std::vector<IPAddress> ipAddresses;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t pos = line.find('\t');
        if (pos != std::string::npos) {
            IPAddress ip;
            ip.address = line.substr(0, pos);
            sscanf(ip.address.c_str(), "%d.%d.%d.%d", &ip.first_byte, &ip.second_byte, &ip.third_byte, &ip.fourth_byte);
            ipAddresses.push_back(ip);
        }
    }

    std::sort(ipAddresses.begin(), ipAddresses.end(), compareIPAddresses);

    for (const auto& ip : ipAddresses) {
        std::cout << ip.address << std::endl;
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.first_byte == 1) {
            std::cout << ip.address << std::endl;
        }
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.first_byte == 46 && ip.second_byte == 70) {
            std::cout << ip.address << std::endl;
        }
    }

    std::cout << std::endl;

    for (const auto& ip : ipAddresses) {
        if (ip.address.find(".46.") != std::string::npos) {
            std::cout << ip.address << std::endl;
        }
    }

    return 0;
}

