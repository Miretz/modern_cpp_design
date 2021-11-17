#include <iostream>

using std::cout;

template <typename T> void reverse(T *str, int n) {
  T *end = str + n - 1;
  T *p = str;
  while (p < end) {
    T tmp = *p;
    *p = *end;
    *end = tmp;
    p++;
    end--;
  }
}

auto main() -> int {

  char ascii_buffer[] = "hello world\0";
  reverse<char>(ascii_buffer, 11);
  cout << ascii_buffer << '\n';

  int numbers[] = {5, 4, 3, 2, 1};
  reverse<int>(numbers, 5);
  for (auto n : numbers) {
    cout << n;
  }
  cout << '\n';

  char utf_buffer[] = "čauko, svet";
  reverse<char>(utf_buffer, 12);
  reverse<char>(&utf_buffer[10], 2);
  cout << utf_buffer << std::endl;

  return 0;
}
