#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

using std::cout;

template <typename T> inline void test(const T &x) {
    cout << "x = " << x << " (";
    int oldp = cout.precision(std::numeric_limits<T>::digits10 + 1);
    cout << x << ")\n";
    cout.precision(oldp);
}

// example computing minimum value from a container
template <typename Container>
typename Container::value_type inline minimum(const Container &c) {
    using vt = typename Container::value_type;
    vt min_value = std::numeric_limits<vt>::max();
    for (const vt &x : c) {
        if (x < min_value) {
            min_value = x;
        }
    }
    return min_value;
}

// computing square root
template <typename T> T square_root(const T &x) {
    // epsilon is the smallest possible increment (unit of least precision)
    const T my_eps = T{2} * x * std::numeric_limits<T>::epsilon();
    T r = x;
    while (std::abs((r * r) - x) > my_eps) {
        r = (r + x / r) / T{2};
    }
    return r;
}

auto main() -> int {
    test(1.f / 3.f);
    test(1. / 3.0);
    test(1. / 3.0l);

    std::vector<double> someValues = {1.0, 7.0, 3.9, 33.2, 18.5, -700.5, -30.1};
    cout << minimum(someValues) << '\n';

    cout << square_root(157.22) << '\n';
    // stl version for comparison
    cout << std::sqrt(157.22) << '\n';

    return 0;
}