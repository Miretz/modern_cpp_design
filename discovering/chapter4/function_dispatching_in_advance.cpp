#include <iostream>
#include <iterator>
#include <list>


template <typename Iterator, typename Distance>
inline void advance_aux(Iterator &i, Distance n, std::input_iterator_tag) {
    assert(n >= 0);
    for (; n > 0; --n) {
        ++i;
    }
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator &i, Distance n,
                        std::bidirectional_iterator_tag) {
    if (n >= 0) {
        for (; n > 0; --n) {
            ++i;
        }
    } else {
        for (; n < 0; ++n) {
            --i;
        }
    }
}

template <typename Iterator, typename Distance>
inline void advance_aux(Iterator &i, Distance n,
                        std::random_access_iterator_tag) {
    i += n;
}

template <typename Iterator, typename Distance, typename IteratorCategory>
inline void advance(Iterator &i, Distance n) {
    advance_aux<Iterator, Distance, IteratorCategory>(i, n);
}

auto main() -> int {
    std::list<int> l = {3, 7, 9, 11};
    auto it = l.end();

    advance(it, -2);
    std::cout << *it << '\n'; // 9

    advance(it, -2);
    std::cout << *it << '\n'; // 3

    advance(it, 1);
    std::cout << *it << '\n'; // 7

    return 0;
}