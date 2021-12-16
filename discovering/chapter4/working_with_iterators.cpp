#include <iostream>
#include <list>

auto main() -> int {
    std::list<int> l = {3, 5, 9, 7};

    for (auto it = cbegin(l), e = cend(l); it != e; ++it) {
        int i = *it;
        std::cout << i << std::endl;
    }

    for (const auto& i : l) {
        std::cout << i << std::endl;
    }

    return 0;
}