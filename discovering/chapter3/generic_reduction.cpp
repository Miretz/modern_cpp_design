#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

template <typename Iter, typename T, typename BinaryFunction>
T my_accumulate(Iter it, Iter end, T init, BinaryFunction op) {
    for (; it != end; ++it) {
        init = op(init, *it);
    }
    return init;
}

template <typename T> struct add {
    T operator()(const T &x, const T &y) const { return x + y; }
};

// we could also parametrize the oparator()
struct times {
    template <typename T> T operator()(const T &x, const T &y) const {
        return x * y;
    }
};

auto main() -> int {
    std::vector<double> v = {7.0, 8.0, 11.0};
    double s = my_accumulate(v.begin(), v.end(), 0.0, add<double>{});
    double p = my_accumulate(v.begin(), v.end(), 1.0, times{});

    std::cout << "Sum: " << s << '\n';
    std::cout << "Product: " << p << '\n';

    // std also has this - needs <numeric> and <functional> headers
    double s2 = std::accumulate(v.begin(), v.end(), 0.0, std::plus<double>{});
    double p2 =
        std::accumulate(v.begin(), v.end(), 1.0, std::multiplies<double>{});
    std::cout << "STL Sum: " << s2 << '\n';
    std::cout << "STL Product: " << p2 << '\n';

    return 0;
}