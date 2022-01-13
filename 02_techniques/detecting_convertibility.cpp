#include <array>
#include <iostream>
#include <vector>

template <class T, class U> class Conversion {
    using Small = char;
    class Big {
      public:
        std::array<char, 2> dummy;
    };

    static auto test(U) -> Small;
    static auto test(...) -> Big;

    static auto make_T() -> T;

  public:
    enum { exists = sizeof(test(make_T())) == sizeof(Small) }; // NOLINT
    enum { sameType = false };
};

template <class T> class Conversion<T, T> {
  public:
    enum { exists = 1, sameType = 1 };
};

// determine ineritance
// true if U inherits from T or if T and U are the same type
// clang-format off
// NOLINTNEXTLINE
#define SUPERSUBCLASS(T, U) \
  (Conversion<const U*, const T*>::exists && \
  !Conversion<const T*, const void*>::sameType)

// stricter test - false if T and U are same type
// NOLINTNEXTLINE
#define SUPERSUBCLASS_STRICT(T, U) \
  (SUPERSUBCLASS(T, U) && \
  !Conversion<const T, const U>::sameType)
// clang-format on

class Base {};
class Sub : public Base {};
class Unrelated {};

auto main() -> int {
    // 1 0 0
    std::cout << Conversion<double, int>::exists << ' '
              << Conversion<char, char *>::exists << ' '
              << Conversion<size_t, std::vector<int>>::exists << '\n';

    // 1 0 0
    std::cout << Conversion<int, int>::sameType << ' '
              << Conversion<char, int>::sameType << ' '
              << Conversion<int, double>::sameType << '\n';

    // 1 1 0
    std::cout << SUPERSUBCLASS(Base, Sub) << ' ' //
              << SUPERSUBCLASS(Base, Base) << ' '
              << SUPERSUBCLASS(Base, Unrelated) << '\n';

    // 1 0 0
    std::cout << SUPERSUBCLASS_STRICT(Base, Sub) << ' '
              << SUPERSUBCLASS_STRICT(Base, Base) << ' '
              << SUPERSUBCLASS_STRICT(Base, Unrelated) << '\n';

    return 0;
}
