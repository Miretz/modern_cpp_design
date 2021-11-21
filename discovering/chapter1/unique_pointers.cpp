#include <iostream>
#include <memory>

std::unique_ptr<double> f() { return std::unique_ptr<double>{new double}; }

auto main() -> int {
  std::unique_ptr<double> dp{new double};
  *dp = 7;
  auto *dpp = dp.get();
  std::cout << *dpp << std::endl;

  // can only be moved
  auto dp2 = std::move(dp);
  std::cout << *dp2 << std::endl;
  std::cout << *dpp << std::endl;
  // std::cout << *dp << std::endl; //error, dp has moved to dp2

  // moved back to dp, now dp2 is nullptr
  dp = std::move(dp2);
  std::cout << *dp << std::endl;

  // pointed is automatically moved from function return
  auto dp3 = f();
  std::cout << *dp3 << std::endl;

  // unique ptr has special implementation for arrays to use delete[]
  std::unique_ptr<double[]> da{new double[3]};
  for (unsigned i = 0; i < 3; ++i)
    da[i] = i + 2;

  for (unsigned i = 0; i < 3; ++i) {
    std::cout << da[i] << ((i == 2) ? "\n" : ", ");
  }

  return 0;
}
