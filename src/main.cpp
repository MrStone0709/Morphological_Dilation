#include "BinaryImage.h"
#include "StructuringElement.h"

#include <vector>

int main() {
  // 创建一个 5×5 方形结构元素
  std::vector<std::vector<int>> matrix = {{1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1},
                                          {1, 1, 0, 1, 1},
                                          {1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1}};

  StructuringElement element(matrix, 2, 2);

  element.print();

  return 0;
}