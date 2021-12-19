#include <iostream>
#include <vector>
#include <list>

// Implement a custom find operation
template <typename InputIterator, typename T>
auto my_find(InputIterator first, InputIterator last, const T &value)
    -> InputIterator {
    while (first != last && *first != value) {
        ++first;
    }
    return first;
}

auto main() -> int {
    std::vector<int> seq = {3, 4, 7, 9, 2, 5, 7, 8};

    // returns values between 7 and 7
    auto it = my_find(seq.begin(), seq.end(), 7);
    auto end = my_find(it + 1, seq.end(), 7);
    for (auto past = end + 1; it != past; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // the implementation above will not work for list
    // because of random-access iterator it's using

    std::list<int> seq2 = {3, 4, 7, 9, 2, 5, 7, 8};
    auto lit = my_find(seq2.begin(), seq2.end(), 7), lit2 = lit;
    ++lit2;
    auto lend = my_find(lit2, seq2.end(), 7);
    ++lend;
    for(;lit!=lend; ++lit){
        std::cout << *lit << ' ';
    }
    std::cout << '\n';
    

}