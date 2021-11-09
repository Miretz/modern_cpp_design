#include <iostream>
#include <type_traits>

// Alexandrescu type select example

template <bool flag, typename T, typename U> struct my_select {
  typedef T type;
};

template <typename T, typename U> struct my_select<false, T, U> {
  typedef U type;
};

template <bool flag, typename T, typename U>
using my_select_t = typename my_select<flag, T, U>::type;

// Doc Brown type select example

// identity metafunction
template <class T> struct type_is { using type = T; };
// primary template - assumes true
template <bool, class T, class> struct IF : type_is<T> {};
// specialization
template <class T, class F> struct IF<false, T, F> : type_is<F> {};

template <bool B, class T, class F> using IF_t = typename IF<B, T, F>::type;

auto main() -> int {
  my_select_t<true, int, double> a = 123;
  my_select_t<false, int, double> b = 123;

  std::cout << typeid(a).name();
  std::cout << " a=";
  std::cout << a;
  std::cout << '\n';
  std::cout << typeid(b).name();
  std::cout << " b=";
  std::cout << b;
  std::cout << '\n';

  IF_t<true, float, double> c = 33.0;
  IF_t<false, float, double> d = 33.0;

  std::cout << typeid(c).name();
  std::cout << " c=";
  std::cout << c;
  std::cout << '\n';
  std::cout << typeid(d).name();
  std::cout << " d=";
  std::cout << d;
  std::cout << '\n';
  
  // In C++ all of this already exists in the standard library!
  // std::conditional_t
  std::conditional_t<true, int, char> e = 68;
  std::conditional_t<false, int, char> f = 68;

  std::cout << typeid(e).name();
  std::cout << " e=";
  std::cout << e;
  std::cout << '\n';
  std::cout << typeid(f).name();
  std::cout << " f=";
  std::cout << f;
  std::cout << '\n';
  
  return 0;
}
