#include <iostream>
#include <type_traits>

template <auto Value> struct new_integral_constant {
  static constexpr auto value = Value;
};

auto main() -> int {

  using fortytwo_type = new_integral_constant<42>;
  using true_type = new_integral_constant<true>;
  using false_type = new_integral_constant<false>;

  static_assert(!std::is_same_v<true_type, decltype(true)>);
  static_assert(!std::is_same_v<false_type, decltype(false)>);
  static_assert(!std::is_same_v<true_type, false_type>);
  static_assert(!std::is_same_v<fortytwo_type, int>);

  static_assert(std::is_same_v<fortytwo_type, fortytwo_type>);
  static_assert(std::is_same_v<true_type, true_type>);

  return 0;
}
