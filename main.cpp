#include <iostream>

#include "Prime.h"

int main(int argc, char** argv) {
    int x = 53;
    if (argc >= 2) {
        std::cout << "arkv[1]: " << argv[1] << std::endl;
        x = atoi(argv[1]);
    }
    int next_p = Prime::next_Prime(x);
    std::cout << "x: " << x << ", next prime: " << next_p << "." << std::endl;
    return 0;
}
