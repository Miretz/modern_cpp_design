#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

constexpr double area(const double r) { return r * r * M_PI; }

constexpr size_t kElements = 4;
constexpr std::array<double, kElements> pipes{1.0, 3.2, 3.5, 9.2};
constexpr std::array<double, kElements> hoses{4.2, 1.9, 9.8, 2.2};

double total_area_all() {

  const auto accumulate_area = [](const auto lhs, const auto rhs) {
    return lhs + area(rhs);
  };

  const auto total_area = [&](const auto &container) {
    return std::accumulate(begin(container), end(container), 0.0,
                           accumulate_area);
  };

  return total_area(pipes) + total_area(hoses);
}

auto main() -> int {

  std::cout << total_area_all();
  return 0;
}
