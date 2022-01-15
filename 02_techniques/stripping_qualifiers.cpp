#include <iostream>
#include <type_traits>

// Alexandrescu's method

template <typename T> class TypeTraits {
  private:
    template <class U> struct UnConst { using Result = U; };
    template <class U> struct UnConst<const U> { using Result = U; };

  public:
    using NonConstType = typename UnConst<T>::Result;
};

// Doc Brown's Method

template <class T> struct remove_const { using type = T; };
template <class U> struct remove_const<U const> { using type = U; };
template <class T> using remove_const_t = typename remove_const<T>::type;

// Example

auto main() -> int {
    using cc = const char;

    TypeTraits<cc>::NonConstType a = 0; // Alexandrescu
    remove_const_t<cc> b = 0;           // Doc Brown
    std::remove_const<cc>::type c = 0;  // STL

    a = 'a';
    b = 'b';
    c = 'c';

    std::cout << a << ' ' << b << ' ' << c << '\n';

    return 0;
}
