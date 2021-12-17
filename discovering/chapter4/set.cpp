#include <iostream>
#include <set>

using std::multiset;
using std::set;

auto main() -> int {

    std::cout << "Set\n";

    set<int> s = {1, 3, 4, 7, 9};
    s.insert(5);
    for (int i = 0; i < 6; ++i) {
        std::cout << i << " appears " << s.count(i) << " times.\n";
    }

    std::cout << "Multiset\n";

    // multiset counts how often a value was inserted
    multiset<int> ms = {1, 3, 4, 7, 9, 1, 1, 4};
    ms.insert(4);
    for (int i = 0; i < 6; ++i) {
        std::cout << i << " appears " << ms.count(i) << " times.\n";
    }

    return 0;
}