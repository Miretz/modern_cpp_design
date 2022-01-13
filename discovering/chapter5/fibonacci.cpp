#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <span>

// constexpr function
// - should be a single return statement
// - cannot read and write outside, no side effects!
// - can only call functions which are constexpr as well
constexpr auto fibonacci(int32_t n) -> int32_t {
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

auto main(int argc, char *argv[]) -> int {
    if (argc != 2) {
        std::cout << "Please provide a single numeric argument.\n";
        return EXIT_FAILURE;
    }

    // C++20 use Span
    // auto args = std::span(argv, size_t(argc));
    // const int32_t n = atoi(args[1]);

    const int32_t n = atoi(argv[1]); // NOLINT

    // the function cannot be evaluated on compile-time as the argument
    // is not known
    std::cout << "fibonacci(" << n << ") = " << fibonacci(n) << '\n';
    return EXIT_SUCCESS;
}
