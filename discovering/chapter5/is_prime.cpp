#include <ios>
#include <iostream>

// compile-time prime number check

// our own square root if the compiler does not provide a
// constexpr version
constexpr auto const_abs(double x) -> double { return x >= 0 ? x : -x; }
constexpr auto square_root(int x) -> int {
    double r = x, dx = x;
    while (const_abs((r * r) - dx) > 0.1) {
        r = (r + dx / r) / 2;
    }
    return static_cast<int>(r);
}

// C++14 version
constexpr auto is_prime(int i) -> bool {
    if (i == 1) {
        return false;
    }
    if (i % 2 == 0) {
        return i == 2;
    }
    int max_check = static_cast<int>(square_root(i)) + 1;
    for (int j = 3; j < max_check; j += 2) {
        if (i % j == 0) {
            return false;
        }
    }
    return true;
}

// C++11 restricted version
constexpr auto is_prime_aux(int i, int div) -> bool {
    return div >= i ? true : (i % div == 0 ? false : is_prime_aux(i, div + 2));
}
constexpr auto is_prime_restricted(int i) -> bool {
    return i == 1 ? false : (i % 2 == 0 ? i == 2 : is_prime_aux(i, 3));
}

auto main() -> int {
    std::cout << std::boolalpha;
    std::cout << "is_prime(2) = " << is_prime(2) << '\n';
    std::cout << "is_prime_restricted(2) = " << is_prime_restricted(3) << '\n';

    std::cout << "is_prime(18) = " << is_prime(18) << '\n';
    std::cout << "is_prime_restricted(18) = " << is_prime_restricted(18)
              << '\n';

    return 0;
}