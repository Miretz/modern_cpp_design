#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T> struct list_entry {
    explicit list_entry(const T &value)
        : value(value), next(nullptr), previous(nullptr) {}
    T value = 0;
    list_entry<T> *next = nullptr;
    list_entry<T> *previous = nullptr;
};

template <typename T> class list_iterator {
  public:
    explicit list_iterator(list_entry<T> *entry) : entry(entry) {}

    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    T &operator*() { return entry->value; }
    const T &operator*() const { return entry->value; }

    list_iterator<T> &operator++() {
        entry = entry->next;
        return *this;
    }
    list_iterator<T> operator++(int) {
        entry = entry->next;
        return *this;
    }
    list_iterator<T> &operator--() {
        entry = entry->previous;
        return *this;
    }
    list_iterator<T> operator--(int) {
        entry = entry->previous;
        return *this;
    }

    list_iterator<T> &operator+(difference_type v) {
        while (v > 0) {
            entry = entry->next;
            v--;
        }
        return *this;
    }
    list_iterator<T> &operator-(difference_type v) {
        while (v > 0) {
            entry = entry->previous;
            v--;
        }
        return *this;
    }
    difference_type operator-(const list_iterator<T> &other) {
        std::ptrdiff_t ret = 0;
        auto temp = entry;
        while (temp != other.entry) {
            temp = temp->previous;
            ++ret;
        }
        return ret;
    }

    bool operator!=(const list_iterator<T> &other) const {
        return entry != other.entry;
    }
    bool operator==(const list_iterator<T> &other) const {
        return entry == other.entry;
    }
    bool operator<(const list_iterator<T> &other) const {
        return entry->value < other.entry->value;
    }
    bool operator>(const list_iterator<T> &other) const {
        return entry->value > other.entry->value;
    }

  private:
    list_entry<T> *entry;
};

template <typename T> struct list {
    list() : first(nullptr), current(nullptr), last(new list_entry<T>(0)) {}
    ~list() {
        while (first) {
            list_entry<T> *tmp = first->next;
            delete first;
            first = tmp;
        }
        if (last) {
            delete last;
            last = nullptr;
        }
    }
    void append(const T &x) {
        if (first) {
            current->next = new list_entry<T>(x);
            current->next->previous = current;
            current->next->next = last;
            current = current->next;
            last->previous = current;
        } else {
            first = new list_entry<T>(x);
            first->next = last;
            first->previous = first;
            current = first;
        }
    }

    // for iterator
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(last); }

    list_entry<T> *first, *current, *last;
};

auto main() -> int {

    list<float> l;
    l.append(2.0f);
    l.append(7.0f);
    l.append(4.0f);
    l.append(1.0f);
    l.append(22.0f);
    l.append(199.0f);
    l.append(18.0f);
    l.append(13.0f);
    l.append(99.0f);
    l.append(51.0f);

    for (auto i : l) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // not sure why the first 3 entries are wrong and then it just works
    std::sort(l.begin(), l.end());

    // for each test
    std::for_each(l.begin(), l.end(),
                  [](const auto &v) { std::cout << v << ' '; });
    std::cout << std::endl;

    // backwards
    auto it = l.end();
    for (; it != l.begin(); --it) {
        if (it != l.end()) {
            std::cout << *it << ' ';
        }
    }
    std::cout << *it << ' ';
    std::cout << std::endl;

    return 0;
}