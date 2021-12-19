#include <algorithm>
#include <iostream>
#include <list>

auto check(int i) -> bool { return i > 4 && i < 7; }

auto main() -> int {
    std::list<int> seq = {3, 4, 7, 9, 2, 5, 7, 8};
    auto it = std::find_if(begin(seq), end(seq), check);
    std::cout << "The first value in range is " << *it << '\n';

    // same with lambda as predicate
    auto itl = std::find_if(begin(seq), end(seq),
                            [](int i) { return i > 4 && i < 7; });
    std::cout << "The first value in range is " << *itl << '\n';

    return 0;
}