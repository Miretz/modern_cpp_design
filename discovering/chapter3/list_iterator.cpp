#include <iostream>

template <typename T> struct list_entry {
    explicit list_entry(const T &value) : value(value), next(0) {}
    T value;
    list_entry<T> *next;
};

template <typename T> struct list_iterator {
    using value_type = T;
    explicit list_iterator(list_entry<T> *entry) : entry(entry) {}
    T &operator*() { return entry->value; }
    const T &operator*() const { return entry->value; }
    list_iterator<T> operator++() {
        entry = entry->next;
        return *this;
    }
    bool operator!=(const list_iterator<T> &other) const {
        return entry != other.entry;
    }
    list_entry<T> *entry;
};

template <typename T> struct list {
    list() : first(0), last(nullptr) {}
    ~list() {
        while (first) {
            list_entry<T> *tmp = first->next;
            delete first;
            first = tmp;
        }
    }
    void append(const T &x) {
        last = (first ? last->next : first) = new list_entry<T>(x);
    }

    // for iterator
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }

    list_entry<T> *first, *last;
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
    // now accumulate works for both lists and arrays
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "array sum = " << accumulate(a, a + 10, 0) << '\n';

    list<float> l;
    l.append(2.0f);
    l.append(4.0f);
    l.append(7.0f);
    std::cout << "array sum = " << accumulate(l.begin(), l.end(), 0) << '\n';

    for(auto i : l){
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}