#include <iostream>

template <typename T> inline T sum(T t) { return t; }

template <typename T, typename... P> inline T sum(T t, P... p) {
    return t + sum(p...);
}

// variadic counting of parameters
template <typename... P> void count(P... p) {
    std::cout << "You have " << sizeof...(P) << " parameters.\n";
}

auto main() -> int {
    auto s = sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s is " << s << " and it's type is " << typeid(s).name()
              << '\n'; // the result is incorrect due to all numbers being
                       // converted to int

    count(1, 4, 3.2, "test");

    return 0;
}