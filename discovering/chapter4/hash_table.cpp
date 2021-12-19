#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::string;
using std::unordered_map;

auto main() -> int {

    unordered_map<string, double> constants = {
        {"e", 2.7}, {"pi", 3.14}, {"h", 6.6e-34}};

    cout << "The Planck constant is " << constants["h"] << '\n';

    constants["c"] = 299792458;

    cout << "The Euler constant is " << constants.at("e") << "\n\n";

    return 0;
}