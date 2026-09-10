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

/*
 * 返回结构元素关于锚点旋转 180°后的结果
 */
StructuringElement StructuringElement::reflected() const {
  std::vector<std::vector<int>> reflectedData(rows(),
                                              std::vector<int>(cols(), 0));

  for (int row = 0; row < rows(); row++) {
    for (int col = 0; col < cols(); col++) {
      reflectedData[row][col] = data[rows() - 1 - row][cols() - 1 - col];
    }
  }

  int reflectedAnchorRow = rows() - 1 - anchorRow;

  int reflectedAnchorCol = cols() - 1 - anchorCol;

  return StructuringElement(reflectedData, reflectedAnchorRow,
                            reflectedAnchorCol);
}

void StructuringElement::print() const {
  for (const auto &row : data) {
    for (int value : row) {
      std::cout << value << " ";
    }

    std::cout << std::endl;
  }
}