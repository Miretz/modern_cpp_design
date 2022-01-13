#include <iostream>

template <typename... P> struct sum_type;

template <typename T> struct sum_type<T> { using type = T; };

template <typename T, typename... P> struct sum_type<T, P...> {
    using type = decltype(T() + typename sum_type<P...>::type());
};

template <typename... P> using sum_type_t = typename sum_type<P...>::type;

template <typename T> inline auto sum(T t) -> T { return t; }

template <typename T, typename... P>
inline auto sum(T t, P... p) -> sum_type_t<T, P...> {
    return t + sum(p...);
}

auto main() -> int {
    auto s = sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s is " << s << " and its type is " << typeid(s).name()
              << '\n';

    auto s2 = sum(-7, 3.7f, 9u, -42.6);
    std::cout << "s2 is " << s2 << " and its type is " << typeid(s2).name()
              << '\n';

    return 0;
}
