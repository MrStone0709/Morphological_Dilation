#ifndef STRUCTURING_ELEMENT_H
#define STRUCTURING_ELEMENT_H

#include <vector>

class StructuringElement {
private:
  std::vector<std::vector<int>> data;

  int anchorRow;
  int anchorCol;

public:
  StructuringElement(const std::vector<std::vector<int>> &matrix, int anchorRow,
                     int anchorCol);

  int get(int row, int col) const;

  int rows() const;

  int cols() const;

  int getAnchorRow() const;

  int getAnchorCol() const;

  void print() const;
};

#endif