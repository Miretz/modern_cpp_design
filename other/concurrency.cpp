#include <chrono>
#include <cstdio>
#include <thread>
#include <utility>
#include <vector>

void fun(int &nRef, int id, int sleepTime) {
    printf("Thread started id: %d, value: %d\n", id, nRef);

    for (int i = 0; i < 10; i++) {
        ++nRef;
        printf("Thread updated id: %d, value: %d\n", id, nRef);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
    printf("Thread finished id: %d, value: %d\n", id, nRef);
}

auto main() -> int {
    printf("%d concurrent threads are supported.\n",
           std::thread::hardware_concurrency());

    int num = 0;
    std::thread t1(fun, std::ref(num), 0, 10);
    std::thread t2(fun, std::ref(num), 1, 20);

    t1.join();
    t2.join();

    printf("Num value: %d\n", num);

    return 0;
}
