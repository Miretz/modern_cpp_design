#include <cmath>
#include <iostream>
#include <limits>
#include <string>

// my ultra-complicated stupid solution
static constexpr auto interval_check(int a, int b, int c, int d)
    -> std::pair<int, int> {

    // input intervals must be ordered
    if (a >= b || c >= d) {
        return {-1, -1};
    }

    // no overlap
    if (a > d) {
        return {0, 0};
    }

    if (b > c) {
        if (d < b) {
            return {c, d};
        } else {
            if (a > c) {
                return {a, b};
            } else {
                return {c, b};
            }
        }
    }

    if (a > c && a < d) {
        if (b < d) {
            return {a, b};
        } else {
            return {d, a};
        }
    } else {
        return {0, 0};
    }
}

// how smart people solve it
static constexpr auto interval_check2(int a, int b, int c, int d)
    -> std::pair<int, int> {

    // input intervals must be ordered
    if (a >= b || c >= d) {
        return {-1, -1};
    }

    if (b < c || d < a) {
        return {0, 0};
    }

    std::pair<int, int> result{std::max(a, c), std::min(b, d)};
    if (result.first == result.second) {
        return {0, 0};
    }
    return result;
}

static constexpr auto compare(std::pair<int, int> r, std::pair<int, int> l)
    -> bool {
    return r == l;
}

auto main() -> int {

    static_assert(compare(interval_check(1, 2, 3, 4), {0, 0}));
    static_assert(compare(interval_check(1, 5, 2, 7), {2, 5}));
    static_assert(compare(interval_check(1, 1, 2, 2), {-1, -1}));
    static_assert(compare(interval_check(1, 9, 2, 8), {2, 8}));
    static_assert(compare(interval_check(1, 7, 2, 5), {2, 5}));
    static_assert(compare(interval_check(1, 3, 1, 3), {1, 3}));
    static_assert(compare(interval_check(1, 5, 1, 3), {1, 3}));
    static_assert(compare(interval_check(8, 9, 1, 2), {0, 0}));
    static_assert(compare(interval_check(1, 2, 8, 9), {0, 0}));
    static_assert(compare(interval_check(1, 9, 2, 3), {2, 3}));
    static_assert(compare(interval_check(2, 3, 1, 9), {2, 3}));
    static_assert(compare(interval_check(1, 2, 2, 3), {0, 0}));
    static_assert(compare(interval_check(1, 3, 6, 7), {0, 0}));
    static_assert(compare(interval_check(5, 7, 6, 7), {6, 7}));
    static_assert(compare(interval_check(3, 6, 4, 5), {4, 5}));
    static_assert(compare(interval_check(1, 4, 2, 7), {2, 4}));
    static_assert(compare(interval_check(10, 14, 12, 13), {12, 13}));

    static_assert(compare(interval_check2(1, 2, 3, 4), {0, 0}));
    static_assert(compare(interval_check2(1, 5, 2, 7), {2, 5}));
    static_assert(compare(interval_check2(1, 1, 2, 2), {-1, -1}));
    static_assert(compare(interval_check2(1, 9, 2, 8), {2, 8}));
    static_assert(compare(interval_check2(1, 7, 2, 5), {2, 5}));
    static_assert(compare(interval_check2(1, 3, 1, 3), {1, 3}));
    static_assert(compare(interval_check2(1, 5, 1, 3), {1, 3}));
    static_assert(compare(interval_check2(8, 9, 1, 2), {0, 0}));
    static_assert(compare(interval_check2(1, 2, 8, 9), {0, 0}));
    static_assert(compare(interval_check2(1, 9, 2, 3), {2, 3}));
    static_assert(compare(interval_check2(2, 3, 1, 9), {2, 3}));
    static_assert(compare(interval_check2(1, 2, 2, 3), {0, 0}));
    static_assert(compare(interval_check2(1, 3, 6, 7), {0, 0}));
    static_assert(compare(interval_check2(5, 7, 6, 7), {6, 7}));
    static_assert(compare(interval_check2(3, 6, 4, 5), {4, 5}));
    static_assert(compare(interval_check2(1, 4, 2, 7), {2, 4}));
    static_assert(compare(interval_check2(10, 14, 12, 13), {12, 13}));

    return 0;
}
