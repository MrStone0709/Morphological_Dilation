#include "StructuringElement.h"
#include <iostream>

// 通过构造函数初始化结构元素的矩阵数据和锚点位置
StructuringElement::StructuringElement(
    const std::vector<std::vector<int>> &matrix, int anchorRow, int anchorCol) {
  data = matrix;

  this->anchorRow = anchorRow;
  this->anchorCol = anchorCol;
}

int StructuringElement::get(int row, int col) const { return data[row][col]; }

int StructuringElement::rows() const { return data.size(); }

int StructuringElement::cols() const {
  if (data.empty()) {
    return 0;
  }

  return data[0].size();
}

int StructuringElement::getAnchorRow() const { return anchorRow; }

int StructuringElement::getAnchorCol() const { return anchorCol; }

void StructuringElement::print() const {
  for (const auto &row : data) {
    for (int value : row) {
      std::cout << value << " ";
    }

    std::cout << std::endl;
  }
}