#include <cmath>
#include <iostream>

// look into functors.cpp
// lambdas are basically a shorthand for functors and objects combined

template <typename F, typename T>
T inline fin_diff(F f, const T &x, const T &h) {
    return (f(x + h) - f(x)) / h;
}

auto main() -> int {
    // instead of defining psc_f as in functors.cpp
    // we just create a lambda
    auto sc_l = [](double x) { return std::sin(x) + std::cos(x); };
    std::cout << fin_diff(sc_l, 1., 0.001) << '\n';

    // we can also parametrize
    auto result = fin_diff(
        [](double x) { return std::sin(2.5 * x) + std::cos(x); }, 1., 0.001);
    std::cout << result << '\n';

    // capture by value
    double phi = 2.5;
    auto sin_phi = [phi](double x) { return std::sin(phi * x); };
    std::cout << "phi captured by value: " << fin_diff(sin_phi, 1., 0.001)
              << '\n';
    phi = 3.2;
    std::cout << "phi captured by value: " << fin_diff(sin_phi, 1., 0.001)
              << '\n';
    // NOTE: modifying phi here has no effect on the lambda!

    // capture by reference
    auto sin_phi_2 = [&phi](double x) { return std::sin(phi * x); };
    phi = 2.5;
    std::cout << "phi captured by reference: " << fin_diff(sin_phi_2, 1., 0.001)
              << '\n';
    phi = 3.0;
    std::cout << "phi captured by reference: " << fin_diff(sin_phi_2, 1., 0.001)
              << '\n';

    return 0;
}