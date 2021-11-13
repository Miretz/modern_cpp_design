#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>

// function template
template <typename T> T abs(T x) { return (x >= 0) ? x : -x; }

// variable template
template <typename T> T number = T(65.21);

// alias templates
template <typename T> using myvec = std::vector<T>;

// pretty print the name of the function and params
template <typename T> void nice([[maybe_unused]] T x) {
  puts(__PRETTY_FUNCTION__);
}

auto main() -> int {

  // example templated function
  double (*foo)(double) = abs<double>;
  std::cout << abs<int>(-42) << ' ' << foo(-42.2) << '\n';

  // test variable templates
  static_assert(std::is_same_v<decltype(number<int>), int>);
  static_assert(std::is_same_v<decltype(number<double>), double>);

  std::cout << std::fixed;
  std::cout << std::setprecision(2);

  std::cout << number<double> << ' ' << number<char> << ' '
            << number<int> << '\n';

  // test alias templates
  static_assert(std::is_same_v<myvec<int>, std::vector<int>>);
  static_assert(std::is_same_v<myvec<float>, std::vector<float>>);
  static_assert(std::is_same_v<myvec<double>, std::vector<double>>);

  // using __PRETTY_FUNCTION__
  nice(4);
  nice(4.2);
  nice("hello");

  return 0;
}
