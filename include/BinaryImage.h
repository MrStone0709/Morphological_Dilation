#ifndef BINARY_IMAGE_H
#define BINARY_IMAGE_H

#include <vector>

class BinaryImage {
private:
  std::vector<std::vector<int>> data;

public:
  BinaryImage(int rows, int cols);

  int get(int row, int col) const;

  void set(int row, int col, int value);

  int rows() const;

  int cols() const;

  void print() const;
};

#endif