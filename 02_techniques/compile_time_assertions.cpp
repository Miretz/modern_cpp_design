#include <iostream>

template <bool> struct CompileTimeChecker { explicit CompileTimeChecker(...); };

template <> struct CompileTimeChecker<false> {};

template <class To, class From> auto safe_reinterpret_cast(From from) -> To {
    static_assert(sizeof(From) <= sizeof(To), "Destination_Type_Too_Narrow");
    return reinterpret_cast<To>(from); // NOLINT
}

auto main() -> int {

    // no error
    char st[] = "some text\0";                   // NOLINT
    void *c = safe_reinterpret_cast<void *>(st); // NOLINT
    char *cs = safe_reinterpret_cast<char *>(c); // NOLINT
    std::cout << cs << '\n';

    // uncomment these to see the compile time error
    // char fake = safe_reinterpret_cast<char>(cs);
    // std::cout << fake << '\n';

    return 0;
}
