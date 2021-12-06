#include <iostream>

auto main() -> int {

    int x = 4;
    auto y = [&r = x, x = x + 1]() {
        r += 2;       // r is a reference to the outer x
        return x + 2; // return x + 2 where x is the outer x + 1
    };

    std::cout << "x is " << x << '\n';
    std::cout << "y() is " << y() << '\n';

    return 0;
}