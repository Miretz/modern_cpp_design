#include <iostream>
#include <type_traits>

#include "../loki-0.1.7/include/loki/Typelist.h"

using Loki::NullType;
using Loki::Typelist;
using namespace Loki::TL;

template <class TList, class T> struct MyIndexOf;

template <class T> struct MyIndexOf<NullType, T> {
  enum { value = -1 };
};

template <class T, class Tail> struct MyIndexOf<Typelist<T, Tail>, T> {
  enum { value = 0 };
};

template <class Head, class Tail, class T>
struct MyIndexOf<Typelist<Head, Tail>, T> {
private:
  enum { temp = MyIndexOf<Tail, T>::value };

public:
  enum { value = temp == -1 ? -1 : 1 + temp };
};

auto main() -> int {
  typedef Typelist<
      signed char,
      Typelist<short int, Typelist<int, Typelist<long int, NullType>>>>
      SignedIntegrals;

  int search_result = MyIndexOf<SignedIntegrals, int>::value;

  std::cout << search_result << '\n';

  return 0;
}
