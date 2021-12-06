#include <algorithm>
#include <iostream>
#include <vector>

template <typename C> void reverse_sort(C &c) {
    sort(begin(c), end(c), [](auto x, auto y) { return x > y; });
}

auto main() -> int {
    std::vector<int> v{7, 9, 5, 2, 1};
    reverse_sort(v);

    std::for_each(begin(v), end(v),
                  [](const auto &v) { std::cout << v << ' '; });
    std::cout << '\n';

    return 0;
}