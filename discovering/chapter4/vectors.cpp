#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
    std::vector<int> v = {3, 4, 7, 9};
    for (int i = 0; i < v.size(); ++i) {
        v[i] *= 2;
    }
    for (auto &x : v) {
        x *= 2;
    }

    std::for_each(cbegin(v), cend(v),
                  [](const auto &x) { std::cout << x << std::endl; });

    return 0;
}