#include "BinaryImage.h"
#include "Morphology.h"
#include "StructuringElement.h"

#include <iostream>
#include <vector>

int main() {

  std::vector<std::vector<int>> imageData = {{0, 0, 0, 0, 0},
                                             {0, 1, 1, 0, 0},
                                             {0, 1, 1, 1, 0},
                                             {0, 0, 0, 0, 0},
                                             {0, 0, 0, 0, 0}};

  // 创建 5×5 图像
  BinaryImage image(imageData);

  std::cout << "Original image:" << std::endl;
  image.print();

  // 创建一个不对称结构元素
  std::vector<std::vector<int>> matrix = {{0, 1, 1}, {0, 1, 0}, {1, 0, 0}};

  StructuringElement element(matrix, 1, 1);

  std::cout << std::endl;
  std::cout << "Original structuring element:" << std::endl;

  element.print();

  // 查看 180°反射后的结构元素
  StructuringElement reflected = element.reflected();

  std::cout << std::endl;
  std::cout << "Reflected structuring element:" << std::endl;

  reflected.print();

  // 膨胀
  BinaryImage dilated = Morphology::dilation(image, element);

  std::cout << std::endl;
  std::cout << "Dilated image:" << std::endl;

  dilated.print();

  // 腐蚀
  BinaryImage eroded = Morphology::erosion(image, element);

  std::cout << std::endl;
  std::cout << "Eroded image:" << std::endl;

  eroded.print();

  return 0;
}