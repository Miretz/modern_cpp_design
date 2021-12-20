#include <iostream>
#include <random>

auto global_urng() -> std::default_random_engine & {
    static std::default_random_engine u{};
    return u;
}

void randomize() {
    static std::random_device rd{};
    global_urng().seed(rd());
}

auto pick(int from, int thru) -> int {
    static std::uniform_int_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(global_urng(), parm_t{from, thru});
}

auto pick(double from, double upto) -> double {
    static std::uniform_real_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(global_urng(), parm_t{from, upto});
}

auto main() -> int {
    randomize();
    std::cout << "Dice roll result: " << pick(1, 6) << '\n';
    return 0;
}
