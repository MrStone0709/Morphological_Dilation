#include "BinaryImage.h"
#include <iostream>

BinaryImage::BinaryImage(const std::vector<std::vector<int>> &matrix) {
  data = matrix;
}

int BinaryImage::get(int row, int col) const { return data[row][col]; }

void BinaryImage::set(int row, int col, int value) { data[row][col] = value; }

int BinaryImage::rows() const { return data.size(); }

int BinaryImage::cols() const {
  if (data.empty()) {
    return 0;
  }

  return data[0].size();
}

void BinaryImage::print() const {
  for (const auto &row : data) {
    for (int value : row) {
      std::cout << value << " ";
    }

    std::cout << std::endl;
  }
}