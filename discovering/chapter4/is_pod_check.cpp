// POD - Plain Old Data type
// types and simple classes that can be used in a C program
// <type_traits> has is_pod function to check if an object is POD

#include <initializer_list>
#include <ios>
#include <iostream>
#include <type_traits>

struct simple_point {
#ifdef __cplusplus
    simple_point(double x, double y) : x(x), y(y) {}
    simple_point() = default;
    simple_point(std::initializer_list<double> il) {
        auto it = begin(il);
        x = *it;
        y = *std::next(it);
    }
#endif
    double x, y;
};

auto main() -> int {
#if __cplusplus < 201703L

    std::cout << "simple_point is pod = " << std::boolalpha
              << std::is_pod<simple_point>::value << std::endl;

// note that is_pod is deprecated in C++20
#else
    
    std::cout << "simple_point is pod = " << std::boolalpha
              << (std::is_standard_layout<simple_point>::value &&
                  std::is_trivial<simple_point>::value)
              << std::endl;

#endif

    // the __cplusplus macro is defined in all C++ compilers
    // prints out which standard does the compiler supports
    std::cout << __cplusplus << std::endl;
    return 0;
}