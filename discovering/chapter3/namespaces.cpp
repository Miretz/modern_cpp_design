#include <iostream>

struct same {};
namespace c1 {
struct same {};
namespace c2 {
struct same {};
struct cc {};
namespace c1 {
struct csame {
  ::same x;
  same z;
};
} // namespace c1
} // namespace c2
} // namespace c1

void fun() {
  using c1::c2::cc;
  cc x;
  cc y;
}

void fun2() {
  using namespace c1::c2;
  cc x;
  cc y;
}

void namespace_alias() {
  namespace ccs = c1::c2;
  using namespace ccs;
  cc x;
  cc y;
}

auto main() -> int {
  fun();
  fun2();
  namespace_alias();
  return 0;
}