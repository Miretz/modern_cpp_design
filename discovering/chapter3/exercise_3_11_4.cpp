#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

template <typename T> struct list_entry {
    explicit list_entry(const T &value) : value(value), next(0) {}
    T value;
    list_entry<T> *next;
    list_entry<T> *previous;
};

template <typename T> bool are_neighbors(list_entry<T> *A, list_entry<T> *B) {
    return (A->next == B && B->previous == A) ||
           (A->previous == B && B->next == A);
}

template <typename T> void refresh_outer(list_entry<T> *A) {
    if (A->previous != nullptr) {
        A->previous->next = A;
    }
    if (A->next != nullptr) {
        A->next->previous = A;
    }
}

template <typename T> void swap(list_entry<T> *A, list_entry<T> *B) {
    list_entry<T> *swapperVector[4];
    list_entry<T> *temp;

    std::cout << "Swapping: " << A->value << " and " << B->value << std::endl;

    if (A == B)
        return;

    if (B->next == A) {
        temp = A;
        A = B;
        B = temp;
    }

    swapperVector[0] = A->previous;
    swapperVector[1] = B->previous;
    swapperVector[2] = A->next;
    swapperVector[3] = B->next;

    if (are_neighbors(A, B)) {
        A->previous = swapperVector[2];
        B->previous = swapperVector[0];
        A->next = swapperVector[3];
        B->next = swapperVector[1];
    } else {
        A->previous = swapperVector[1];
        B->previous = swapperVector[0];
        A->next = swapperVector[3];
        B->next = swapperVector[2];
    }

    refresh_outer(A);
    refresh_outer(B);
}

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
            current = first;
        }
    }

    // for iterator
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(last); }

    list_entry<T> *first, *current, *last;
};

auto main() -> int {

    // now accumulate works for both lists and arrays

    list<float> l;
    l.append(2.0f);
    l.append(7.0f);
    l.append(4.0f);
    l.append(1.0f);
    l.append(22.0f);
    l.append(18.0f);
    l.append(13.0f);
    l.append(199.0f);

    for (auto i : l) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

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