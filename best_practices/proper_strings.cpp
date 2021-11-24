#include <iostream>
#include <string>
#include <string_view>

// dont const return value types! no const std::string get_string() ...
std::string get_string() {
  const std::string s{"Hello There World"};
  return s;
}

void use_string(const std::string &s) { std::cout << s << '\n'; }
void use_string_view(std::string_view s) { std::cout << s << '\n'; }

auto main() -> int {

  // WARNING! don't do this
  const std::string str = get_string();
  use_string(str.c_str()); // code smell: string -> c_str -> string
  // clang-tidy warns about this - but the compiler does not show any warnings

  use_string(str); // better

  use_string_view(str); // string view is basically like a pointer - much more
                        // efficient when passed by value

  // absoulutely best - avoid the temporary
  use_string(get_string());

  // static const - it has to check a boolean / mutex check whether it is
  // initialized each time it is run - static variables add overhead
  static const std::string val{"Some Text"};
  std::cout << val << '\n';

  // use constexpr - happens at compile time
  // static const - is a code smell that should be replaced by constexpr
  constexpr static std::string_view valBetter{"Some Other Text"};
  std::cout << valBetter << '\n';

  // string concat - optimizes with consts in the right place
  // try removing consts and compare in godbolt
  // consts are important!
  const std::string greet1 = "Hello";
  const std::string greet2 = ", World!";
  const auto greet3 = greet1 + greet2;
  const auto length = greet3.size();
  std::cout << length << '\n';

  return 0;
}
