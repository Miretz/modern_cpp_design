#include <deque>
#include <iostream>
#include <string>

struct parameters {
    std::string name;
};

struct mat {
    std::string name;
};

struct solver {
    solver(const mat &ref, const parameters &para) : ref(ref), para(para) {}
    solver(const solver &) = delete;
    solver(const solver &&) = delete;
    auto operator=(const solver &) -> solver & = delete;
    auto operator=(const solver &&) -> solver & = delete;
    ~solver() = default;
    const mat &ref;
    const parameters &para;
    friend auto operator<<(std::ostream &stream, const solver &c) -> std::ostream & {
        stream << '(' << c.ref.name << ", " << c.para.name << ')';
        return stream;
    }
};

using std::deque;

auto solve_x(solver &s) { std::cout << "Running solver: " << s << '\n'; }

auto main() -> int {
    parameters p1{"p1"}, p2{"p2"}, p3{"p3"};
    mat A{"A"}, B{"B"}, C{"C"};
    deque<solver> solvers;
    solvers.emplace_back(B, p3);
    solvers.emplace_back(C, p2);
    solvers.emplace_back(A, p1);
    for (auto &s : solvers) {
        solve_x(s);
    }
}
