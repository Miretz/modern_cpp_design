#include <array>
#include <iostream>

template <typename T, typename U>
void foo([[maybe_unused]] std::array<T, sizeof(U)> x,
         [[maybe_unused]] std::array<U, sizeof(T)> y, [[maybe_unused]] int z) {
  puts(__PRETTY_FUNCTION__);
}

auto main() -> int {
  foo(std::array<int, 8>{}, std::array<double, 4>{}, 0.0);
  // foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0);
  return 0;
}
