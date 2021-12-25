#include <functional>
#include <iostream>
#include <random>

using std::cout;

void random_numbers() {
    static std::random_device rd;
    static std::default_random_engine re(rd());
    std::normal_distribution<> normal;
    cout << "Random numbers: ";
    for (int i = 0; i < 4; i++) {
        cout << normal(re) << (i < 3 ? ", " : "");
    }
    cout << "\n";
}

void bind_example() {
    // we can bind the distribution to the engine using std::bind (from
    // <functional>)
    auto normal = std::bind(std::normal_distribution<>{},
                            std::default_random_engine(std::random_device{}()));

    cout << "Callong bound normal(): ";
    for (int i = 0; i < 4; i++) {
        cout << normal() << (i < 3 ? ", " : "");
    }
    cout << "\n";

    // or just use a lambda with init capture
    auto normal2 = [re = std::default_random_engine(std::random_device{}()),
                    n = std::normal_distribution<>{}]() mutable {
        return n(re);
    };

    cout << "Callong lambda normal2(): ";
    for (int i = 0; i < 4; i++) {
        cout << normal2() << (i < 3 ? ", " : "");
    }
    cout << "\n";
}

auto main() -> int {
    random_numbers();
    random_numbers();
    bind_example();
    bind_example();
    return 0;
}