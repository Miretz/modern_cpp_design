// memcpy is old style (C-style)
// in C++ use std::copy

#include <iostream>
#include <type_traits>

#include <initializer_list>
#include <ios>
#include <iostream>
#include <type_traits>

struct simple_point {
#ifdef __cplusplus
    simple_point(double x, double y) : x(x), y(y) {}
    simple_point() = default;
#endif
    double x, y;
};

auto main() -> int {
    simple_point p1{3.0, 7.1};
    simple_point p2;
    simple_point p3;

    static_assert(
        std::is_trivially_copyable<simple_point>::value,
        "simple_point is not as simple as you think and cannot be memcpyd!");

    memcpy(&p2, &p1, sizeof(p1));

    // proper c++ style is
    std::copy(&p1, &p1 + 1, &p3);

    std::cout << "p2 is " << p2.x << ", " << p2.y << std::endl;
    std::cout << "p3 is " << p3.x << ", " << p3.y << std::endl;

    return 0;
}