#include <iostream>
#include <tuple>
#include <vector>
#include <iterator>

auto get_even_and_sum(const std::vector<int> &A)
    -> std::tuple<std::vector<int>, int> {
    std::vector<int> even;
    int sum = 0;
    for (const auto &v : A) {
        if (v % 2 == 0) {
            even.push_back(v);
        }
        sum += v;
    }
    // to avoid copies we could move
    return std::make_tuple(std::move(even), sum);
}

auto main() -> int {
    std::vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto result = get_even_and_sum(A);

    // tuple values can be accessed using get
    // get works by taking the index or type
    auto even = std::get<std::vector<int>>(result);
    auto sum = std::get<int>(result);

    // this can also be done via tie()
    std::tie(even, sum) = result;

    // or structured binding since C++17
    const auto &[a, b] = result;

    std::cout << "The sum is: " << sum << '\n';
    std::cout << "The sum is: " << b << '\n';

    std::copy(even.begin(), even.end(),
              std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    return 0;
}