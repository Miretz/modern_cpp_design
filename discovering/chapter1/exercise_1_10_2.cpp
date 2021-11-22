#include <iostream>

auto main() -> int {

  // Part 1

  char k = 'p';
  char *p_k = &k;

  int ten_integers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *p_ten_integers = &ten_integers[0];

  const char *strings[] = {"one", "two", "three"};

  char **p_p_k = &p_k;

  const int konstant1 = 1;
  constexpr int konstant2 = 2;

  const int *p_konstant1 = &konstant1;
  p_konstant1 = &konstant2;

  const int *const p_konstant2 = &konstant1;
  // p_konstant2 = &konstant1; // Error

  // Part 2

  int array1[100];
  int *array2 = new int[100];

  delete[] array2;

  return 0;
}
