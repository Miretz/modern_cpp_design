#include <iostream>
#include <random>
#include <vector>

// simulate possible stock's share price development
// in the Black-Sholes model.
auto main() -> int {
    std::default_random_engine re(std::random_device{}());
    std::normal_distribution<> normal;

    const double mu = 0.05;
    const double sigma = 0.3;
    const double delta = 0.5;
    const double years = 20.01;

    const double a = sigma * std::sqrt(delta);
    const double b = delta * (mu - 0.5 * sigma * sigma);

    std::vector<double> s = {345.2}; // Initial price

    for (double t = 0.0; t < years; t += delta) {
        s.push_back(s.back() * std::exp(a * normal(re) + b));
    }

    for (const auto &v : s) {
        std::cout << v << '\n';
    }
    return 0;
}