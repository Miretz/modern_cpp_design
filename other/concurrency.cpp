#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

void fun(int &nRef, int id, int sleepTime) {
  std::cout << "Thread started id: " << id << " ,value: " << nRef << "\n";

  for (int i = 0; i < 10; i++) {
    ++nRef;
    std::cout << "Thread updated id: " << id << " ,value: " << nRef << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  }
  std::cout << "Thread finished id: " << id << " ,value: " << nRef << "\n";
}

int main() {
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

  int num = 0;
  std::thread t1(fun, std::ref(num), 0, 10);
  std::thread t2(fun, std::ref(num), 1, 20);

  t1.join();
  t2.join();

  std::cout << "Num value: " << num << "\n";

  return 0;
}
