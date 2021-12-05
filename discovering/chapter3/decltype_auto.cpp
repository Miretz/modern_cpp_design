#include <iostream>
#include <vector>

struct too_small {};
struct too_large {};

// view on vector which test wheter given values are in range
template <typename Vector> class value_range_vector {
    using value_type = typename Vector::value_type;
    using size_type = typename Vector::size_type;

  public:
    value_range_vector(Vector &vref, value_type minv, value_type maxv)
        : vref(vref), minv(minv), maxv(maxv) {}

    // using decltype here to return result of [] with exactly the same
    // qualifiers
    decltype(auto) operator[](size_type i) {
        decltype(auto) value = vref[i];
        if (value < minv)
            throw too_small{};
        if (value > maxv)
            throw too_large{};
        return value;
    }

  private:
    Vector &vref;
    value_type minv, maxv;
};

auto main() -> int {
    using Vec = std::vector<double>;
    Vec v = {2.3, 8.1, 9.2};

    value_range_vector<Vec> w(v, 1.0, 10.0);
    decltype(auto) val = w[1]; // val is double& as wanted
    // if we used auto here it would be just double

    std::cout << val << '\n';

    return 0;
}