#include <iostream>
#include <type_traits>

template <typename... Types> struct TypeList {};

// concat type lists

template <typename, typename> struct ConcatTypeListImpl;

template <typename... TA, typename... TB>
struct ConcatTypeListImpl<TypeList<TA...>, TypeList<TB...>> {
  using Type = TypeList<TA..., TB...>;
};

template <typename TA, typename TB>
using ConcatTypeList = typename ConcatTypeListImpl<TA, TB>::Type;

// another way to concat type lists

template <typename... TA, typename... TB>
constexpr auto concat_type_list(TypeList<TA...>, TypeList<TB...>)
    -> TypeList<TA..., TB...> {
  return {};
}

// get type by index

template <size_t Index, typename First, typename... Rest>
struct IndexTypesImpl {
  static_assert(Index <= sizeof...(Rest), "index out ouf range");
  using Type = typename IndexTypesImpl<Index - 1, Rest...>::Type;
};

template <typename First, typename... Rest>
struct IndexTypesImpl<0, First, Rest...> {
  using Type = First;
};

template <size_t Index, typename... Types>
using IndexTypes = typename IndexTypesImpl<Index, Types...>::Type;

// check if type list contains type

template <typename T, typename... Types> constexpr bool ContainsType = false;

template <typename T, typename... Rest>
constexpr bool ContainsType<T, T, Rest...> = true;

template <typename T, typename U, typename... Rest>
constexpr bool ContainsType<T, U, Rest...> = ContainsType<T, Rest...>;

// append type if not in the list

template <typename T, typename... Types>
using AppendTypeUnique =
    std::conditional_t<ContainsType<T, Types...>, TypeList<Types...>,
                       TypeList<Types..., T>>;

// convert the type list to contain only unique elements

template <typename... Results>
constexpr auto unique_type_list(TypeList<Results...>, TypeList<>)
    -> TypeList<Results...> {
  return {};
}

template <typename... Results, typename First, typename... Inputs>
constexpr auto unique_type_list(TypeList<Results...>,
                                TypeList<First, Inputs...>)
    -> decltype(unique_type_list(AppendTypeUnique<First, Results...>{},
                                 TypeList<Inputs...>{})) {
  return {};
}

template <typename... Types>
using UniqueTypeList =
    decltype(unique_type_list(TypeList<>{}, TypeList<Types...>{}));

// tests

auto main() -> int {
  static_assert(std::is_same_v<TypeList<bool, float, int, char, unsigned>,
                               ConcatTypeList<TypeList<bool, float, int>,
                                              TypeList<char, unsigned>>>);
  static_assert(
      std::is_same_v<TypeList<bool, float, int, char, unsigned>,
                     decltype(concat_type_list(TypeList<bool, float, int>{},
                                               TypeList<char, unsigned>{}))>);

  static_assert(std::is_same_v<bool, IndexTypes<0, bool, int, float>>);
  static_assert(std::is_same_v<int, IndexTypes<1, bool, int, float>>);
  static_assert(std::is_same_v<float, IndexTypes<2, bool, int, float>>);

  static_assert(ContainsType<int, float, double, int, void>);
  static_assert(!ContainsType<short, float, double, int, void>);

  static_assert(std::is_same_v<TypeList<bool, int, float, double>,
                               AppendTypeUnique<double, bool, int, float>>);

  static_assert(std::is_same_v<TypeList<bool, int, float>,
                               AppendTypeUnique<int, bool, int, float>>);

  static_assert(std::is_same_v<TypeList<int, bool, double, float>,
                               UniqueTypeList<int, bool, bool, double, int,
                                              float, float, double, bool>>);

  return 0;
}
