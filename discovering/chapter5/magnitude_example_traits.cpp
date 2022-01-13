#include <cmath>
#include <complex>
#include <iostream>

template <typename T> struct Magnitude { using type = T; };

template <typename T> struct Magnitude<std::complex<T>> { using type = T; };

template <typename T> auto inline min_magnitude(const T &x, const T &y) -> T {
    using std::abs;
    typename Magnitude<T>::type ax = abs(x), ay = abs(y);
    return ax < ay ? x : y;
}

auto main() -> int {
    std::complex<double> a(3.), b(4.);
    std::cout << "min_magnitude |a, b| = " << min_magnitude(a, b) << std::endl;
    return 0;
}
