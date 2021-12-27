#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

auto add(double x, double y) -> double { return x + y; }

auto mul(double x, double y) -> double { return x * y; }

inline auto sub(double x, double y) -> double { return x - y; }

struct mult {
    auto operator()(double x, double y) const -> double { return x * y; }
};

template <typename Value> struct power {
    auto operator()(Value x, Value y) -> Value const { return std::pow(x, y); }
};

struct greater_t {
    template <typename Value> auto operator()(Value x, Value y) -> Value const {
        return x > y;
    }
} greater_than;

auto main() -> int {
    using bin_fun = std::function<double(double, double)>;
    bin_fun f = &add;
    std::cout << "f(6,3) = " << f(6, 3) << std::endl;

    std::vector<bin_fun> functions;
    functions.emplace_back(add);
    functions.emplace_back(sub);
    functions.emplace_back(mult{}); // also works for functors
    functions.emplace_back(power<double>{});
    functions.emplace_back(greater_than);
    functions.emplace_back([](double x, double y) { return x / y; });

    for (auto &vf : functions) {
        std::cout << "vf(6,3) = " << vf(6, 3) << '\n';
    }

    return 0;
}