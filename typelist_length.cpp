#include <iostream>

#include "loki-0.1.7/include/loki/Typelist.h"

using Loki::Typelist;
using namespace Loki::TL;

class NullType {};

template <class TList> struct MyLength;

template <> struct MyLength<NullType> {
  enum { value = 0 };
};

template <class T, class U> struct MyLength<Typelist<T, U>> {
  enum { value = 1 + MyLength<U>::value };
};

auto main() -> int {
  typedef Typelist<
      signed char,
      Typelist<short int, Typelist<int, Typelist<long int, NullType>>>>
      SignedIntegrals;

  int len = MyLength<SignedIntegrals>::value;

  std::cout << len << '\n';

  return 0;
}
