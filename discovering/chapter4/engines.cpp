#include <iostream>
#include <random>

using std::cout;

void random_numbers() {
    static std::random_device rd;
    static std::default_random_engine re(rd());
    cout << "Random numbers: ";
    for (int i = 0; i < 4; i++) {
        cout << re() << (i < 3 ? ", " : "");
    }
    cout << "\n";
}

auto main() -> int {
    random_numbers();
    random_numbers();
    return 0;
}