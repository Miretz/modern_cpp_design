#include <algorithm>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// Laminate flooring. Calculates the number of planks needed.

using std::cin;
using std::cout;

struct Params {
  std::pair<int, int> room;
  std::pair<int, int> tile;
  auto print() -> void {
    cout << "Room"
         << " (x: " << room.first << ", y:" << room.second
         << ", sq: " << (room.first * room.second) << ")\n"
         << "Default Tile"
         << " (x: " << tile.first << ", y:" << tile.second
         << ", sq: " << (tile.first * tile.second) << ")\n"
         << "Rough estimate: "
         << std::ceil((room.first * room.second) / (tile.first * tile.second))
         << '\n';
  }
};

struct Tile {
  std::pair<int, int> dimensions;

  bool operator==(const Tile &rhs) const {
    return dimensions == rhs.dimensions;
  }

  bool operator<(const Tile &rhs) const { return dimensions < rhs.dimensions; }

  bool operator>(const Tile &rhs) const { return dimensions > rhs.dimensions; }

  auto to_string() const -> std::string {
    std::stringstream ss;
    ss << "[" << std::left << std::setw(4) << dimensions.first << " x "
       << std::left << std::setw(4) << dimensions.second << "]";
    return ss.str();
  }

  auto print() const -> void { cout << to_string(); }
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

auto print_line() -> void { cout << std::string(30, '-') << '\n'; }

auto main() -> int {

  auto params = get_parameters();

  print_line();
  params.print();
  print_line();

  // full tiles
  int full_tiles_in_col =
      std::floor(static_cast<float>(params.room.second) / params.tile.second);
  int full_tiles_in_row =
      std::floor(static_cast<float>(params.room.first) / params.tile.first);

  // slices
  int slice_right = params.room.first - (full_tiles_in_row * params.tile.first);
  int slice_bottom =
      params.room.second - (full_tiles_in_col * params.tile.second);

  int rows = slice_bottom > 0 ? 1 + full_tiles_in_col : full_tiles_in_col;
  int cols = slice_right > 0 ? 1 + full_tiles_in_row : full_tiles_in_row;

  std::vector<std::vector<Tile>> tiles;
  tiles.resize(rows, std::vector<Tile>(cols));

  std::vector<Tile> left_over_pieces;

  int used_from_left_overs = 0;

  for (auto &row : tiles) {
    for (auto &tile : row) {
      tile.dimensions = params.tile;
      // last tile in row
      if (slice_right > 0 && (&tile == &row.back())) {
        tile.dimensions.first = slice_right;
      }
      // last row
      if (slice_bottom > 0 && (&row == &tiles.back())) {
        tile.dimensions.second = slice_bottom;
      }
      tile.print();

      if (tile.dimensions != params.tile) {
        // if there is a sufficient left over - cut from it
        bool found = false;
        for (auto &lo : left_over_pieces) {
          if (lo.dimensions.first >= tile.dimensions.first &&
              lo.dimensions.second == tile.dimensions.second) {
            lo.dimensions.first -= tile.dimensions.first;
            used_from_left_overs++;
            found = true;
            break;
          }
          if (lo.dimensions.second >= tile.dimensions.second &&
              lo.dimensions.first == tile.dimensions.first) {
            lo.dimensions.second -= tile.dimensions.second;
            used_from_left_overs++;
            found = true;
            break;
          }
        }

        // no sufficient piece in left overs, store the cut
        if (!found) {
          Tile left_over{{{params.tile.first == tile.dimensions.first
                               ? tile.dimensions.first
                               : params.tile.first - tile.dimensions.first},
                          {params.tile.second == tile.dimensions.second
                               ? tile.dimensions.second
                               : params.tile.second - tile.dimensions.second}}};

          left_over_pieces.push_back(left_over);
        }

        // erase all pieces with a dimension of 0
        left_over_pieces.erase(
            std::remove_if(left_over_pieces.begin(), left_over_pieces.end(),
                           [](auto &p) {
                             return p.dimensions.first <= 0 ||
                                    p.dimensions.second <= 0;
                           }),
            left_over_pieces.end());
      }
    }

    // print left overs
    cout << "\t\t Left over: ";
    std::set<Tile> unique_left_over(left_over_pieces.begin(),
                                    left_over_pieces.end());
    for (const auto &u : unique_left_over) {
      auto count =
          std::count(left_over_pieces.begin(), left_over_pieces.end(), u);
      u.print();
      cout << " x " << count << ", ";
    }

    cout << '\n';
  }

  print_line();

  auto full_tiles = full_tiles_in_col * full_tiles_in_row;
  auto tiles_total = ((rows * cols) - used_from_left_overs);
  auto tiles_final = std::ceil(static_cast<double>(tiles_total) * 1.10);

  cout << "Uncut planks needed: " << full_tiles << '\n';
  cout << "Total planks needed (uncut & cut): " << tiles_total << '\n';
  cout << "Plus 10% to accommodate aditional waste: " << tiles_final << '\n';

  print_line();

  return 0;
}
