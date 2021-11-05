#include <iostream>
#include <type_traits>

using std::cout;

// book version
template <int v> struct Int2Type {
  enum { value = v };
};

// specializations - can't call with wrong type
// compile time check
template <class T> struct NumStruct {
  void func() {
    cout << "Default NumStruct of type: " << typeid(*this).name() << '\n';
  }
};

template <> struct NumStruct<Int2Type<2>> {
  void func() { cout << "Two struct\n"; }
};

template <> struct NumStruct<Int2Type<3>> {
  void func() { cout << "Three struct\n"; }
};

auto main() -> int {
  typedef Int2Type<2> i2_t;
  typedef Int2Type<3> i3_t;

  // C++17 built-in integral constant
  typedef std::integral_constant<int, 2> ic2_t;
  typedef std::integral_constant<int, 3> ic3_t;

  // check the integral constants - book
  static_assert(!std::is_same<i2_t, i3_t>::value);
  static_assert(!std::is_same<i3_t, i2_t>::value);
  static_assert(std::is_same<i2_t, i2_t>::value);
  static_assert(std::is_same<i3_t, i3_t>::value);

  // check the integral constants - built-in
  static_assert(!std::is_same<ic2_t, ic3_t>::value);
  static_assert(!std::is_same<ic3_t, ic2_t>::value);
  static_assert(std::is_same<ic2_t, ic2_t>::value);
  static_assert(std::is_same<ic3_t, ic3_t>::value);

  // check both
  // despite having same value the type is different
  static_assert(!std::is_same<i2_t, ic2_t>::value);
  static_assert(!std::is_same<i3_t, ic3_t>::value);
  static_assert(!std::is_same<ic2_t, i2_t>::value);
  static_assert(!std::is_same<ic3_t, i3_t>::value);

  NumStruct<i2_t> s1;
  s1.func(); // Two struct
  NumStruct<i3_t> s2;
  s2.func(); // Three struct

  NumStruct<ic2_t> s3;
  s3.func(); // Default struct

  NumStruct<int> s4;
  s4.func(); // Default struct

  return 0;
}
