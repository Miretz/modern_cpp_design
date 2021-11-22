#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <complex>

auto main() -> int {

  std::string temp;
  std::ifstream file("matrix_market.txt");

  // handle comment lines
  std::getline(file, temp);
  while ((temp.length() == 0 || temp[0] == '%') && !file.eof()) {
    std::cout << "LINE SKIPPED: " << temp << std::endl;
    std::getline(file, temp);
  }

  // get the dimesnsions of the matrix
  int rows;
  int cols;
  std::istringstream dimensions_stream(temp);
  dimensions_stream >> rows >> cols;
  std::cout << "Matrix dimensions are " << rows << " by " << cols
            << std::endl;

  using val_t = std::complex<double>;


  std::vector<std::vector<val_t>> data_matrix;
  data_matrix.resize(rows, std::vector<val_t>(cols));

  int row;
  int col;
  double real;
  double imag = 0;

  while (!file.eof()) {
    std::getline(file, temp);
    std::istringstream number_stream(temp);
    number_stream >> col;
    number_stream >> row;
    number_stream >> real;
    imag = 0.0;
    number_stream >> imag;
    data_matrix[col][row] = {real, imag};
  }

  std::cout << std::fixed << std::setprecision(1);

  // print matrix
  for (const auto &row_data : data_matrix) {
    for (const auto &val : row_data) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
