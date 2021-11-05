#include <iostream>

template <bool> struct CompileTimeChecker { CompileTimeChecker(...); };

template <> struct CompileTimeChecker<false> {};

// clang-format off
#define STATIC_CHECK(expr, msg) \
  {\
    class ERROR_##msg{}; \
    (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg{}))); \
  }
// clang-format on

template <class To, class From> To safe_reinterpret_cast(From from) {
  STATIC_CHECK(sizeof(From) <= sizeof(To), Destination_Type_Too_Narrow);
  return reinterpret_cast<To>(from);
}

auto main() -> int {

  // no error
  char st[] = "some text\0";
  void *c = safe_reinterpret_cast<void *>(st);
  char *cs = safe_reinterpret_cast<char *>(c);
  std::cout << cs << '\n';

  // uncomment these to see the compile time error
  // char fake = safe_reinterpret_cast<char>(cs);
  // std::cout << fake << '\n';

  return 0;
}
