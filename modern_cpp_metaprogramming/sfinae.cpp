#include <iostream>
#include <random>
#include <sstream>
#include <type_traits>

// Ugly SFINAE example

struct HasX {
  int x;
};
struct HasY {
  int y;
};

template <typename T, typename = decltype(T::x)> void print_xy(T const &obj) {
  std::cout << "x: " << obj.x << '\n';
}

template <typename T, typename = decltype(T::y), typename = void>
void print_xy(T const &obj) {
  std::cout << "y: " << obj.y << '\n';
}

static void example_sfinae() {
  HasX has_x{3};
  print_xy(has_x);
  HasY has_y{5};
  print_xy(has_y);
}

// just helper for printing

template <typename... Args> void print_multiple(Args &&...params) {
  std::stringstream ss;
  [[maybe_unused]] auto _ = {
      (static_cast<void>(ss << std::forward<Args>(params) << ", "), 0)...};
  std::cout << '\n' << ss.str() << '\n';
}

// enable if with SFINAE example

template <typename T, typename REng>
auto random_number(REng &&engine, T min, T max)
    -> std::enable_if_t<std::is_floating_point_v<T>, T> {
  return std::uniform_real_distribution<T>{min, max}(engine);
}

template <typename T, typename REng>
auto random_number(REng &&engine, T min, T max)
    -> std::enable_if_t<std::is_integral_v<T>, T> {
  return std::uniform_int_distribution<T>{min, max}(engine);
}

static void example_enable_if() {
  std::default_random_engine engine{0};
  auto rnd1 = random_number(engine, 0.f, 100.f);
  auto rnd2 = random_number(engine, 1, 6);
  auto rnd3 = random_number<float>(engine, 0.5, 1.5);
  auto rnd4 = random_number<double>(engine, 1, 6);
  auto rnd5 = random_number<std::uint32_t>(engine, 42, 420);

  static_assert(std::is_same_v<decltype(rnd1), float>);
  static_assert(std::is_same_v<decltype(rnd2), int>);
  static_assert(std::is_same_v<decltype(rnd3), float>);
  static_assert(std::is_same_v<decltype(rnd4), double>);
  static_assert(std::is_same_v<decltype(rnd5), std::uint32_t>);

  print_multiple(rnd1, rnd2, rnd3, rnd4, rnd5);
}

auto main() -> int {
  example_sfinae();
  example_enable_if();
  return 0;
}
