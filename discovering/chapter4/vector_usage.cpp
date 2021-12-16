#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
    std::vector<int> v = {3, 4, 7, 9};
    auto it = std::find(v.begin(), v.end(), 4);
    std::cout << "After " << *it << " comes " << *(it + 1) << '\n';
    auto it2 = v.insert(it + 1, 5);
    v.erase(v.begin());
    std::cout << "Size = " << v.size() << ", capacity = " << v.capacity()
              << '\n';
    v.shrink_to_fit(); // drop extra entries
    std::cout << "Size = " << v.size() << ", capacity = " << v.capacity()
              << '\n';
    v.push_back(7);
    for (const auto &i : v) {
        std::cout << i << ", ";
    }
    std::cout << '\n';
    std::cout << "Size = " << v.size() << ", capacity = " << v.capacity()
              << '\n';
    return 0;
}