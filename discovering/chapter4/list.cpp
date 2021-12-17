#include <iostream>
#include <list>
#include <algorithm>

using std::list;

auto main() -> int {
    list<int> l = {3, 4, 7, 9};
    auto it = std::find(begin(l), end(l), 4);
    auto it2 = std::find(begin(l), end(l), 7);
    l.erase(it); // doubly linked list so erasing does not move elements
    std::cout << "it2 still points to " << *it2 << '\n';
}