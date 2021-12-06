#include <iostream>
#include <sstream>

template <typename T> std::string to_string(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <typename T> inline std::string to_tuple_string_aux(T t) {
    return to_string(t);
}

template <typename T, typename... P>
inline std::string to_tuple_string_aux(T t, P... p) {
    return to_string(t) + ", " + to_tuple_string_aux(p...);
}

template <typename... T> std::string to_tuple_string(const T... t) {
    std::stringstream ss;
    ss << '(';
    ss << to_tuple_string_aux(t...);
    ss << ')';
    return ss.str();
}

auto main() -> int {

    std::cout << to_string(42) << ' ' << to_string(97.1) << ' '
              << to_string("test") << '\n';

    std::cout << "to tupple string: " << to_tuple_string(7, 2, "af", 3.2, 0.2f)
              << '\n';

    return 0;
}