#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

auto main() -> int {

    // vector resize and copy values
    {
        std::vector<int> seq = {3, 4, 7, 9, 2, 5, 7, 8}, v;
        v.resize(seq.size());
        std::copy(seq.begin(), seq.end(), v.begin());

        // print values by means of std::copy
        std::copy(seq.begin(), seq.end(),
                  std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }

    // remove duplicates (using std::unique)
    {
        std::vector<int> seq = {3, 4, 7, 9, 2, 5, 7, 8, 3, 4, 3, 9};
        std::sort(seq.begin(), seq.end());
        auto it = std::unique(seq.begin(), seq.end());
        seq.resize(std::distance(seq.begin(), it));

        std::copy(seq.begin(), seq.end(),
                  std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }

    return 0;
}