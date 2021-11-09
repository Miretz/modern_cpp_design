#include <iostream>
#include <type_traits>

// Alexandrescu's method

template <typename T> class TypeTraits {
private:
  template <class U> struct UnConst { typedef U Result; };
  template <class U> struct UnConst<const U> { typedef U Result; };

public:
  typedef typename UnConst<T>::Result NonConstType;
};

// Doc Brown's Method

template <class T> struct remove_const { using type = T; };
template <class U> struct remove_const<U const> { using type = U; };
template <class T> using remove_const_t = typename remove_const<T>::type;

// Example

auto main() -> int {
  typedef const char cc;

  TypeTraits<cc>::NonConstType a; // Alexandrescu
  remove_const_t<cc> b;           // Doc Brown
  std::remove_const<cc>::type c;  // STL

  a = 'a';
  b = 'b';
  c = 'c';

  std::cout << a << ' ' << b << ' ' << c << '\n';

  return 0;
}
