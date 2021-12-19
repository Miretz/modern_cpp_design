#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::map;
using std::multimap;
using std::string;

auto main() -> int {

    map<string, double> constants = {{"e", 2.7}, {"pi", 3.14}, {"h", 6.6e-34}};

    cout << "The Planck constant is " << constants["h"] << '\n';
    constants["c"] = 299892458;

    // NOTE: missing entries will be created!
    cout << "The Coulomb constant is " << constants["k"] << '\n';

    cout << "The value of Pi is " << constants.find("pi")->second << '\n';

    auto it_phi = constants.find("phi");
    if (it_phi != constants.end()) {
        cout << "Golden ratio is " << it_phi->second << '\n';
    }
    cout << "The Euler constant is " << constants.at("e") << "\n\n";

    for (const auto &c : constants) {
        cout << "The value of " << c.first << " is " << c.second << '\n';
    }
    cout << '\n';

    // Multimap is a map where one key can be associated with multiple values
    multimap<int, double> mm = {
        {3, 1.3}, {2, 4.1}, {3, 1.8}, {4, 9.2}, {3, 1.5}};

    for (auto it = mm.lower_bound(3), end = mm.upper_bound(3); it != end;
         ++it) {
        cout << "The value is " << it->second << '\n';
    }

    return 0;
}