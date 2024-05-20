#include <iostream>
#include <print_ip.h>
#include "version.h"

using namespace std;


int main()
{
    using namespace std;

    cout << "print-ip version: " << PROJECT_VERSION << endl;

    print_ip(int8_t{-1}) << std::endl;
    print_ip(int16_t{0}) << std::endl;
    print_ip(int32_t{2130706433}) << std::endl;
    print_ip(int64_t{8875824491850138409}) << std::endl;
    print_ip(std::string{"Hello, World!"}) << std::endl;
    print_ip(std::vector<int>{100, 200, 300, 400}) << std::endl;
    print_ip(std::list<short>{400, 300, 200, 100}) << std::endl;
    print_ip(std::make_tuple(123, 456, 789, 0)) << std::endl;

    return 0;
}
