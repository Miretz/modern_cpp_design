#include <iostream>

template <typename T> T max(T a, T b) { return a > b ? a : b; }

auto main() -> int {
    std::cout << "The maximum of 3 and 5 is " << max(3, 5);
    std::cout << "\nThe maximum of 31 and 51 is " << max(31, 51);
    std::cout << "\nThe maximum of 3.0 and 5.0 is " << max(3.0, 5.0);
    std::cout << "\nExplicit float template parameter " << max<float>(3.0, 5.0);
    std::cout << '\n';
    return 0;
}
