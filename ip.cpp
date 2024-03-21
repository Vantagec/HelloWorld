#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct IPAddress {
    std::string address;

    bool operator<(const IPAddress& other) const {
        // Разбиваем IP-адрес на части и сравниваем их как целые числа
        std::vector<int> thisParts, otherParts;
        size_t pos = 0;
        while (pos != std::string::npos) {
            size_t newPos = address.find('.', pos);
            if (newPos == std::string::npos) {
                newPos = address.size();
            }
            thisParts.push_back(std::stoi(address.substr(pos, newPos - pos)));
            pos = newPos + 1;
        }

        pos = 0;
        while (pos != std::string::npos) {
            size_t newPos = other.address.find('.', pos);
            if (newPos == std::string::npos) {
                newPos = other.address.size();
            }
            otherParts.push_back(std::stoi(other.address.substr(pos, newPos - pos)));
            pos = newPos + 1;
        }

        return std::lexicographical_compare(thisParts.rbegin(), thisParts.rend(), otherParts.rbegin(), otherParts.rend());
    }
};

int main() {
    std::vector<IPAddress> addresses;

    // Считываем IP-адреса из стандартного ввода
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t tabPos = line.find('\t');
        if (tabPos != std::string::npos) {
            IPAddress ip;
            ip.address = line.substr(0, tabPos);
            addresses.push_back(ip);
        }
    }

    // Сортируем IP-адреса в обратном лексикографическом порядке
    std::sort(addresses.rbegin(), addresses.rend());

    // Выводим отсортированный список IP-адресов
    for (const auto& ip : addresses) {
        std::cout << ip.address << '\n';
    }

    // Фильтрация и вывод IP-адресов по заданным условиям
    for (const auto& ip : addresses) {
        if (ip.address.substr(0, ip.address.find('.')) == "1") {
            std::cout << ip.address << '\n';
        }
    }

    for (const auto& ip : addresses) {
        if (ip.address.substr(0, ip.address.find('.')) == "46" && ip.address.substr(ip.address.find('.') + 1, ip.address.find('.', ip.address.find('.') + 1) - ip.address.find('.') - 1) == "70") {
            std::cout << ip.address << '\n';
        }
    }

    for (const auto& ip : addresses) {
        if (ip.address.find(".46.") != std::string::npos) {
            std::cout << ip.address << '\n';
        }
    }

    return 0;
}
