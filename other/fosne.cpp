#include <algorithm>
#include <array>
#include <cmath>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// Laminate flooring. Calculates the number of planks needed.

inline constexpr auto black_pixel = "0 0 0\n";
inline constexpr auto white_pixel = "255 255 255\n";

inline constexpr std::array<std::string_view, 6> colors{{
    {"145 189 241\n"},
    {"63 218 132\n"},
    {"221 225 132\n"},
    {"221 225 245\n"},
    {"255 183 247\n"},
    {"255 155 157\n"},
}};

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
  std::string_view color;

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

  auto draw_line(int y) const -> std::string {
    std::stringstream ss;
    ss << black_pixel;
    for (int x = 0; x < dimensions.first - 2; x++) {
      if (y == (dimensions.second - 1)) {
        ss << black_pixel;
      } else {
        ss << color;
      }
    }
    ss << black_pixel;
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

auto export_image(std::pair<int, int> image_size,
                  const std::vector<std::vector<Tile>> &tiles) -> void {
  std::ofstream file;
  file.open("output.ppm");
  file << "P3\n" << image_size.first << ' ' << image_size.second << "\n255\n";

  bool reverse_row = false;
  for (auto &row : tiles) {
    for (int y = 0; y < row[0].dimensions.second; y++) {
      if (reverse_row) {
        for (int i = row.size() - 1; i >= 0; --i) {
          file << row[i].draw_line(y);
        }
      } else {
        for (const auto &tile : row) {
          file << tile.draw_line(y);
        }
      }
    }
    reverse_row = !reverse_row;
  }

  file.close();
}

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

  int index = 0;

  for (auto &row : tiles) {
    for (auto &tile : row) {
      auto color = colors[index++ % colors.size()];
      tile.color = color;
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
                               : params.tile.second - tile.dimensions.second}},
                         color};

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

  cout << "Exporting image...\n";
  export_image(params.room, tiles);
  cout << "DONE.\n";

  print_line();

  return 0;
}
