#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

// Reference wrapper solves the problem of creating a container of references

auto main() -> int {
    // vector of references to vectors of ints
    std::vector<std::reference_wrapper<std::vector<int>>> vv;

    std::vector<int> v1 = {2, 3, 4};
    std::vector<int> v2 = {5, 6};
    std::vector<int> v3 = {7, 8};

    vv.push_back(v1);
    vv.push_back(v2);
    vv.push_back(v3);
    vv.push_back(v2);
    vv.push_back(v1);

    for (const std::vector<int> &vr : vv) {
        std::copy(begin(vr), end(vr),
                  std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }

    // std::map<int, std::reference_wrapper<std::vector<int>>> mv;
    // the above can also be written like:
    std::map<int, decltype(ref(v1))> mv;

    // brackets don't work here e.g. mv[4] will cause Error
    // use emplace and insert
    mv.emplace(std::make_pair(4, ref(v1)));
    mv.emplace(std::make_pair(7, ref(v2)));
    mv.emplace(std::make_pair(8, ref(v3)));
    mv.emplace(std::make_pair(9, ref(v2)));

    std::cout << "Map Example:\n";
    for (const auto &vr : mv) {
        std::cout << vr.first << ": ";
        for (int i : vr.second.get()) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }

    // instead of brackets use find()
    const auto &v7 = mv.find(7)->second.get();
    std::cout << "value (7,0) is " << v7[0] << std::endl;

    return 0;
}