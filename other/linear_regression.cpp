#include <array>
#include <iomanip>
#include <iostream>
#include <random>

// compile-time linear regression model

inline constexpr size_t n_values = 12;
inline constexpr size_t n_iterations = 100'000;

constexpr std::array<double, n_values> ys{890.0,  1411.0, 1560.0, 2220.0,
                                          2091.0, 2878.0, 3537.0, 3268.0,
                                          3920.0, 4163.0, 5471.0, 5157.0};

constexpr std::array<double, n_values> xs{1.0, 2.0, 2.0, 3.0, 3.0, 4.0,
                                          5.0, 6.0, 6.0, 6.0, 8.0, 10.0};

[[nodiscard]] inline constexpr auto j(double t0, double t1, double x, double y)
    -> double {
  return ((t0 + t1 * x) - y);
}

[[nodiscard]] constexpr auto deriv1(double t0, double t1) -> double {
  auto s = 0.0;
  for (size_t i = 0; i < n_values; ++i) {
    s = s + j(t0, t1, xs[i], ys[i]);
  }
  return (1.0 / static_cast<double>(n_values)) * s;
}

[[nodiscard]] constexpr auto deriv2(double t0, double t1) -> double {
  auto s = 0.0;
  for (size_t i = 0; i < n_values; ++i) {
    s = s + j(t0, t1, xs[i], ys[i]) * xs[i];
  }
  return (1.0 / static_cast<double>(n_values)) * s;
}

// model is trained during compilation
[[nodiscard]] constexpr auto train() -> std::pair<double, double> {
  auto t0 = 0.0;
  auto t1 = 0.0;
  constexpr auto alpha = 0.001;
  for ([[maybe_unused]] size_t i = 0; i < n_iterations; ++i) {
    t0 = t0 - alpha * deriv1(t0, t1);
    t1 = t1 - alpha * deriv2(t0, t1);
  }
  return {t0, t1};
}

auto predict(double x, std::pair<double, double> thetas) -> void {
  const auto hx = thetas.first + thetas.second * x;
  std::cout << "Input: " << std::left << std::setw(6) << x
            << "Predicted output: " << std::left << std::setw(6) << hx << '\n';
}

auto run() -> void {
  auto thetas = train();
  std::cout << "Gradient descent calcuated t0 = " << thetas.first
            << ",t1 = " << thetas.second << '\n';
  for (size_t i = 0; i < n_values; ++i) {
    predict(xs[i], thetas);
    std::cout << "Actual label: " << ys[i] << '\n';
  }

  // predict some test number
  predict(10, thetas);
}

auto main() -> int {
  std::cout.precision(6);
  run();
  return 0;
}
