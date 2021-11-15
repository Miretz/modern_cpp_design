#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// This is a very unoptimal solution

using std::cin;
using std::cout;

struct Params {
  std::pair<int, int> room;
  std::pair<int, int> tile;
  auto print() -> void {
    cout << "room"
         << " (x: " << room.first << ", y:" << room.second
         << ", sq: " << (room.first * room.second) << ")\n"
         << "tile"
         << " (x: " << tile.first << ", y:" << tile.second
         << ", sq: " << (tile.first * tile.second) << ")\n"
         << "Rough estimate: "
         << std::ceil((room.first * room.second) / (tile.first * tile.second))
         << '\n';
  }
};

auto get_parameters() -> Params {

  Params params;

  cout << "Enter room size x (cm): ";
  cin >> params.room.first;

  cout << "Enter room size y (cm): ";
  cin >> params.room.second;

  cout << "Enter tile size x (cm): ";
  cin >> params.tile.first;

  cout << "Enter tile size y (cm): ";
  cin >> params.tile.second;

  return params;
}

auto print_tile(int width) -> void {
  if (width == 0)
    return;
  cout << "[." << std::left << std::setw(4) << width << ']';
}

auto print_line() -> void { cout << std::string(30, '-') << '\n'; }

auto main() -> int {

  auto params = get_parameters();

  print_line();
  params.print();
  print_line();

  int count_of_tiles = 0;
  int left_over = 0;
  int rows =
      std::ceil(static_cast<float>(params.room.second) / params.tile.second);

  for (int r = 1; r < rows + 1; r++) {

    int count_of_tiles_row = std::floor(params.room.first / params.tile.first);
    int left_over_row =
        params.room.first - (count_of_tiles_row * params.tile.first);

    for (int i = 0; i < count_of_tiles_row; i++) {
      print_tile(params.tile.first);
    }
    print_tile(left_over_row);

    count_of_tiles += count_of_tiles_row;
    left_over += left_over_row;

    cout << "\t\tRow: " << std::left << std::setw(4) << r
         << " Tiles in row: " << std::left << std::setw(4) << count_of_tiles_row
         << " Tiles total: " << std::left << std::setw(4) << count_of_tiles
         << " Left over in row: " << std::left << std::setw(4) << left_over_row
         << " Left over total: " << std::left << std::setw(4) << left_over;
    cout << "\n";
  }

  print_line();
  cout << "Number of full tiles needed: " << count_of_tiles << "\n";

  while (left_over > 0) {
    count_of_tiles++;
    left_over -= params.tile.first;
  }

  cout << "Number of all tiles (full & cut) needed: " << count_of_tiles << '\n';
  cout << "After placing them " << std::abs(left_over) << " cm remains.\n";

  return 0;
}
