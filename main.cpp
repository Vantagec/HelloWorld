#include <iostream>
#include <cstdlib>
//cccccccc
int main(int argc, char* argv[]) {
    if (argc > 1) {
        int build_number = std::atoi(argv[1]);
        std::cout << "build " << build_number << std::endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
