#include <bitset>
#include <iostream>

template <typename T> constexpr auto power(const T &x, int n) -> T {
    T r(1);
    while (--n > 0) {
        r *= x;
    }
    return r;
}

// counts the number of 1-bits in binary data
constexpr auto popcount(size_t x) -> size_t {
    int count = 0;
    for (; x != 0; ++count) {
        x &= x - 1;
    }
    return count;
}

// same as above using constexpr
constexpr auto popcount_two(size_t x) -> size_t {
    return x == 0 ? 0 : popcount(x & x - 1) + 1;
}

auto main() -> int {
    std::cout << power(4, 2) << '\n';
    // use std::bitset to print bits
    std::cout << popcount(11) << " in " << std::bitset<16>(11) << '\n';
    std::cout << popcount_two(16) << " in " << std::bitset<16>(16) << '\n';
    return 0;
}