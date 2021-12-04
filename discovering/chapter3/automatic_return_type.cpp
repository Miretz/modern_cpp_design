#include <iostream>

template <typename T, typename U> inline auto max(T a, U b) {
  return a > b ? a : b;
}

auto main() -> int {
  std::cout << max<int, double>(143, 150.22) << std::endl;
  return 0;
}