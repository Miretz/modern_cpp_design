#include <iostream>
#include <memory>

std::shared_ptr<double> f() {
  std::shared_ptr<double> p1{new double};
  std::shared_ptr<double> p2{new double}, p3 = p2;
  std::cout << "p3.use_count() = " << p3.use_count() << std::endl;
  return p3;
}

auto main() -> int {
  std::shared_ptr<double> p = f();
  std::cout << "p.use_count() = " << p.use_count() << std::endl;

  // shared_ptr should be created by make_shared if possible
  // the memory caching is more efficient
  auto ps = std::make_shared<double>();
  std::cout << "ps.use_count() = " << ps.use_count() << std::endl;

  return 0;
}
