#include <iostream>

struct list_entry {
    explicit list_entry(const int value) : value(value), next(0) {}
    int value;
    list_entry *next;
};

struct odd_iterator {
    using value_type = int;
    explicit odd_iterator(list_entry *entry) : entry(entry) {}
    auto operator*() -> value_type & {
        if (entry->value % 2 == 0) {
            (*this)++;
        }
        return entry->value;
    }
    auto operator++() -> odd_iterator {
        entry = entry->next;
        while (entry->value % 2 == 0) {
            entry = entry->next;
        }
        return *this;
    }
    auto operator++(int) -> odd_iterator {
        entry = entry->next;
        while (entry->value % 2 == 0) {
            entry = entry->next;
        }
        return *this;
    }
    auto operator!=(const odd_iterator &other) const -> bool {
        return entry != other.entry;
    }
    list_entry *entry;
};

struct integer_list {
    integer_list() = default;
    ~integer_list() {
        while (first) {
            list_entry *tmp = first->next;
            delete first;
            first = tmp;
        }
    }
    integer_list(const integer_list &) = default;
    auto operator=(const integer_list &) -> integer_list & = default;
    integer_list(const integer_list &&) = delete;
    auto operator=(const integer_list &&) -> integer_list & = delete;
    void append(const int x) {
        last = (first ? last->next : first) = new list_entry(x);
    }
    auto begin() -> odd_iterator { return odd_iterator(first); }
    auto end() -> odd_iterator { return odd_iterator(last); }
    list_entry *first = 0, *last = nullptr;
};

// generic summation
template <typename Iter, typename T>
inline T accumulate(Iter it, Iter end, T init) {
    for (; it != end; ++it) {
        init += *it;
    }
    return init;
}

auto main() -> int {

    integer_list l;
    l.append(2);
    l.append(4);
    l.append(7);
    l.append(3);
    l.append(9);
    l.append(1);
    l.append(10);
    l.append(20);
    l.append(12);
    l.append(14);
    l.append(5);

    std::cout << "Begin: " << *(l.begin()) << std::endl;
    std::cout << "End: " << *(l.end()) << std::endl;

    std::cout << "odd array sum = " << accumulate(l.begin(), l.end(), 0)
              << '\n';

    for (auto i : l) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}