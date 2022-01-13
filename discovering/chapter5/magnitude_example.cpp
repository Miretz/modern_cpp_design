#include <cmath>
#include <complex>
#include <iostream>

template <typename T> auto inline min_magnitude(const T &x, const T &y) -> T {
    using std::abs;
    auto ax = abs(x), ay = abs(y);
    return ax < ay ? x : y;
}

auto main() -> int {
    double d1 = 3., d2 = 4.;
    std::cout << "min |d1, d2| = " << min_magnitude(d1, d2) << '\n';

    std::complex<double> c1(3.), c2(4.);
    std::cout << "min |c1, c2| = " << min_magnitude(c1, c2) << '\n';

    return 0;
}
