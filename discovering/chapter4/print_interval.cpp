#include <algorithm>
#include <iostream>
#include <list>
#include <ostream>
#include <sstream>

template <typename T> struct value_not_found {
    bool isFirst;
    T value;
};

template <typename Range, typename Value>
void print_interval(const Range &r, const Value &v,
                    std::ostream &os = std::cout) {
    using std::begin;
    using std::end;
    auto it = std::find(begin(r), end(r), v), it2 = it;
    if (it == end(r)) {
        throw value_not_found<Value>{true, v};
    }
    ++it2;
    auto past = std::find(it2, end(r), v);
    if (past == end(r)) {
        throw value_not_found<Value>{false, v};
    }
    ++past;
    for (; it != past; ++it) {
        os << *it << ' ';
    }
    os << '\n';
}

auto main() -> int {

    try {

        std::list<int> seq = {3, 4, 7, 9, 2, 5, 7, 8};
        print_interval(seq, 7);

        int array[] = {3, 4, 7, 9, 2, 5, 7, 8};
        std::stringstream ss;
        print_interval(array, 7, ss);
        std::cout << ss.str();

        std::list<int> seq2 = {3, 4, 7, 9, 2, 5, 11, 8};
        print_interval(seq2, 7);

    } catch (value_not_found<int> &ex) {
        const auto whichValue = ex.isFirst ? "First" : "Second";
        std::cout << "Error:  " << whichValue << " interval value not found ("
                  << ex.value << ")\n";
    }
    return 0;
}