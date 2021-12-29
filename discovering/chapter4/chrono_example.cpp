#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

using std::chrono::steady_clock;
using std::chrono::system_clock;
using std::chrono::time_point;

inline auto my_root(double x, double eps = 1e-12) -> double {
    double sq = 1.0, sqo = 0.0;
    do {
        sqo = sq;
        sq = 0.5 * (sqo + x / sqo);
    } while (abs(sq - sqo) > eps);
    return sq;
}

auto main() -> int {
    time_point<system_clock> now = system_clock::now();
    auto then = now + std::chrono::hours(2);

    time_t then_time = system_clock::to_time_t(then);

    std::cout << "I will be there at " << ctime(&then_time);
    // ctime also puts in a newline

    std::cout << std::setprecision(4);

    // example of timing a function
    double r3 = 0.0;
    int rep = 1000000;
    time_point<steady_clock> start = steady_clock::now();
    for (int i = 0; i < rep; ++i) {
        r3 = my_root(3.0);
    }
    auto end = steady_clock::now();

    std::cout << "my_root(3.0) = " << r3 << ", the calculation took "
              << ((end - start) / rep).count() << " ticks\n";

    // convert duration to microseconds
    auto durationUs = std::chrono::duration_cast<std::chrono::microseconds>(
                          (end - start) / rep)
                          .count();

    std::cout << "my_root(3.0) = " << r3 << ", the calculation took "
              << durationUs << " microseconds\n";

    // nanoseconds
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(
                          (end - start) / rep)
                          .count() /
                      1000;

    std::cout << "my_root(3.0) = " << r3 << ", the calculation took "
              << durationNs << " nanoseconds\n";

    // clock resolution
    using P = steady_clock::period;
    std::cout << "Resolution is " << double{P::num} / P::den << "s.\n";

    // Summary
    // We have 3 clocks
    // system_clock - native wall clock of the system
    // high_resolution_clock - maximal resolution on the system
    // steady_clock - clock with guaranteed increasing time points
    // (is not adjusted e.g. at midnight so it's good for timers)

    return 0;
}