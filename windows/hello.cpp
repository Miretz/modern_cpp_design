#include <windows.h>

// on MinGW: g++ -mwindows hello.cpp

auto main() -> int
{
  const auto& title = "Hello, World!";
  const auto& text  = "Click the OK button to quit.";
  MessageBox(0, text, title, MB_SETFOREGROUND);
  return 0;
}
