#include <cmath>
#include <complex>
#include <iostream>
#include <limits>
#include <random>

auto global_urng() -> std::default_random_engine & {
    static std::default_random_engine u{};
    return u;
}

void randomize() {
    static std::random_device rd{};
    global_urng().seed(rd());
}

auto pick(double from, double upto) -> double {
    static std::uniform_real_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(global_urng(), parm_t{from, upto});
}

using complex = std::complex<double>;

const double eps = 10 * std::numeric_limits<double>::epsilon();

inline auto similar(complex x, complex y) -> bool {
    double sum = abs(x) + abs(y);
    if (sum < 1000 * std::numeric_limits<double>::min()) {
        return true;
    }
    return abs(x - y) / sum <= eps;
}

struct distibutivity_violated {};

inline void test(complex a, complex b, complex c) {
    if (!similar(a * (b + c), a * b + a * c)) {
        std::cerr.precision(3);
        std::cerr << "Test detected that " << a << " * (" << b << " + " << c
                  << ") != " << a << " * " << b << " + " << a << " * " << c
                  << '\n';
        std::cerr.precision(15);
        std::cerr << "Compared values are: " << a * (b + c) << '\n'

                  << "                and: " << a * b + a * c << '\n';
        throw distibutivity_violated{};
    }
}

const double from = -10.0, upto = 10.0;

inline auto mypick() -> complex { return {pick(from, upto), pick(from, upto)}; }

auto main() -> int {

    const int max_test = 20;
    randomize();

    try {

        for (int i = 0; i < max_test; ++i) {
            complex a = mypick();
            for (int j = 0; j < max_test; ++j) {
                complex b = mypick();
                for (int k = 0; k < max_test; ++k) {
                    complex c = mypick();
                    test(a, b, c);
                }
            }
        }

    } catch (distibutivity_violated &err) {
        std::cerr << "Exception: Distributivity Violation\n";
    }

    return 0;
}
