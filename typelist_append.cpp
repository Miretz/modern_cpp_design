#include <iostream>
#include <type_traits>

#include "loki-0.1.7/include/loki/Typelist.h"

using Loki::Typelist;
using Loki::NullType;
using namespace Loki::TL;

template <class TList, class T> struct MyAppend;

template <> struct MyAppend<NullType, NullType> { typedef NullType Result; };

template <class T> struct MyAppend<NullType, T> {
  typedef Typelist<T, NullType> Result;
};

template <class Head, class Tail>
struct MyAppend<NullType, Typelist<Head, Tail>> {
  typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct MyAppend<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename MyAppend<Tail, T>::Result> Result;
};

auto main() -> int {
  typedef Typelist<
      signed char,
      Typelist<short int, Typelist<int, Typelist<long int, NullType>>>>
      SignedIntegrals;

  typedef MyAppend<
      SignedIntegrals,
      Typelist<float, Typelist<double, Typelist<long double, NullType>>>>::
      Result SignedTypes;

  std::cout << Length<SignedTypes>::value << '\n';

  return 0;
}
